# 演算法分析機測
# 學號 : 11027222 / 11027239 / 11027254
# 姓名 : 黃彥霖 / 邱宥文 / 方璿瑞
# 中原大學資訊工程系

import time


def dfs(matrix, x, y, visited):
    # 四個參數 matrix是二維矩陣 x和y是開始搜索的點的坐標 visited用於記錄是否被訪問過。
    directions = [(-1, 0), (1, 0), (0, -1), (0, 1), (-1, -1),
                  (-1, 1), (1, -1), (1, 1)]  # 全部方向無死角
    stack = [(x, y)]
    area = 0  # 初始化
    while stack:  # 只要有訪問到就會繼續
        cx, cy = stack.pop()  # 後進先出 (因為使用的是DFS)
        if visited[cx][cy]:  # 訪問過就跳過
            continue
        visited[cx][cy] = True  # 紀錄是否訪問過
        area += 1  # 增加他的area
        for dx, dy in directions:  # 無死角搜索
            nx, ny = cx + dx, cy + dy
            if 0 <= nx < len(matrix) and 0 <= ny < len(matrix[0]) and matrix[nx][ny] == 1 and not visited[nx][ny]:
                stack.append((nx, ny))
    return area


def connected_components(matrix):
    rows, cols = len(matrix), len(matrix[0])  # 取得他的rows and columns
    # 創建一個跟matrix大小一樣的矩陣然後把全部都設為false
    visited = [[False for _ in range(cols)] for _ in range(rows)]
    components = []

    for i in range(rows):
        for j in range(cols):
            if matrix[i][j] == 1 and not visited[i][j]:  # 如果是1並且沒有被訪問過就開始循環
                area = dfs(matrix, i, j, visited)
                components.append(area)

    return components


count = 1  # 計算第幾張圖


while True:
    rows, cols = map(int, input().split())  # 輸入你的rows and columns ex: 10 10
    if rows == 0 and cols == 0:
        break

    # 看你上面輸入多少這邊就輸入 你rows * columns的數量
    matrix = []
    for _ in range(rows):
        row = list(map(int, list(input().strip())))
        matrix.append(row)
    start_time = time.time()
    # 執行並輸出
    components = connected_components(matrix)
    print(f"Image #{count}")
    print(f"Number of Connected Components = {len(components)}")
    for i, area in enumerate(components, start=1):
        print(f"Connected Component #{i} Area = {area}")
    count += 1
    total_time = time.time() - start_time
    print(f"time = {total_time}")
