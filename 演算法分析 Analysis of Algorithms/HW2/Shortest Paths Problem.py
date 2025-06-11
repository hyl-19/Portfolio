# 演算法分析機測
# 學號: 11027222 / 11027234 / 11027254
# 姓名: 黃彥霖 / 邱宥文 / 方璿瑞
# 中原大學資訊工程系

import heapq
import time


def dijkstra(n, edges, source):

    # edges' list，對於每邊(u, v, w)，在 graph[u]中加入(v, w)。
    """
    1 (2, 2)
    1 (5, 10)
    2 (3, 3)
    2 (5, 7)
    3 (4, 4)
    4 (5, 5)
    5 (3, 6)
    """
    graph = {i: [] for i in range(1, n + 1)}
    for u, v, w in edges:
        graph[u].append((v, w))

    # 初始化距離
    distances = {i: float('inf') for i in range(1, n + 1)}
    distances[source] = 0  # {1: 0, 2: inf, 3: inf, 4: inf, 5: inf}
    q = [(0, source)]

    while q:
        # 從heap中選出當前距離最小的頂點，並更新其鄰居的距離。
        # 如果發現更短的距離，則更新並將鄰居加入優先隊列。

        # q is ( current distance, 目前的點 )
        cur_dist, cur_vert = heapq.heappop(q)

        if cur_dist > distances[cur_vert]:  # 跳過這個頂點。在此情況下，已經找到了一條更短的路徑。
            continue

        # 有更小的，更新distance，存入新的distance in heap
        for neighbor, weight in graph[cur_vert]:
            distance = cur_dist + weight

            if distance < distances[neighbor]:
                distances[neighbor] = distance
                heapq.heappush(q, (distance, neighbor))

    return distances


def main():

    while True:
        n = int(input("Enter number of vertices (0 to end): "))
        if n == 0:
            break
        m = int(input("Enter number of edges: "))
        source = int(input("Enter source vertex: "))
        edges = []

        for _ in range(m):
            u, v, w = map(int, input().split())
            edges.append((u, v, w))

        input()  # read 0

        print("output")
        start_time = time.time()
        distances = dijkstra(n, edges, source)
        total_time = time.time() - start_time
        for i in range(1, n + 1):
            if i != source:
                print(f"{source} to {i} = {distances[i]}")

        print("time: ", total_time)


if __name__ == "__main__":
    main()

"""
5
7
1
1 2 2
1 5 10
2 3 3
2 5 7
3 4 4
4 5 5
5 3 6
0
"""
