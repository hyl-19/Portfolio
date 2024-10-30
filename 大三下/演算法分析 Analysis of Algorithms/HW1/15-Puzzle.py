# 演算法分析機測
# 學號 : 11027222 / 11027239 / 11027254
# 姓名 : 黃彥霖 / 邱宥文 / 方璿瑞
# 中原大學資訊工程系

import time


def read_puzzle_sets():  # 輸入4*4
    num_sets = int(input("Enter the number of puzzle sets: "))
    puzzle_sets = []
    for _ in range(num_sets):
        print("\nPlease enter your 4x4 puzzle, use '0' for the blank space:")
        board = []
        for i in range(4):
            row = input(f"Row {i+1}: ")
            board.append(list(map(int, row.split())))
        puzzle_sets.append(board)
    return puzzle_sets


class Puzzle:
    def __init__(self, board, moves=0, prev=None, last_move=None):
        self.board = board
        self.moves = moves
        self.prev = prev
        # Record the last move (number and direction)
        self.last_move = last_move
        self.size = len(board)  # 4
        self.blank_pos = self._find_blank()
        self.manhattan = self._manhattan_distance()

    def _find_blank(self):
        for i in range(self.size):
            for j in range(self.size):
                if self.board[i][j] == 0:
                    return i, j
        return None

    def _manhattan_distance(self):  # 計算當前拼圖狀態到目標狀態的曼哈頓距離，即所有非空白格到其目標位置的距離之和。
        distance = 0
        for i in range(self.size):
            for j in range(self.size):
                if self.board[i][j] != 0:
                    target_x, target_y = divmod(
                        self.board[i][j] - 1, self.size)
                    # 距離計算為當前位置和目標位置之間的行差和列差的絕對值之和。
                    distance += abs(target_x - i) + abs(target_y - j)
        return distance

    def is_goal(self):
        return self.manhattan == 0

    def neighbors(self):
        dirs = [(-1, 0, 'D'), (1, 0, 'U'), (0, -1, 'R'), (0, 1, 'L')]  # 上下左右
        result = []
        x, y = self.blank_pos  # 空白格的位置
        for dx, dy, move_dir in dirs:
            nx, ny = x + dx, y + dy
            if 0 <= nx < self.size and 0 <= ny < self.size:  # 還在不在裡面
                new_board = [list(row) for row in self.board]  # 一個copy
                # change
                new_board[x][y], new_board[nx][ny] = new_board[nx][ny], new_board[x][y]
                result.append(
                    (Puzzle(new_board, self.moves + 1, self), move_dir))
        return result

    def __lt__(self, other):
        return self.manhattan + self.moves < other.manhattan + other.moves


def astar_solver(initial):
    from heapq import heappush, heappop
    open_set = []
    heappush(open_set, (initial.manhattan, initial))
    visited = set()
    while open_set:
        current = heappop(open_set)[1]
        if current.is_goal():
            return current
        visited.add(tuple(map(tuple, current.board)))
        for neighbor, move_dir in current.neighbors():  # 遍歷當前狀態的所有鄰居狀態及相應的移動方向。
            if tuple(map(tuple, neighbor.board)) not in visited:
                moved_number = current.board[neighbor.blank_pos[0]
                                             ][neighbor.blank_pos[1]]
                new_neighbor = Puzzle(
                    neighbor.board, neighbor.moves, current, (moved_number, move_dir))
                heappush(open_set, (new_neighbor.manhattan +
                         new_neighbor.moves, new_neighbor))
    return None


def reconstruct_path(goal_state):  # 移動路徑
    moves = []
    current = goal_state
    while current.prev is not None:
        if current.last_move:  # Check if there is a last move
            move_number, move_dir = current.last_move
            moves.append(f"{move_number}{move_dir}")
        current = current.prev
    moves.reverse()
    return moves


def format_moves(moves):  # 印出移動路徑
    # Format and print moves, max 5 per line.
    for i in range(0, len(moves), 5):
        line = ', '.join(moves[i:i+5])
        print(line)

# Example board to test the implementation


def main():
    puzzle_sets = read_puzzle_sets()
    for i, initial_board in enumerate(puzzle_sets, start=1):
        print(f"\n15-Puzzle #{i}:")
        initial_state = Puzzle(initial_board)
        start_time = time.time()
        solution = astar_solver(initial_state)
        total_time = time.time() - start_time
        if solution:
            total_moves = solution.moves
            path = reconstruct_path(solution)
            print(f"Number of moves = {total_moves}")
            format_moves(path)
        else:
            print("No solution found.")
        print(f"time = {total_time}")


if __name__ == "__main__":
    main()

'''
2
1 2 3 4
5 6 7 8
9 10 15 11
0 13 14 12
0 1 2 3
5 6 7 4
9 10 11 8
13 14 15 12
'''
