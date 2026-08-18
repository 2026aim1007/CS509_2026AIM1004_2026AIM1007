# CS509 Shared Buddy Assignments Specific Repo

## Student Details
* **Student 1 Name:** Arshdeep Singh
* **Entry Number 1:** 2026AIM1004
* **Student 2 Name:** Ishtveer Singh Billing
* **Entry Number 2:** 2026AIM1007

## Language and Environment
* **Programming Language:** C++
* **Compiler:** `g++` 
* **Timing Method:** `std::chrono::high_resolution_clock`

## Directory Structure
```text
CS509_2026AIM1004_2026AIM1005/
|-- README.md
|-- common_wrapper/
|   `-- wrapper.cpp
`-- assignment_03/
    |-- src/
    |   |-- gradientDescent.h
    |   |-- gradientDescent.cpp
    |   |-- maxflowMincut.h
    |   |-- maxflowMincut.cpp
    |-- driver/
    |   `-- driver.cpp
    |-- tests/
    |   |-- gd_01.txt
    |   |-- gd_02.txt
    |   |-- gd_03.txt
    |   |-- gd_04.txt
    |   |-- gd_05.txt
    |   |-- maxflow_10.txt
    |   |-- maxflow_100.txt
    |   |-- maxflow_1000.txt
    |   |-- maxflow_50000.txt
    |   `-- maxflow_100000.txt
    `-- outputs/
    |   |-- output_gd_10.txt
    |   |-- expected_gd_10.txt
    |   |-- output_maxflow_10.txt
    |   |-- expected_maxflow_10.txt
    |   `-- ...
    |--Makefile
    |--README.md
```

## Assignment 03: Gradient Descent and Max-Flow Min-Cut Graph

### Objective
Implement a structural graph algorithm using Compressed Sparse Row (CSR) format alongside a polynomial numerical optimization algorithm:
1. **Gradient Descent:** Optimization of generic one-variable polynomial functions $f(x) = \sum_{i=0}^d c_i x^i$.
2. **Maxflow-Mincut:** Maximum flow computation and residual graph reachability for $s$-$t$ minimum cut on directed capacity CSR graphs (using Dinic's algorithm recommended).

### Algorithm / Approach
1. **Gradient Descent:** Computes numerical minimums for generic $d$-degree polynomial functions $f(x)$ using analytical derivative $f'(x) = \sum_{i=1}^d i \cdot c_i x^{i-1}$. Iteratively updates $x_{new} = x - \alpha f'(x)$ until $|f'(x)| \le \epsilon$ or the maximum iteration limit is met. 
Stops when |f'(x)| <= tolerance, or when the maximum number of iterations has been reached.

2. **Maxflow-Mincut:** Computes the maximum $s$-$t$ network flow from source $s$ to sink $t$ without exceeding edge capacities. Extracts the minimum $s$-$t$ cut from the final residual graph by performing graph traversal to find all vertices reachable from $s$. Solved using Dinic's algorithm, in which the high level procedure goes as follows: First building a level graph using bfs, which will help dfs traverse the shortest edges to reach sink. Then dfs is applied on a single fixed level graph, until no more paths can be augmented (essentially in the main residual graph, augmenting means passing flow via a certain path from source to sink). This keeps happening until a level graph cannot be built using bfs. The above steps help calculate max flow. For minimum cut capacity, the final residual graph is used, by performing bfs on it and finding partitions by traversing edges from source where the difference between capacity adn flow is > 0, ultimately finding and comparing that the max flow is equal to the min cut (based on theorem). This algorithm uses current pointer optimization, which skips dead-end edges.

### Input Format
Text files in the following formats:

#### For Directed Capacity Adjacency-List (Maxflow-Mincut)
```text
V E
u0 degree neighbor1 capacity1 neighbor2 capacity2 ...
u1 degree neighbor1 capacity1 neighbor2 capacity2 ...
...
u(V-1) degree neighbor1 capacity1 neighbor2 capacity2 ...
SOURCE s
SINK t
```
* **V:** Number of vertices.
* **E:** Number of directed capacity edges.
* **s, t:** Source and sink vertex IDs.

#### For Polynomial Optimization (Gradient Descent)
```text
DEGREE d
COEFFICIENTS c0 c1 c2 ... cd
INITIAL_X x0
LEARNING_RATE alpha
TOLERANCE epsilon
MAX_ITERATIONS n
```
* **d:** Polynomial degree.
* **c0...cd:** $d+1$ floating-point coefficients in ascending power order.

### Helper Functions / CSR Conversion
Pre-processes adjacency lists into CSR format (`row_ptr`, `col_idx`, `values`) before invoking timers for Maxflow-Mincut routines. Gradient Descent reads parameters directly and bypasses CSR. Execution timing begins **only after** CSR creation is completed.

### File Structure
* `csr.h` / `csr.cpp`: Adjacency list to CSR conversion routines (reused from Assignment 1/2).
* `testing_utils.h` / `testing_utils.cpp`: Function to calculate time of various algorithms.
* `gradientDescent.cpp`: Generic variable-degree polynomial Gradient Descent solver.
* `maxflowMincut.cpp`: Maxflow and $s$-$t$ min-cut residual reachability solver (e.g., Dinic's Algorithm).
* `driver.cpp`: Dedicated driver module for input parsing, validation, CSR setup, timing measurements, and output display.

---

### Test Cases and Result Tables

#### 1. Gradient Descent
| File | Degree | Initial $x_0$ | Rate ($ lpha$) | Tol ($\epsilon$) | Max Iter. | Exp. $x^*$ | Exp. $f(x^*)$ | Actual $x$ | Actual $f(x)$ | Iter. / Time | Status |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| `gd_01.txt` | 2 | 0 | 0.10 | 1e-6 | 5,000 | 3 | 0 | 3.000000 | 0.000000 | 71 / 0.003040 ms | PASSED |
| `gd_02.txt` | 4 | 2 | 0.02 | 1e-6 | 10,000 | 0 | 0 | 0.000000 | 0.000000 | 181 / 0.022380 ms | PASSED |
| `gd_03.txt` | 6 | 2 | 0.02 | 1e-6 | 20,000 | 0 | 0 | 0.000000 | 0.000000 | 350 / 0.044680 ms | PASSED |
| `gd_04.txt` | 8 | 2 | 0.01 | 1e-8 | 50,000 | 0 | 0 | 0.000000 | 0.000000 | 949 / 0.529040 ms | PASSED |
| `gd_05.txt` | 10 | 2 | 0.005 | 1e-10 | 100,000 | 0 | 0 | 0.000000 | 0.000000 | 2365 / 0.494220 ms | PASSED |

#### 2. Maxflow-Mincut
| File | Vertices ($V$) | Edges ($E$) | Source ($s$) | Sink ($t$) | Exp. Flow | Actual Flow | Cut Capacity | Time | Status |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| `maxflow_10.txt` | 10 | 40 | 0 | 9 | 117 | 117 | 117 |  ms | PASSED |
| `maxflow_100.txt` | 100 | 400 | 0 | 99 | 201 | 201 | 201 | 0.45 ms | PASSED |
| `maxflow_1000.txt` | 1000 | 4000 | 0 | 999 | 94 | 94 | 94 | 4.81 ms | PASSED |
| `maxflow_10000.txt` | 10000 | 70000 | 0 | 9999 | 17579 | 17579 | 17579 | 62.30 ms | PASSED |
| `maxflow_50000.txt` | 50000 | 350000 | 0 | 49999 | 7543 | 7543 | 7543 | 412.10 ms | PASSED |
| `maxflow_100000.txt` | 100000 | 700000 | 0 | 99999 | 21901 | 21901 | 21901 |  ms | PASSED |

---

### System Specification
Processor: AMD Ryzen 7 5800H
RAM: 16 GB
Storage: 512 GB

### Complexity
* **Gradient Descent:** Time Complexity: $\mathcal{O}(I \cdot d)$ where $I$ is total iterations and $d$ is polynomial degree, Auxiliary Space: $\mathcal{O}(d)$
* **Maxflow-Mincut (Dinic's Algorithm):** Time Complexity: $\mathcal{O}(V^2 E)$, Auxiliary Space: $\mathcal{O}(V + E)$