# CS509 Laboratory Repository

## Repository Overview
Buddy Assignments Repository for CS509 - PG Software Lab M.Tech AI 2026-27.

## Student / Pair Details
2026AIM1004 - Arshdeep Singh
2026AIM1007 - Ishtveer Singh Billing

## Language and Environment
C++ Language
g++ compiler
GNU Make

## Directory Structure
```text
CS509_CS1001_AI1002/
|-- common_wrapper/
|   `-- common_wrapper.cpp
|-- assignment_01/
|   |-- src/
|   |-- driver/
|   |-- tests/
|   |   |-- unweighted10.txt
|   |   |-- unweighted100.txt
|   |   |-- unweighted10000.txt
|   |   `-- ...
|   `-- outputs/
|       |-- output_bfs_10.txt
|       |-- output_bfs_100.txt
|       `-- ...
|-- Makefile
`-- README.md
```

## Common Wrapper: Build and Usage
Wrapper is the main program which is used to choose and run the algorithm of choice on input file from any folder.

## Assignment 01 - BFS, DFS and SSSP
### Objective
Program and execute BFS, DFS and SSSP and record their execution times.

### Algorithm / Approach
BFS is implemented using Queue
DFS is implemented using Stack
SSSP, used Djikstra algorithm since the graph weights were positive, using priority Queue
The input file in the format of adjacency list gets converted to CSR format using helper function. From there any algorithm that runs uses the CSR encoding of graph.

### Input Format
Text files in the following format:

#### For Unweighted Adjacency-List
V E
u0 degree neighbor1 neighbor2 ...
u1 degree neighbor1 neighbor2 ...
...
u(V-1) degree neighbor1 neighbor2 ...
SOURCE s
V: number of vertices.
E: number of edges. For an undirected graph, count each graph edge once in E even though it appears in both adjacency lists.
u: vertex whose adjacency list is being written.
degree: number of neighbours listed after u.
s: source vertex for BFS or DFS.

#### For weighted Adjacency-List
V E
u0 degree neighbor1 weight1 neighbor2 weight2 ...
u1 degree neighbor1 weight1 neighbor2 weight2 ...
...
u(V-1) degree neighbor1 weight1 neighbor2 weight2 ...
SOURCE s

### Helper Functions / CSR Conversion
CSR Conversion is done using csr.cpp and csr.h file.
The csr format of three arrays, along with number of vertices, edges and the source vertex are combined to be in a single structure CsrGraph.
Class Csr is used to define functions that convert the input txt file, depending on whether it is weighted or not.
The functions convert (overloading) take in filepath as input and fill the struct with correct values.

Graph_algorithms header file contains the initialization of all 3 graph algorithms, with each algorithm implemented in seperate file.


### Compilation
To compile all source files (`driver.cpp`, `csr.cpp`, `bfs.cpp`, `dfs.cpp`, `sssp.cpp`) and generate the executable, run:

```bash
make
```
### Execution
./driver_app

### Test Cases and Result Table
| Algorithm | Test File | Vertices | Edges | Input Type | Source | Expected Output | Actual Output | Time | Status |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| BFS | `unweighted10.txt` | 10 | 10 | Unweighted adjacency list converted to CSR | 0 | `expected_bfs_10.txt` | `output_bfs_10.txt` | 0 ms | Pass |
| BFS | `unweighted100.txt` | 100 | 100 | Unweighted adjacency list converted to CSR | 0 | `expected_bfs_100.txt` | `output_bfs_100.txt` | 0 ms | Pass |
| BFS | `unweighted10000.txt` | 10000 | 10000 | Unweighted adjacency list converted to CSR | 0 | `expected_bfs_10000.txt` | `output_bfs_10000.txt` | 1 ms | Pass |
| BFS | `unweighted50000.txt` | 50000 | 50000 | Unweighted adjacency list converted to CSR | 0 | `expected_bfs_50000.txt` | `output_bfs_50000.txt` | 13 ms | Pass |
| BFS | `unweighted100000.txt` | 100000 | 100000 | Unweighted adjacency list converted to CSR | 0 | `expected_bfs_100000.txt` | `output_bfs_100000.txt` | 26 ms | Pass |
| DFS | `unweighted10.txt` | 10 | 10 | Unweighted adjacency list converted to CSR | 0 | `expected_dfs_10.txt` | `output_dfs_10.txt` | 0 ms | Pass |
| DFS | `unweighted100.txt` | 100 | 100 | Unweighted adjacency list converted to CSR | 0 | `expected_dfs_100.txt` | `output_dfs_100.txt` | 0 ms | Pass |
| DFS | `unweighted10000.txt` | 10000 | 10000 | Unweighted adjacency list converted to CSR | 0 | `expected_dfs_10000.txt` | `output_dfs_10000.txt` | 3 ms | Pass |
| DFS | `unweighted50000.txt` | 50000 | 50000 | Unweighted adjacency list converted to CSR | 0 | `expected_dfs_50000.txt` | `output_dfs_50000.txt` | 17 ms | Pass |
| DFS | `unweighted100000.txt` | 100000 | 100000 | Unweighted adjacency list converted to CSR | 0 | `expected_dfs_100000.txt` | `output_dfs_100000.txt` | 34 ms | Pass |
| SSSP | `sssp10.txt` | 10 | 10 | Positive weighted adjacency list converted to CSR | 0 | `expected_sssp_10.txt` | `output_sssp_10.txt` | 0 ms | Pass |
| SSSP | `sssp100.txt` | 100 | 100 | Positive weighted adjacency list converted to CSR | 0 | `expected_sssp_100.txt` | `output_sssp_100.txt` | 0 ms | Pass |
| SSSP | `sssp10000.txt` | 10000 | 10000 | Positive weighted adjacency list converted to CSR | 0 | `expected_sssp_10000.txt` | `output_sssp_10000.txt` | 19 ms | Pass |
| SSSP | `sssp50000.txt` | 50000 | 50000 | Positive weighted adjacency list converted to CSR | 0 | `expected_sssp_50000.txt` | `output_sssp_50000.txt` | 113 ms | Pass |
| SSSP | `sssp100000.txt` | 100000 | 100000 | Positive weighted adjacency list converted to CSR | 0 | `expected_sssp_100000.txt` | `output_sssp_100000.txt` | 231 ms | Pass |

### System Specification
Processor: AMD Ryzen 7 5800H
RAM: 16 GB
Storage: 512 GB

### Complexity

**Breadth-First Search (BFS) & Depth-First Search (DFS)**
*   **Time Complexity:** $O(V + E)$, where $V$ is the number of vertices and $E$ is the number of edges. We visit every vertex and explore every edge exactly once.
*   **Space Complexity:** $O(V + E)$ to store the graph in Compressed Sparse Row (CSR) format. The auxiliary space for the Queue (in BFS) or Stack (in DFS) and the visited arrays is $O(V)$. Overall Space Complexity is $O(V + E)$.

**Single-Source Shortest Path (SSSP) - Dijkstra's Algorithm**
*   **Time Complexity:** $O((V + E) \log V)$. Using a min-priority queue allows us to extract the minimum distance vertex in $O(\log V)$ time, and each edge relaxation takes $O(\log V)$ time.
*   **Space Complexity:** $O(V + E)$ to store the weighted graph in CSR format. The priority queue and distance tracking arrays require $O(V)$ auxiliary space. Overall Space Complexity is $O(V + E)$.
