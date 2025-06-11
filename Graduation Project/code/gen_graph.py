import pandas as pd
import matplotlib.pyplot as plt
from gen_html import generate_html
import os
import sys

def tansfer_file(txt_file):  # 读取txt
    sound_data = []
    with open(txt_file, 'r', encoding='utf-8') as file:
        lines = file.readlines()

        for line in lines:
            parts = line.split(', Confidence: ')
            if len(parts) == 2:
                # 提取声音标签和置信度
                sound = parts[0].strip()
                confidence = float(parts[1].strip())
                sound_data.append((sound, confidence))

    df = pd.DataFrame(sound_data, columns=['Sound', 'Confidence'])

    return df

def pie_chart(sound_counts, pie_chart_path):
    plt.figure(figsize=(12, 12))
    plt.pie(
        sound_counts['Count'],
        labels=sound_counts['Sound'],
        autopct='%1.1f%%',  # 在图上显示比例
        startangle=90,
        wedgeprops={'edgecolor': 'none'},  # 移除外边框
        textprops={'fontsize': 8}  # 减少字体大小，避免拥挤
    )
    plt.title('Sound Occurrences (Percentage)', fontsize=14)
    plt.tight_layout()  # 自动调整图表的边界

    plt.savefig(pie_chart_path)
    plt.close()

def bar_chart(sound_counts, bar_chart_path):
    plt.figure(figsize=(12, 10))  # 调整图像高度
    plt.bar(sound_counts['Sound'], sound_counts['Count'], color='skyblue')
    plt.title('Sound Occurrences (All Sounds)', fontsize=16)
    plt.xlabel('Sound', fontsize=14)
    plt.ylabel('Count', fontsize=14)
    plt.xticks(rotation=45, ha='right', fontsize=10)  # 旋转X轴标签，避免拥挤
    plt.yticks(fontsize=12)

    plt.tight_layout()  # 自动调整布局，避免标签重叠
    plt.savefig(bar_chart_path)
    plt.close()

def generate_graph(df):
    # 统计声音出现次数
    sound_counts = df['Sound'].value_counts().reset_index()
    sound_counts.columns = ['Sound', 'Count']

    pie_chart_path = 'pie.png'
    bar_chart_path = 'bar.png'

    pie_chart(sound_counts, pie_chart_path)
    bar_chart(sound_counts, bar_chart_path)

    top_5_sounds = sound_counts.head(5)

    return pie_chart_path, bar_chart_path, top_5_sounds

def continuous_sounds(df):
    longest_counts = []

    # 遍历所有声音种类
    for sound in df['Sound'].unique():
        sound_data = df['Sound'].tolist()
        max_count = 0
        current = 0
        gaps = 0

        for i in range(len(sound_data)):
            if sound_data[i] == sound:
                current += 1
                gaps = 0
            else:
                gaps += 1
                if gaps <= 2:  # 确定允许的间隔数量
                    current += 1
                else:
                    max_count = max(max_count, current)
                    current = 0
                    gaps = 0

        # 最后一次出现的可能是最大值
        max_count = max(max_count, current)
        longest_counts.append((sound, max_count))

    # 根据最大连续出现次数排序，取前五名
    top_5_sounds = sorted(longest_counts, key=lambda x: x[1], reverse=True)[:5]

    return top_5_sounds

def main():
    txt_file = 'real_result.txt'  # 替换为你的txt文件路径
    html_file_path = 'sound_statistics.html'

    df = tansfer_file(txt_file)

    if df.empty:
        print("Warning: 'real_result.txt' is empty")
    else:
        pie_chart_path, bar_chart_path, top_5_sounds = generate_graph(df)
        top_5_continuous_sounds = continuous_sounds(df)



        generate_html(pie_chart_path, bar_chart_path, top_5_sounds,
                      top_5_continuous_sounds, html_file_path)

if __name__ == '__main__':
    main()
