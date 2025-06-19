# 演算法分析機測
# 學號 : 11027222 / 11027239 / 11027254
# 姓名 : 黃彥霖 / 邱宥文 / 方璿瑞
# 中原大學資訊工程系
import time
import cv2
import numpy as np
import os
import matplotlib.pyplot as plt

image_path = input("Enter file name: ")

img = cv2.imread(image_path, 1)

gray_img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
_, binary_maze_corrected = cv2.threshold(
    gray_img, 127, 255, cv2.THRESH_BINARY_INV)

start_point_corrected = (0, 0)
end_point_corrected = (
    binary_maze_corrected.shape[1] - 1, binary_maze_corrected.shape[0] - 1)


def find_shortest_path_corrected(binary_maze, start, end):
    rows, cols = binary_maze.shape
    queue = [(start, [start])]
    visited = set()

    while queue:
        (x, y), path = queue.pop(0)
        if (x, y) == end:
            return path

        for dx, dy in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
            nx, ny = x + dx, y + dy
            if 0 <= nx < cols and 0 <= ny < rows and binary_maze[ny, nx] == 255 and (nx, ny) not in visited:
                visited.add((nx, ny))
                queue.append(((nx, ny), path + [(nx, ny)]))

    return None


start_time = time.time()
path_corrected = find_shortest_path_corrected(
    binary_maze_corrected, start_point_corrected, end_point_corrected)
total_time = time.time() - start_time


def center_path(path):
    return [(x * 20 + 10, y * 20 + 10) for (x, y) in path]


if path_corrected:
    path_centered = center_path([(x//20, y//20) for (x, y) in path_corrected])
else:
    path_centered = []

maze_color_final = cv2.imread(image_path)

if path_centered:
    for i in range(len(path_centered) - 1):
        # 藍色的線條，寬度2
        cv2.line(maze_color_final,
                 path_centered[i], path_centered[i + 1], (255, 0, 0), 2)

base, ext = os.path.splitext(image_path)
result_path_final = f"{base}sol{ext}"
print(f"time = {total_time}")
plt.figure(figsize=(10, 10))
plt.imshow(cv2.cvtColor(maze_color_final, cv2.COLOR_BGR2RGB))
plt.axis('off')
plt.show()

cv2.imwrite(result_path_final, maze_color_final)

print(f"result file：{result_path_final}")
