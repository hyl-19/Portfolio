# 演算法分析機測
# 學號: 11027222 / 11027239 / 11027254
# 姓名: 黃彥霖 / 邱宥文 / 方璿瑞
# 中原大學資訊工程系

import time


class WaterJug():
    def gcd(self, a, b):  # 找到最大公因數
        if b == 0:
            return a
        return self.gcd(b, a % b)

    def Pour(self, a, b, target, jug=['A', 'B']):
        print(f"Fill {jug[0]}")  # 將A裝滿水
        fromWaterJug = a
        toWaterJug = 0
        result = False

        while (toWaterJug != target):  # 假如還未達成目標
            temp = min(fromWaterJug, b - toWaterJug)

            toWaterJug = toWaterJug + temp
            fromWaterJug = fromWaterJug - temp
            print(f"Pour {jug[0]} {jug[1]}")  # 將A倒入B

            if (toWaterJug == target):  # 如果以達成目標就return
                result = True
                break

            if fromWaterJug == 0:  # 當A為empty時，將A注滿水
                fromWaterJug = a
                print(f"Fill {jug[0]}")

            if toWaterJug == b:  # 當B滿，將B之水倒光
                toWaterJug = 0
                print(f"Empty {jug[1]}")

        return result

    def Process(self, a, b, target):

        if target % self.gcd(a, b) != 0:  # 若目標無法整除A,B兩水桶容量的最大公因數就無解
            print("No answer")
            return
        if target > a + b:  # 若目標大於A and B
            print("No answer")
            return

        jug = ['A', 'B']
        if (a > b):  # 假如A 容量大於 B , 將A and B交換
            temp = a
            a = b
            b = temp
            jug[0] = 'B'
            jug[1] = 'A'

        result = self.Pour(a, b, target, jug)

        if result:
            print("Success")
        else:
            print("No answer")


def main():
    inputNum = input("輸入三個數字（輸入{0 0 0}結束）：")
    problem_list = []
    temp = inputNum.split(' ')
    while temp[0] != '0' and temp[1] != '0' and temp[2] != '0':
        problem_list.append(temp)
        inputNum = input("輸入三個數字（輸入{0 0 0}結束）：")
        temp = inputNum.split(' ')

    process = WaterJug()
    cnt = 0
    for x in problem_list:
        cnt += 1
        start_time = time.time()
        process.Process(int(x[0]), int(x[1]), int(x[2]))
        print(f"execution time {cnt}:{time.time() - start_time}")
    return 0


if __name__ == '__main__':
    main()
