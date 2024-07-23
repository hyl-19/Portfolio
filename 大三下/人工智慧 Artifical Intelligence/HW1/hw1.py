import matplotlib.pyplot as plt
import numpy as np
from queue import PriorityQueue


def read_maze(file_path):
    with open(file_path, 'r') as file:
        maze = [list(line.strip().split()) for line in file.readlines()]
    return maze


def find_special_positions(maze):
    special_positions = {}
    for i, row in enumerate(maze):
        for j, cell in enumerate(row):
            if cell in "SGABCDEF":
                special_positions[cell] = (i, j)
    return special_positions


def heuristic(a, b):
    return abs(a[0] - b[0]) + abs(a[1] - b[1])


def a_star_search(maze, start, goal):
    neighbors = [(0, 1), (1, 0), (0, -1), (-1, 0)]
    frontier = PriorityQueue()
    frontier.put((0, start))
    came_from = {start: None}
    cost_so_far = {start: 0}
    while not frontier.empty():
        current = frontier.get()[1]
        if current == goal:
            break
        for next_step in neighbors:
            next = (current[0] + next_step[0], current[1] + next_step[1])
            if 0 <= next[0] < len(maze) and 0 <= next[1] < len(maze[0]) and maze[next[0]][next[1]] != '#':
                new_cost = cost_so_far[current]
                if maze[next[0]][next[1]] not in "SGABCDEF":
                    new_cost += int(maze[next[0]][next[1]])
                if next not in cost_so_far or new_cost < cost_so_far[next]:
                    cost_so_far[next] = new_cost
                    priority = new_cost + heuristic(goal, next)
                    frontier.put((priority, next))
                    came_from[next] = current
    return came_from, cost_so_far


def reconstruct_path(came_from, start, goal):
    current = goal
    path = []
    while current != start:
        path.append(current)
        current = came_from[current]
    path.append(start)
    path.reverse()
    return path


def plot_maze_with_path(maze, path, output_image):
    nrows, ncols = len(maze), len(maze[0])
    fig, ax = plt.subplots()
    maze_array = np.zeros((nrows, ncols, 3))
    for r in range(nrows):
        for c in range(ncols):
            if maze[r][c] == '#':
                maze_array[r, c] = [0, 0, 0]  # Black for walls
            else:
                # White background for numbers and path
                maze_array[r, c] = [1, 1, 1]

    for (x, y) in path:
        maze_array[x, y] = [0.8, 0.8, 1]  # Light blue for correct path

    ax.imshow(maze_array)

    for r in range(nrows):
        for c in range(ncols):
            if maze[r][c] not in ['#', '*']:
                # Black font color for numbers
                ax.text(c, r, maze[r][c], ha='center',
                        va='center', color='black')

    # Add arrows along the path
    for i in range(len(path)-1):
        (x1, y1), (x2, y2) = path[i], path[i+1]
        dx, dy = x2 - x1, y2 - y1
        ax.arrow(y1, x1, dy, dx, head_width=0.2,
                 head_length=0.2, fc='red', ec='red')

    ax.axis('off')
    plt.savefig(output_image, bbox_inches='tight')
    plt.close()


def main(maze_file, output_image):
    maze = read_maze(maze_file)
    special_positions = find_special_positions(maze)
    full_path = []

    order = ['A', 'B', 'C', 'D', 'E', 'F', 'G']
    start = special_positions['S']
    total_steps = 0
    for goal_label in order:
        goal = special_positions[goal_label]
        came_from, _ = a_star_search(maze, start, goal)
        if goal not in came_from:  # Check if the goal was reached
            # Prints "No appropriate path" if a path to the goal was not found
            print("無適當路徑")
            return  # Terminate the function early
        path_segment = reconstruct_path(came_from, start, goal)
        if full_path:
            path_segment = path_segment[1:]
        full_path += path_segment
        start = goal
        total_steps += len(path_segment)

    # Subtract 1 because 'S' to 'A' is counted twice
    print("Total number of steps:", total_steps - 1)
    plot_maze_with_path(maze, full_path, output_image)


if __name__ == "__main__":
    main("maze.txt", "path.png")
