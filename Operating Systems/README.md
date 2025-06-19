# Operating Systems Assignments

**Development Environment**: Windows 11, Visual Studio Code

## 📘 HW1: Multi-strategy Sorting with Python

### Language: Python 3.10.1  
### Description:
This project implements four different methods for sorting integer datasets with different parallelization strategies:

- **Task 1**: Single-process Bubble Sort
- **Task 2**: Single-process Split Bubble + Merge Sort
- **Task 3**: Multi-processing Split Bubble + Merge Sort
- **Task 4**: Multi-threading Split Bubble + Merge Sort

### Optimization:
- Used `@jit` (Numba) to accelerate sorting.
- Introduced swap flags in Bubble Sort for early termination.

### Observations:
- Multi-process (Task 3) showed best performance on large data.
- Threads in Python (Task 4) were limited by GIL.
- Bubble Sort scales poorly on large input size.

---

## 📘 HW2: CPU Scheduling Simulation in C++

### Language: C++  
### Description:
This program simulates four CPU scheduling algorithms:

1. **FCFS**: First Come First Serve
2. **SJF**: Shortest Job First
3. **SRTF**: Shortest Remaining Time First (Preemptive)
4. **RR**: Round Robin (Time Quantum)

### Features:
- Parses input file for process data.
- Simulates scheduling and calculates key metrics:
  - Waiting Time
  - Turnaround Time
  - Response Time
- Outputs detailed logs and summaries for each algorithm.

### Execution:
Compile with a C++11-compatible compiler and run with appropriate input format.

---

## 📘 HW3: Page Replacement Algorithm Comparison

### Language: C++  
### Description:
Implements and compares 5 page replacement strategies:

1. **FIFO**
2. **LRU**
3. **LFU+FIFO**
4. **MFU+FIFO**
5. **LFU+LRU**
6. **ALL**: Executes all methods

### Data Structures Used:
- `unordered_set`: page frame
- `unordered_map`: access counters
- `queue`: order tracking

### Output:
- Number of page faults
- Number of replacements
- Belady’s Anomaly examples

### Results Summary:
- **LFU+LRU** generally had the lowest page fault and replacement counts.
- **FIFO** susceptible to Belady’s Anomaly.
- Performance varies based on input patterns.

---

## 🔧 How to Run

### HW1:
```bash
python os1.py input_file K method
```

### HW2:
```bash
g++ os2.cpp -o os2
./os2 input.txt
```

### HW3:
```bash
g++ os3.cpp -o os3
./os3
```

---

## 📝 Reports
Detailed PDF/Word reports are included in each folder with algorithm explanations, experimental results, and charts.
