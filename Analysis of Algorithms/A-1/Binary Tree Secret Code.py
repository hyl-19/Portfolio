# 演算法分析機測
# 學號: 11027222 / 11027239 / 11027254
# 姓名: 黃彥霖 / 邱宥文 / 方璿瑞
# 中原大學資訊工程系

import time


class TreeNode():
    def __init__(self, val='', left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

    def buildTree(self, preorder, inorder):
        # 如果中序和前序序列都不為空
        if inorder and preorder:
            # 找到根節點在中序序列中的位置
            index = inorder.index(preorder.pop(0))
            # 創建根節點
            root = TreeNode(inorder[index])
            # 遞迴建立左子樹
            root.left = self.buildTree(preorder, inorder[:index])
            # 遞迴建立右子樹
            root.right = self.buildTree(preorder, inorder[index + 1:])
            return root

    def printMessage(self, root):
        if root:
            # 遞迴輸出左子樹、右子樹和根節點的值
            return self.printMessage(root.left) + self.printMessage(root.right) + (root.val)
        else:
            return ''


def main():
    cnt = 0
    preorder = ''
    inorder = ''
    answer = []
    preorder = input("輸入前序序列：")
    while preorder != '0':
        inorder = input("輸入中序序列：")
        pre_list = list(preorder)
        in_list = list(inorder)
        tree = TreeNode()
        start_time = time.time()
        # 建立二元樹
        root = tree.buildTree(pre_list, in_list)
        total_time = time.time() - start_time
        # 記錄執行時間和遍歷結果
        answer.append((total_time, tree.printMessage(root)))
        preorder = input("輸入下一組前序序列（輸入0結束）：")

    # 輸出執行時間和遍歷結果
    for x in answer:
        cnt += 1
        print(f"執行時間 {cnt}:{x[0]} 秒")
        print(x[1])


if __name__ == "__main__":
    main()
