# 演算法分析機測
# 學號: 11027222 / 11027234 / 11027254
# 姓名: 黃彥霖 / 邱宥文 / 方璿瑞
# 中原大學資訊工程系

import time


def knapsack(W, weights, values):
    n = len(values)
    dp = []
    for i in range(n+1):
        t = []
        for j in range(W+1):
            t.append(0)
        dp.append(t)

    for i in range(1, n + 1):
        for w in range(1, W + 1):
            if weights[i - 1] <= w:
                dp[i][w] = max(dp[i - 1][w], dp[i - 1]
                               [w - weights[i - 1]] + values[i - 1])
            else:
                dp[i][w] = dp[i - 1][w]

    w = W
    items = []
    for i in range(n, 0, -1):
        if dp[i][w] != dp[i - 1][w]:
            items.append(i)
            w -= weights[i - 1]

    items.sort()
    return dp[n][W], items


def print_result(max_value, items):
    print("Total Value =", max_value)
    print("Items =", end=' ')
    i = 0
    while i < len(items):
        print(items[i], end='')
        if i < len(items) - 1:
            print(', ', end='')
        i += 1


def main():
    W = int(input())
    answer = []
    while W != 0:
        num = int(input())
        weights = []
        values = []
        while num > 0:
            s = input()
            s = s.split(' ')
            weights.append(int(s[0]))
            values.append(int(s[1]))
            num -= 1

        start_time = time.time()
        max_value, items = knapsack(W, weights, values)
        total_time = time.time() - start_time

        answer.append((max_value, items))
        W = int(input())

    for i in answer:
        print_result(i[0], i[1])
        print('')
        print("time: ", total_time)


if __name__ == '__main__':
    main()
