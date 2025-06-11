import threading
import queue
import laion_clap
import json
import torch
import numpy as np
import sounddevice as sd
from pydub import AudioSegment
from io import BytesIO
from transfer_labels import labels
import os
import tkinter as tk
from tkinter import scrolledtext, messagebox
from tkinter import font as tkfont
from datetime import datetime, timedelta
import subprocess
import sys

# 設置設備
device = torch.device('cuda:0' if torch.cuda.is_available() else 'cpu')

# 加載類別索引和模型
class_index_dict_path = 'audioset_class_labels_indices.json'
ckpt = r'C:\\Users\\huang\\Desktop\\LION_CLAP\\630k-audioset-best.pt'

model = laion_clap.CLAP_Module(enable_fusion=False, device=device)
model.load_ckpt(ckpt)

with open(class_index_dict_path, encoding='utf-8') as f:
    class_index_dict = {int(k): v for v, k in json.load(f).items()}

all_texts = ["This is a sound of " + v for k, v in class_index_dict.items()]


def text_embeddings(texts, model, batch_size=50):
    embeddings = []
    for i in range(0, len(texts), batch_size):
        batch_texts = texts[i:i + batch_size]
        batch_embeddings = model.get_text_embedding(batch_texts)
        embeddings.append(torch.tensor(batch_embeddings))
    return torch.cat(embeddings, dim=0)


# 嵌入文本
text_embed = text_embeddings(all_texts, model, batch_size=200)


def classify_sound(audio_segment):
    with torch.no_grad():
        audio_embed = model.get_audio_embedding_from_filelist(
            x=[audio_segment])
        similarities = torch.tensor(audio_embed) @ text_embed.t()
        ranking = torch.argsort(similarities, descending=True)
        top_pred_idx = ranking[0, 0].item()
        confidence_score = similarities[0, top_pred_idx].item()

        if top_pred_idx in class_index_dict:
            predicted_label = labels.get(top_pred_idx, "Unknown")
        else:
            predicted_label = "Unknown"

        return predicted_label, confidence_score


def audio_callback(indata, frames, time, status, q):
    if status:
        print(status, flush=True)
    q.put(indata.copy())


def process_audio_data(q, result_queue, stop_event, file_handle, channels, fs):
    buffer = np.zeros((0, channels), dtype=np.float32)
    window_size = fs * 4  # 4 秒音頻
    stride = fs * 3       # 每次滑動 3 秒

    audio_counter = 1

    while not stop_event.is_set():
        try:
            data = q.get(timeout=0.1)
        except queue.Empty:
            continue
        if data is None:
            break
        buffer = np.concatenate((buffer, data), axis=0)

        while len(buffer) >= window_size:
            audio_data = buffer[:window_size]
            buffer = buffer[int(stride):]

            audio_data_int16 = (audio_data * 32767).astype(np.int16)
            audio_segment = AudioSegment(
                data=audio_data_int16.tobytes(),
                sample_width=audio_data_int16.dtype.itemsize,
                frame_rate=fs,
                channels=channels
            )

            audio_counter += 1

            # 計算時間範圍
            end_time = datetime.now()
            start_time = end_time - timedelta(seconds=4)

            # 分類聲音
            audio_file = BytesIO()
            audio_segment.export(audio_file, format="wav")
            predicted_label, confidence_score = classify_sound(audio_file)

            # 格式化時間標籤
            time_label = f"[{start_time.strftime('%H:%M:%S')} ~ {end_time.strftime('%H:%M:%S')}]"
            result_gui = f"{time_label} {predicted_label}"
            result_file = f"{predicted_label}, Confidence: {confidence_score:.2f}"

            print(result_gui)
            file_handle.write(result_file + "\n")
            file_handle.flush()

            # 將結果發送到 UI
            result_queue.put(result_gui)


def classify_real_time_audio(fs_arg=44100, q=None, stop_event=None):
    channels = 1  # 單聲道
    fs = fs_arg
    with sd.InputStream(samplerate=fs, channels=channels, callback=lambda *args: audio_callback(*args, q)):
        while not stop_event.is_set():
            sd.sleep(100)


# 設置 GUI

def create_gui():
    root = tk.Tk()
    root.title("Real Time Sounds Classification")
    root.geometry("1280x720") 

    # 設定字體
    default_font = tkfont.Font(family="Helvetica", size=14)
    root.option_add("*Font", default_font)

    # 創建滾動文本框
    text_area = scrolledtext.ScrolledText(
        root, wrap=tk.WORD, width=90, height=20, state='disabled', font=("Helvetica", 12))
    text_area.pack(padx=20, pady=20, fill=tk.BOTH, expand=True)

    # 創建按鈕框架
    button_frame = tk.Frame(root)
    button_frame.pack(pady=10)

    # 定義事件控制
    stop_event = threading.Event()
    audio_thread = None
    classify_thread = None
    file_handle = None

    # 創建結果隊列
    result_queue = queue.Queue()
    # 初始化音頻隊列
    q = queue.Queue()

    def start_recording():
        nonlocal audio_thread, classify_thread, file_handle, q
        if audio_thread and audio_thread.is_alive():
            messagebox.showwarning(
                "Warning", "Recording is already in progress!")
            return
        # 每次開始錄音時刷新文件
        file_handle = open('real_result.txt', 'w', encoding='utf-8')
        stop_event.clear()
        # 確保 q 被初始化
        q = queue.Queue()
        # 啟動處理音頻數據的線程，並傳遞 q
        audio_thread = threading.Thread(target=process_audio_data, args=(
            q, result_queue, stop_event, file_handle, 1, 44100), daemon=True)
        audio_thread.start()
        # 啟動分類音頻的線程，並傳遞 q
        classify_thread = threading.Thread(target=classify_real_time_audio, args=(
            44100, q, stop_event), daemon=True)
        classify_thread.start()
        update_text()
        print("Start Recording")

    def stop_recording():
        nonlocal file_handle
        if not audio_thread:
            messagebox.showwarning("Warning", "Recording has not started yet!")
            return
        stop_event.set()
        q.put(None)
        if file_handle:
            file_handle.close()
        print("Stop Recording")

    def generate_results():
        try:
            # 運行 gen_graph.py
            subprocess.run([sys.executable, "gen_graph.py"], check=True)
            messagebox.showinfo("Success", "Results generated successfully!")
            # 直接打開生成的 HTML 文件
            html_file_path = 'sound_statistics.html'
            if sys.platform.startswith('darwin'):
                subprocess.call(('open', html_file_path))
            elif os.name == 'nt':
                os.startfile(html_file_path)
            elif os.name == 'posix':
                subprocess.call(('xdg-open', html_file_path))
        except subprocess.CalledProcessError as e:
            messagebox.showerror("Error", f"Error generating results: {e}")
        except Exception as e:
            messagebox.showerror("Error", f"Unexpected error: {e}")

    def close_application():
        nonlocal file_handle
        if audio_thread and audio_thread.is_alive():
            stop_event.set()
            q.put(None)
            audio_thread.join()
        if classify_thread and classify_thread.is_alive():
            classify_thread.join()
        if file_handle:
            file_handle.close()
        root.destroy()
        print("Application Closed")

    # 創建按鈕
    start_button = tk.Button(button_frame, text="Start", width=15,
                             command=start_recording, bg="#4CAF50", fg="white", font=("Helvetica", 14))
    start_button.grid(row=0, column=0, padx=10, pady=10)

    end_button = tk.Button(button_frame, text="End", width=15,
                           command=stop_recording, bg="#f44336", fg="white", font=("Helvetica", 14))
    end_button.grid(row=0, column=1, padx=10, pady=10)

    gen_button = tk.Button(button_frame, text="Generate Results",
                           width=20, command=generate_results, bg="#008CBA", fg="white", font=("Helvetica", 14))
    gen_button.grid(row=0, column=2, padx=10, pady=10)

    close_button = tk.Button(button_frame, text="Close", width=15,
                             command=close_application, bg="#555555", fg="white", font=("Helvetica", 14))
    close_button.grid(row=0, column=3, padx=10, pady=10)

    def update_text():
        while not result_queue.empty():
            result = result_queue.get()
            text_area.configure(state='normal')
            text_area.insert(tk.END, result + "\n")
            text_area.configure(state='disabled')
            text_area.yview(tk.END)
        if not stop_event.is_set():
            root.after(1000, update_text)

    root.protocol("WM_DELETE_WINDOW", close_application)  # 確保點擊窗口關閉按鈕也能正常關閉

    root.mainloop()


def main():
    create_gui()


if __name__ == "__main__":
    print("Starting application...")
    main()
    print("Application ended.")
