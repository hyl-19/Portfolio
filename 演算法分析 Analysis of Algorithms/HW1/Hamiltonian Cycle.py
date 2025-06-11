# 演算法分析機測
# 學號: 11027222 / 11027239 / 11027254
# 姓名: 黃彥霖 / 邱宥文 / 方璿瑞
# 中原大學資訊工程系

import time


def Hamiltonian_path(n, edges):
    neighbor = {i: [] for i in range(1, n+1)}
    # 對於兩個點提供雙向紀錄
    # ex: {1: [2, 3, 5], 2: [1, 4, 6], 3: [1, 4, 7], 4: [2, 3, 8], 5: [1, 6, 7], 6: [2, 5, 8], 7: [3, 5, 8], 8: [4, 6, 7]}
    for u, v in edges:
        neighbor[u].append(v)
        neighbor[v].append(u)

    for start_point in range(1, n+1):  # 從1開始當起點試試看
        path = [start_point]
        visited = set([start_point])  # 設start_point為1

        def backtrack(vertex):
            if len(path) == n:  # 所有頂點都被訪問過了
                if (path[-1] in neighbor[1]):  # 檢查是否可以形成迴圈,path[-1]->最後一個元素在neighbor
                    return True
                else:
                    return False

            for i in neighbor[vertex]:  # next vertice can be found
                if i not in visited:  # 一個點，看和他有連接的點
                    visited.add(i)
                    path.append(i)

                    if backtrack(i):  # 有找到，return true
                        return True
                    visited.remove(i)  # 往這裡跑就代表沒跑到，移除當前的點，找下一個neighbour
                    path.pop()

            return False

        if backtrack(start_point):
            return path + [start_point]

    return "No Hamiltonian cycle can be found"


def Read_input():
    edges_list = []

    vertices, edges_count = map(int, input().split())
    if (vertices == 0 and edges_count == 0):
        return vertices, edges_list

    for _ in range(edges_count):
        edge = tuple(map(int, input().split()))
        edges_list.append(edge)

    return vertices, edges_list


def main():
    while (1):
        vertices, edges_list = Read_input()
        if (vertices == 0):
            break
        start_time = time.time()
        result = Hamiltonian_path(vertices, edges_list)
        print(result)
        total_time = time.time() - start_time
        print(f"time = {total_time}")


if __name__ == "__main__":
    main()


'''
8 12
1 2
1 3
1 5
2 4
2 6
3 4
3 7
4 8
5 6
5 7
6 8
7 8
8 12
1 2
1 3
1 5
2 4
2 6
3 4
3 7
4 8
5 6
5 7
6 8
7 8
0 0
[1, 2, 4, 3, 7, 8, 6, 5, 1]
'''
