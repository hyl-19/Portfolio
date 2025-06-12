
# 演算法分析機測
# 學號: 11027222 / 11027234 / 11027254
# 姓名: 黃彥霖 / 邱宥文 / 方璿瑞
# 中原大學資訊工程系

import time


def longest_increasing_subsequence(arr):
    if len(arr) == 0:
        return 0, []
    if len(arr) == 1:
        return 1, arr

    n = len(arr)
    dp = [1] * n
    parent = [-1] * n

    max_len = 1
    max_index = 0

    for i in range(1, n):
        for j in range(i):
            if arr[j] < arr[i] and dp[j] + 1 >= dp[i]:
                dp[i] = dp[j] + 1
                parent[i] = j
                if dp[i] >= max_len:
                    max_len = dp[i]
                    max_index = i

    lis = []
    current = max_index
    while current != -1:
        lis.append(arr[current])
        current = parent[current]
    lis.reverse()

    return max_len, lis


def main():
    answer = []
    str = input()
    while str != '0':
        str = str.split(' ')
        arr = []
        for i in str:
            arr.append(int(i))

        start_time = time.time()
        l, s = longest_increasing_subsequence(arr)
        total_time = time.time() - start_time

        answer.append((l, s))
        str = input()
    for t in answer:
        print(f"\nLength of LIS = {t[0]}\nLIS = <", end='')
        i = 0
        while i < len(t[1]):
            print(f" {t[1][i]}", end='')
            if i < len(t[1]) - 1:
                print(',', end='')
            else:
                print(' >')
            i += 1
        print('')

        print("time: ", total_time)


if __name__ == '__main__':
    main()
