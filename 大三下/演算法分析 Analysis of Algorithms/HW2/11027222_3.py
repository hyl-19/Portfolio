# 演算法分析機測
# 學號: 11027222 / 11027234 / 11027254
# 姓名: 黃彥霖 / 邱宥文 / 方璿瑞
# 中原大學資訊工程系

import time
import heapq
from collections import OrderedDict


class Node:
    def __init__(self, char, freq):
        self.char = char
        self.freq = freq
        self.left = None
        self.right = None

    def __lt__(self, other):
        return self.freq < other.freq


def encode(frequencies):
    heap = []
    for i in frequencies:
        heap.append(Node(i, frequencies[i]))
    heapq.heapify(heap)
    while len(heap) > 1:
        left = heapq.heappop(heap)
        right = heapq.heappop(heap)
        merged = Node(None, left.freq + right.freq)
        merged.left = left
        merged.right = right
        heapq.heappush(heap, merged)

    root = heap[0]
    codes = {}
    buildHuffmanTree(root, "", codes)
    return codes


def buildHuffmanTree(node, code, codes):
    if node.char is not None:
        codes[node.char] = code
        return
    buildHuffmanTree(node.left, code + "0", codes)
    buildHuffmanTree(node.right, code + "1", codes)


def decode(codes, encoded_str):
    reverse_codes = {}
    for i in codes:
        reverse_codes[codes[i]] = i
    current_code = ""
    decoded_str = ""
    for digit in encoded_str:
        current_code += digit
        if current_code in reverse_codes:
            decoded_str += reverse_codes[current_code]
            current_code = ""
    return decoded_str


def main():
    num = int(input())
    answer = []
    while num != 0:
        frequencies = {}
        for i in range(num):
            str = input()
            str = str.split(' ')
            frequencies[str[0]] = int(str[1])
        codes = encode(frequencies)
        encoded_str = input()

        start_time = time.time()
        codes = OrderedDict(sorted(codes.items()))
        answer.append((codes, encoded_str))

        num = int(input())

    for i in answer:
        for j in i[0]:
            print(f"{j} = {i[0][j]}")
        print(f"Decode = {decode(i[0], i[1])}\n")

        total_time = time.time() - start_time
        print("time: ", total_time)


if __name__ == "__main__":

    main()
