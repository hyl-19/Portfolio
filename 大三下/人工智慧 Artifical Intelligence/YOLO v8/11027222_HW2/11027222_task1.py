import cv2
from ultralytics import YOLO
import torch
import time


def track_objects(video_path, model_path, conf=0.5, iou=0.5):
    device = 'cuda' if torch.cuda.is_available() else 'cpu'
    model = YOLO(model_path).to(device)
    cap = cv2.VideoCapture(video_path)
    while cap.isOpened():
        ret, frame = cap.read()
        if not ret:
            break
        results = model(frame, device=device, iou=iou, conf=conf)
        for result in results:
            for box in result.boxes:
                if box.conf.item() > conf:
                    bbox = box.xyxy[0].tolist()
                    class_id = int(box.cls.item())
                    confidence = float(box.conf.item())
                    cv2.rectangle(frame, (int(bbox[0]), int(bbox[1])), (int(
                        bbox[2]), int(bbox[3])), (0, 255, 0), 2)
                    cv2.putText(frame, f"{class_id} {confidence:.2f}", (int(bbox[0]), int(
                        bbox[1]) - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 2)
        cv2.imshow(f"Frame-{model_path}", frame)
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break
    cap.release()
    cv2.destroyAllWindows()


# Define paths to the models and video
video_path = 'run.mp4'
models = {
    'YOLOv8n': 'yolov8n.pt',
    'YOLOv8s': 'yolov8s.pt',
    'YOLOv8m': 'yolov8m.pt'
}

tracking_times = []

for model_name, model_path in models.items():
    print(f"Tracking with {model_name}")
    start = time.time()
    track_objects(video_path, model_path)
    end = time.time()
    duration = end - start
    tracking_times.append((model_name, duration))

# 在迴圈結束後印出每個模型的運行時間
for model_name, duration in tracking_times:
    print(f"{model_name} Tracking time: {duration:.2f} seconds")
