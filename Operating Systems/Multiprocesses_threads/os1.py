import os
import time
import numpy as np

from numba import jit
from queue import Queue
from threading import Thread, Semaphore
from datetime import datetime, timedelta, timezone
from concurrent.futures import ProcessPoolExecutor, as_completed


def Filetime():
    tz_east_8 = timezone(timedelta(hours=8))
    now = datetime.now(tz_east_8)
    tine = now.strftime("%Y-%m-%d %H:%M:")
    second = f"{now.second + now.microsecond / 1000000:.6f}"
    current_time = (tine + second + "+08:00")
    return current_time


def Writefile(outfilename, data, totaltime):
    with open(outfilename, 'w') as file:
        file.write("Sort : \n")
        for num in data:
            file.write(f"{num}\n")

        file.write(f"CPU Time : {totaltime}\n")
        file.write(f"Output Time : {Filetime()}")


def Spilt_data(list, k):
    return np.array_split(list, k)


# decorated code so that it will entriely without the involvement sof the Pyhton interpreter
@jit(nopython=True)
def Bubblesort(temp):
    n = len(temp)

    for i in range(n):
        swap = False
        # if (i % 10 == 0):
        #  print(i)

        for j in range(0, n-i-1):
            if temp[j] > temp[j+1]:
                temp[j], temp[j+1] = temp[j+1], temp[j]
                swap = True

        if (swap == False):
            break
    return temp


@jit(nopython=True)
def Mergesort(L_list, R_list):
    i = j = 0
    temp = []
    while (i < len(L_list) and j < len(R_list)):
        if (L_list[i] < R_list[j]):
            temp.append(L_list[i])
            i += 1
        else:
            temp.append(R_list[j])
            j += 1

    while (i < len(L_list)):
        temp.append(L_list[i])
        i += 1
    while (j < len(R_list)):
        temp.append(R_list[j])
        j += 1

    return temp

# -----------------------------------------------------------------


def Task1(filename):
    outfilename = filename + "_output1.txt"

    with open(filename + ".txt", 'r') as file:
        data = [int(line.strip()) for line in file]

    # ===========================================================
    start = time.perf_counter()
    Bubblesort(data)
    totaltime = (time.perf_counter() - start) * 1000
    # ===========================================================
    # print(totaltime)  # 繳交要刪掉-------------------------------

    Writefile(outfilename, data, totaltime)


def Task2(filename, slicenum):
    outfilename = filename + "_output2.txt"

    with open(filename + ".txt", 'r') as file:
        data = [int(line.strip()) for line in file]

    # print(f'data : {data}')

    sep_list = Spilt_data(data, slicenum)  # is a list [ [], [], [] ]

    ans = []
    # ===========================================================
    start = time.perf_counter()
    for i in sep_list:
        Bubblesort(i)
        ans.append(i)

    # print(ans)
    while (len(ans) != 1):
        # print(f'wewee : {ans[0]}        {ans[1]}')
        temp = Mergesort(ans[0], ans[1])
        del ans[0:2]
        ans.append(temp)

    totaltime = (time.perf_counter() - start) * 1000
    # ===========================================================
    # print(totaltime)  # 繳交要刪掉-------------------------------

    Writefile(outfilename, ans[0], totaltime)


def Multi_pro_bbsort(sep_list, processesnum):
    with ProcessPoolExecutor(max_workers=processesnum) as executor:
        run = [executor.submit(Bubblesort, sublist) for sublist in sep_list]

        bb_list = []  # 存完成bbsort的list
        # as_completed -> 蒐集每個任務的結果
        for newcome in as_completed(run):
            temp = newcome.result()  # .result來拿做完的process
            bb_list.append(temp)

    return bb_list


def Multi_pro_mgsort(ans_list, processesnum):  # already -1 when it was called
    if (processesnum == 0):  # if k = 1, k-- == 0, process num is not allow to be set at 0
        processesnum = 1
    with ProcessPoolExecutor(max_workers=processesnum) as executor:
        while (len(ans_list) != 1):
            nextturn = []  # next round's list
            mgsort = []  # 存running's mgsort

            for i in range(0, len(ans_list), 2):  # 每兩個丟入precessor
                if (i + 1 < len(ans_list)):
                    run = executor.submit(
                        Mergesort, ans_list[i], ans_list[i+1])
                    mgsort.append(run)
                else:  # reamin one list, do it next time
                    nextturn.append(ans_list[i])

            for run in as_completed(mgsort):
                nextturn.append(run.result())

            ans_list = nextturn

    return ans_list[0]  # if ans_list else []


def Task3(filename, slicenum):

    outfilename = filename + "_output3.txt"

    with open(filename + ".txt", 'r') as file:
        data = [int(line.strip()) for line in file]

    sep_list = Spilt_data(data, slicenum)  # 分割數據
    # ===========================================================
    start = time.perf_counter()
    bb_list = Multi_pro_bbsort(sep_list, slicenum)
    finallist = Multi_pro_mgsort(bb_list, slicenum-1)
    totaltime = (time.perf_counter() - start) * 1000
    # ===========================================================
    # print(totaltime)  # 繳交要刪掉-------------------------------

    Writefile(outfilename, finallist, totaltime)

# merge sort不丟入BBthread，用TB當使用mergesort的跳板


def TB(sublist, q_result, BBthread):
    BBthread.acquire()  # 得到thread的使用權，is full -> wait
    temp = Bubblesort(sublist)
    q_result.put(temp)
    BBthread.release()


def TM(list1, list2, q_result, MGthread):
    MGthread.acquire()
    temp = Mergesort(list1, list2)
    q_result.put(temp)
    MGthread.release()


def Thread_bubble_sort(sep_list, max_threads):
    run = []  # run threads' list
    q_result = Queue()  # 多執行緒間安全地傳資料
    BBthread = Semaphore(max_threads)  # 計算threads數量 use, -1/ finsh, +1

    for sublist in sep_list:
        thread = Thread(target=TB, args=(sublist, q_result, BBthread))
        thread.start()  # 呼叫start()才能開始
        run.append(thread)  # 存running but not finished thread

    for thread in run:
        thread.join()  # wait for thread finish

    bb_list = [q_result.get() for _ in range(q_result.qsize())]
    return bb_list


def Thread_merge_sort(ans_list, max_threads):
    while (len(ans_list) > 1):
        run = []
        q_result = Queue()
        MGthread = Semaphore(max_threads)
        new_sorted_lists = []

        for i in range(0, len(ans_list), 2):
            if (i + 1 < len(ans_list)):
                thread = Thread(target=TM, args=(
                    ans_list[i], ans_list[i+1], q_result, MGthread))
                thread.start()
                run.append(thread)
            else:
                new_sorted_lists.append(ans_list[i])

        for thread in run:
            thread.join()

        new_sorted_lists += [q_result.get() for _ in range(q_result.qsize())]
        ans_list = new_sorted_lists

    return ans_list[0]


def Task4(filename, slicenum):

    outfilename = filename + "_output4.txt"

    with open(filename + ".txt", 'r') as file:
        data = [int(line.strip()) for line in file]

    sep_list = Spilt_data(data, slicenum)  # 分割數據
    # ===========================================================
    start = time.perf_counter()
    bb_list = Thread_bubble_sort(sep_list, slicenum)
    finallist = Thread_merge_sort(bb_list, slicenum-1)
    totaltime = (time.perf_counter() - start) * 1000
    # ===========================================================
    # print(totaltime)  # 繳交要刪掉-------------------------------

    Writefile(outfilename, finallist, totaltime)


def main():
    filename = input('請輸入檔案名稱:\n')
    currentfile = os.listdir('.')

    exixt = (filename + ".txt") in currentfile
    if (exixt == False):
        print("Could not read file:", filename + ".txt")
        return

    slicenum = int(input('請輸入要切成幾份:\n'))
    tasknum = input('請輸入方法編號:(方法1, 方法2, 方法3, 方法4)\n')

    # f = open(filename, "r")

    if (tasknum == '1'):
        Task1(filename)
    elif (tasknum == '2'):
        Task2(filename, slicenum)
    elif (tasknum == '3'):
        Task3(filename, slicenum)
    elif (tasknum == '4'):
        Task4(filename, slicenum)
    else:
        print("wrong task number")


if __name__ == '__main__':
    main()
