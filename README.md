# CS509 Laboratory Repository

## Repository Overview
Buddy Assignments Repository for CS509 - PG Software Lab M.Tech AI 2026-27.

## Student / Pair Details
2026AIM1004 - Arshdeep Singh
2026AIM1007 - Ishtveer Singh Billing

## Language and Environment
C++

## Directory Structure
assignment_01/
|-- src/
|-- driver/
|-- tests/
|   |-- test_01.txt
|   |-- test_02.txt
|   `-- test_03.txt
|-- outputs/
|-- README.md

## Common Wrapper: Build and Usage
(Not yet implemented)

## Assignment 01 - BFS, DFS and SSSP
### Objective
Program and execute BFS, DFS and SSSP and record their execution times.

### Algorithm / Approach
BFS - Using Queue
DFS - Using Stack
SSSP - Djikstra algorithm, Using priority Queue

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

### Helper Functions / CSR Conversion (if applicable)
CSR Conversion is done using csr.cpp and csr.h file.
The csr format of three arrays, along with number of vertices, edges and the source vertex are combined to be in a single structure CsrGraph.
Class Csr is used to define functions that convert the input txt file, depending on whether it is weighted or not.
The functions convert (overloading) take in filepath as input and fill the struct with correct values.

### File Structure
#### src/
bfs.cpp
dfs.cpp
sssp.cpp
csr.cpp
csr.h
graph_algorithms.h

#### driver/
driver.cpp

#### tests/
bfs_10.txt
bfs_50.txt
bfs_100.txt
dfs_10.txt
dfs_50.txt
dfs_100.txt
sssp_10.txt
sssp_50.txt
sssp_100.txt

#### outputs/

### Compilation
g++ driver.cpp ..\src\bfs.cpp ..\src\dfs.cpp ..\src\sssp.cpp ..\src\csr.cpp -o driver

### Execution
./driver

### Test Cases and Result Table
| Algorithm | Test File | Vertices | Edges | Input Type | Source | Expected Output | Actual Output | Time | Status |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| BFS | `bfs_10.txt` | 10 | ... | Unweighted adjacency list converted to CSR | ... | Traversal / distances | ... | ... ms | Pass |
| BFS | `bfs_50.txt` | 10 | ... | Unweighted adjacency list converted to CSR | ... | Traversal / distances | ... | ... ms | Pass |
| BFS | `bfs_100.txt` | 10 | ... | Unweighted adjacency list converted to CSR | ... | Traversal / distances | ... | ... ms | Pass |
| BFS | `bfs_50.txt` | 10 | ... | Unweighted adjacency list converted to CSR | ... | Traversal / distances | ... | ... ms | Pass |
| BFS | `bfs_100.txt` | 10 | ... | Unweighted adjacency list converted to CSR | ... | Traversal / distances | ... | ... ms | Pass |
| DFS | `dfs_10.txt` | 10 | ... | Unweighted adjacency list converted to CSR | ... | Traversal | ... | ... ms | Pass |
| DFS | `dfs_50.txt` | 10 | ... | Unweighted adjacency list converted to CSR | ... | Traversal | ... | ... ms | Pass |
| DFS | `dfs_100.txt` | 10 | ... | Unweighted adjacency list converted to CSR | ... | Traversal| ... | ... ms | Pass |
| DFS | `dfs_50.txt` | 10 | ... | Unweighted adjacency list converted to CSR | ... | Traversal | ... | ... ms | Pass |
| DFS | `dfs_100.txt` | 10 | ... | Unweighted adjacency list converted to CSR | ... | Traversal| ... | ... ms | Pass |
| SSSP | `sssp_10.txt` | 10 | ... | Positive weighted adjacency list converted to CSR | ... | Shortest distances | ... | ... ms | Pass |
| SSSP | `sssp_50.txt` | 10 | ... | Positive weighted adjacency list converted to CSR | ... | Shortest distances | ... | ... ms | Pass |
| SSSP | `sssp_100.txt` | 10 | ... | Positive weighted adjacency list converted to CSR | ... | Shortest distances | ... | ... ms | Pass |
| SSSP | `sssp_100.txt` | 10 | ... | Positive weighted adjacency list converted to CSR | ... | Shortest distances | ... | ... ms | Pass |
| SSSP | `sssp_100.txt` | 10 | ... | Positive weighted adjacency list converted to CSR | ... | Shortest distances | ... | ... ms | Pass |


### Complexity

**Breadth-First Search (BFS) & Depth-First Search (DFS)**
*   **Time Complexity:** $O(V + E)$, where $V$ is the number of vertices and $E$ is the number of edges. We visit every vertex and explore every edge exactly once.
*   **Space Complexity:** $O(V + E)$ to store the graph in Compressed Sparse Row (CSR) format. The auxiliary space for the Queue (in BFS) or Stack (in DFS) and the visited arrays is $O(V)$. Overall Space Complexity is $O(V + E)$.

**Single-Source Shortest Path (SSSP) - Dijkstra's Algorithm**
*   **Time Complexity:** $O((V + E) \log V)$. Using a min-priority queue allows us to extract the minimum distance vertex in $O(\log V)$ time, and each edge relaxation takes $O(\log V)$ time.
*   **Space Complexity:** $O(V + E)$ to store the weighted graph in CSR format. The priority queue and distance tracking arrays require $O(V)$ auxiliary space. Overall Space Complexity is $O(V + E)$.

### References