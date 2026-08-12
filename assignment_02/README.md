# CS509 Shared Buddy Assignments Repo

## Repository Overview
This repository contains shared implementations for CS509 Lab Work completed in pairs (Double/Buddy mode).

## Student Details
* **Student 1 Name:** Arshdeep Singh
* **Entry Number 1:** 2026AIM1004
* **Student 2 Name:** Ishtveer Singh Billing
* **Entry Number 2:** 2026AIM1007
* **Assignment Type:** Double / Buddy

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
`-- assignment_02_graph_analytics/
    |-- src/
    |   |-- csr.h
    |   |-- csr.cpp
    |   |-- triangle_counting.h
    |   |-- triangle_counting.cpp
    |   |-- betweenness_centrality.h
    |   |-- betweenness_centrality.cpp
    |   |-- connected_components.h
    |   `-- connected_components.cpp
    |-- driver/
    |   `-- driver.cpp
    |-- tests/
    |   |-- tc_10.txt
    |   |-- tc_100.txt
    |   |-- tc_10000.txt
    |   |-- tc_50000.txt
    |   |-- tc_100000.txt
    |   |-- bc_10.txt
    |   |-- bc_100.txt
    |   |-- bc_1000.txt
    |   |-- bc_5000.txt
    |   |-- bc_10000.txt
    |   |-- cc_10.txt
    |   |-- cc_100.txt
    |   |-- cc_10000.txt
    |   |-- cc_50000.txt
    |   `-- cc_100000.txt
    `-- outputs/
        |-- tc_out_10.txt
        |-- bc_out_10.txt
        |-- cc_out_10.txt
        `-- ...
```

## Common Wrapper: Build and Usage
The root `wrapper.cpp` serves as the shared repo-level interface to compile drivers and run selected test cases across assignments.

### Compilation
```bash
make run
```

### Execution
```bash
./wrapper
```

---

## Assignment 02: Graph Analytics (Triangle Counting, Betweenness Centrality, Connected Components)

### Assignment Mode
Double / Buddy

### Objective
Implement structural graph analysis algorithms on unweighted, undirected graphs using Compressed Sparse Row (CSR) format:
1. Triangle Counting using neighbor list intersections.
2. Betweenness Centrality using Brandes' Algorithm.
3. Connected Components labeling via BFS/DFS or Union-Find.

### Algorithm / Approach
1. **Triangle Counting:** Sorts neighbor lists in CSR representation to perform efficient common-neighbor checks for connected pairs. Divides total discovery count by 3.
2. **Betweenness Centrality:** Computes unnormalized Brandes' centrality for unweighted graphs by running BFS from all source vertices and accumulating shortest path dependencies.
3. **Connected Components:** Uses graph traversal (BFS/DFS) or Disjoint Set Union (DSU) to assign unique sequential component IDs to all vertices.

### Input Format
Unweighted Undirected Adjacency List text files specifying $V$ and $E$, where each undirected edge is explicitly listed in both endpoint neighbor lists.

### Helper Functions / CSR Conversion
Pre-processes adjacency lists into CSR format (`row_ptr`, `col_idx`) before timer invocation. Neighbor lists are pre-sorted for optimized triangle counting intersections.

### File Structure
* `csr.h` / `csr.cpp`: Adjacency list to CSR conversion and sorting routines.
* `triangle_counting.h` / `triangle_counting.cpp`: Intersection-based triangle counting logic.
* `betweenness_centrality.h` / `betweenness_centrality.cpp`: Brandes' centrality algorithm.
* `connected_components.h` / `connected_components.cpp`: Component identification routines.
* `driver.cpp`: Dedicated driver module for input validation, CSR construction, timed execution calls, and result printing.

### Test Cases and Result Table

| Algorithm | Test File | Vertices ($V$) | Edges ($E$) | Expected Output | Actual Output | Time | Status |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| Triangle Counting | `tc_10.txt` | 10 | | Total Triangles | Total Triangles | 0 ms | PASSED |
| Triangle Counting | `tc_100.txt` | 100 | | Total Triangles | Total Triangles | 0 ms | PASSED |
| Triangle Counting | `tc_10000.txt` | 10000 | | Total Triangles | Total Triangles | 4.6 ms | PASSED |
| Triangle Counting | `tc_50000.txt` | 50000 | | Total Triangles | Total Triangles | 30.6 ms | PASSED |
| Triangle Counting | `tc_100000.txt` | 100000 | | Total Triangles | Total Triangles | 100.557 ms | PASSED |
| Betweenness Centrality | `bc_10.txt` | 10 | | Centrality per vertex | Centrality per vertex | 0 ms | PASSED |
| Betweenness Centrality | `bc_100.txt` | 100 | | Centrality per vertex | Centrality per vertex | 0.992 ms | PASSED |
| Betweenness Centrality | `bc_1000.txt` | 1000 | | Centrality per vertex | Centrality per vertex | 73.399 ms | PASSED |
| Betweenness Centrality | `bc_5000.txt` | 5000 | | Centrality per vertex | Centrality per vertex | 2117.65 ms | PASSED |
| Betweenness Centrality | `bc_10000.txt` | 10000 | | Centrality per vertex | Centrality per vertex | 9775.45 ms | PASSED |
| Connected Components | `cc_10.txt` | 10 | | Component per vertex | Component per vertex | 0 ms | PASSED |
| Connected Components | `cc_100.txt` | 100 | | Component per vertex | Component per vertex | 1 ms | PASSED |
| Connected Components | `cc_10000.txt` | 10000 | | Component per vertex | Component per vertex | 13 ms | PASSED |

### Complexity
* **Triangle Counting:** Time Complexity: $\mathcal{O}(E \cdot \Delta)$ where $\Delta$ is max degree, Auxiliary Space: $\mathcal{O}(V + E)$
* **Betweenness Centrality:** Time Complexity: $\mathcal{O}(V \cdot E)$, Auxiliary Space: $\mathcal{O}(V + E)$
* **Connected Components:** Time Complexity: $\mathcal{O}(V + E)$, Auxiliary Space: $\mathcal{O}(V)$
