#include <iostream>
#include <string>
#include <chrono>

#include "../src/csr.h"
#include "../src/graph_algorithms.h"

using namespace std;
using namespace std::chrono;

int main() {
    string testFilePath = "../tests/test_01.txt";
    cout << "--- CS509 Graph Algorithms Driver ---\n";
    cout << "Test file selected: " << testFilePath << "\n\n";
    cout << "Select Algorithm to Run:\n";
    cout << "1. BFS (Breadth-First Search)\n";
    cout << "2. DFS (Depth-First Search)\n";
    cout << "3. SSSP (Single-Source Shortest Path - Dijkstra)\n";
    cout << "Enter choice (1-3): ";
    
    int choice;
    cin >> choice;
    cout << "\n";
    Csr graph;
    if (choice == 1 || choice == 2) {
        graph.convert(testFilePath);
    } else if (choice == 3) {
        graph.convert(testFilePath, true);
    } else {
        cout << "Invalid choice. Exiting.\n";
        return 1;
    }
    auto start = high_resolution_clock::now();
    if (choice == 1) {
        bfs(graph);
    } else if (choice == 2) {
        dfs(graph);
    } else if (choice == 3) {
        sssp(graph);
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "Execution time: " << duration.count() << " ms\n";
    return 0;
}