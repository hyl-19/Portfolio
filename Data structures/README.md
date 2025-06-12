# Data Structures Course Repository

A comprehensive collection of assignments and implementations for a Data Structures course. Organized into themed modules, each folder contains mission specifications, reference materials, and C++ implementations.

---

## Table of Contents

1. [Module: 1\_Recursion](#module-1_recursion)
2. [Module: 2\_ADT Implementation](#module-2_adt-implementation)
3. [Module: 3\_Linked List](#module-3_linked-list)
4. [Module: 4\_Stack Implementation](#module-4_stack-implementation)
5. [Module: 5\_Sorting](#module-5_sorting)
6. [Module: 6\_Binary Tree](#module-6_binary-tree)

---

## Module: 1\_Recursion

Folder `1_Recursion` explores recursive approaches to permutation generation and the Tower of Hanoi challenge.

### Mission Specifications

* **mission1.pdf**: Generate all permutations of numbers from 1 to N and report count.
* **mission2.pdf**: Prompt for M unique integers (2–9), generate permutations, measure execution time.
* **mission3.pdf**: Permute the first M elements of the sequence 1–9, measure execution time.

Refer to the PDF files for detailed requirements and sample inputs/outputs.

### Solution: Recursion\_hanoi.cpp

Key features:

* `Generate_permutations`: Full-length permutations of a sequence.
* `Permutations_Limit` & `Permutations_Challenge`: Customized permutation lengths and ranges.
* Input validation (`IsDigit`, `CheckSame`).
* Performance timing using `clock()`.
* Interactive menu for choosing missions (1–4).

### How to Run

**Follow Prompts**:

   * Enter mission choice (1–4).
   * Provide required inputs (N, M, etc.) as specified.

Output includes each permutation, total count, and execution time for timed missions.

---

## Module: 2\_ADT Implementation

Folder `2_ADT Implementation` focuses on file object manipulation through classes and basic operations.

### Mission Specifications

The missions are defined in the provided flowchart (`flowchart.pdf`):

1. **COPY**: Read from `inputXXX.txt`, parse records into a `Data` class, and write entries (skipping headers) to `copyXXX.txt`.
2. **FILTER**: From `copyXXX.txt`, select records meeting minimum student and graduate thresholds, saving results back to `copyXXX.txt`.
3. **MERGE**: Merge two datasets (e.g., `copyXXX.txt` and `copyYYY.txt`) preserving grouping by college and department, output to `outputXXX_YYY.txt`.

Refer to `flowchart.pdf` for detailed flow charts of each mission.

### Solution: ADT.cpp

Key features:

* **`Data` class**: Encapsulates row parsing (`GetString`, `FixNum`, `GetLineOfData`).
* **Input Validation**: `IsDigit` and filename parsing (`CheckFileName`).
* **File Operations**: `mission1()`, `mission2()`, `mission3()` implement COPY, FILTER, MERGE workflows.
* **Data Merging**: `InsertData` orders merged records by college/department.
* **User Menu**: Interactive selection of commands (0–3).

Results are written to `copyXXX.txt` or `outputXXX_YYY.txt` with record counts displayed.

---

## Module: 3\_Linked List

Folder `3_Linked List` covers infix/postfix/prefix conversion and evaluation of arithmetic expressions using a linked-list-based stack.

### Mission Specifications

* **m1檢查錯誤.pdf**: Validate infix expression syntax (characters, parentheses, operator count).
* **m2InfixtoPostfix.pdf**: Convert valid infix expressions to postfix notation. 
* **m3計算後序式.pdf**: Evaluate postfix expressions and handle division-by-zero errors. 

Refer to the PDF files in `3_Linked List` for detailed requirements and examples.

### Solution: Linked List.cpp & (P)Linked List.cpp

Key features:

* **Linked-list Stack**: `Node`, `Push`, `Pop`, `Clear`, `Print` operations.
* **Error Detection**: `ErrorOfChar`, `ErrorOfParentheses`, `ErrorOfOperator`, combined in `FindError`.
* **Conversion**: `ToPostFix` and `InfixToPreFix` for infix↔postfix/prefix.
* **Evaluation**: `CalculatePostfix` and `CalculatePrefix`, with operand and operator handling.
* **Interactive Menu**: Missions 1–2 for conversion and evaluation.



## Module: 4\_Stack Implementation

Folder `4_Stack Implementation` implements stack operations and mission workflows based on LIFO structures.

### Mission Specifications

Refer to `Stack.pdf` for detailed tasks:

* **mission1**: Read job orders from file, perform Shell sort on arrival times with tie-breakers on order ID, and output sorted list.
* **mission2**: Simulate job processing with a single chef, using a queue of size 3, track aborts and timeouts, and record total delays and failure percentages.
* **mission3**: Extend simulation to two chefs with individual queues, dispatch jobs optimally, and produce reports for one- and two-chef scenarios.

### Solution: Stack.cpp

Key features:

* **`JobList`, `Queue`, `Work`, `Cook` classes**: Encapsulate order data, queue operations, and chef assignment logic.
* **Sorting**: Shell sort with primary key `arrival`, secondary key `OID`.
* **Simulation**: Single- and multi-chef workflows, abort/timeout handling, delay/failure computation.
* **File I/O**: Read `inputXXX.txt`, write results to `oneXXX.txt`, `twoXXX.txt`, and print timing statistics.



## Module: 5\_Sorting

Folder `5_Sorting` benchmarks various sorting algorithms on graduate data.

### Mission Specifications

Tasks include:

1. **Selection Sort**
2. **Bubble Sort**
3. **Merge Sort**
4. **Quick Sort**
5. **Radix Sort**

Measure execution time of each sort and record results in `sort_time.txt`.

### Solution: sorting.cpp

Key features:

* **`Data` class**: Parses graduate count from input files, handles CSV formatting.
* **Sorting implementations**: `bubble_sort()`, `select_sort()`, `merge_sort()`, `quick_sort()`, and `radix_sort()`.
* **Timing utility**: Uses `clock()` to measure each algorithm's runtime and appends to `sort_time.txt`.
* **Reporting**: Prints sorted data and timing summary.



## Module: 6\_Binary Tree

Folder `6_Binary Tree` builds a height-balanced BST on Pokémon HP and supports queries and deletions.

### Mission Specifications

Refer to `Binary Tree.pdf` for tasks:

1. **Build Tree**: Read Pokémon data, construct BST keyed by HP, allowing duplicates.
2. **Height Query**: Report tree height.
3. **Threshold Search**: Find and display all nodes with `hp >= threshold`, counting visited nodes.
4. **Delete Max**: Remove the node(s) with maximum HP, display deleted entries and new height.

### Solution: Binary Tree.cpp

Key features:

* **`File`, `BST`, `Node` classes**: File I/O, in-memory BST with vector at each node for handling ties.
* **Tree construction**: `build()` inserts data, `buildBalanced()` creates a balanced tree from sorted array.
* **Traversals**: In-order for building, recursive height calculation, conditional search, and deletion.
* **Interactive menu**: Missions 1–4, with prompts for file code and thresholds.
