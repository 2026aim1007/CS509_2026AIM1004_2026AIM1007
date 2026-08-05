#include <iostream>
#include <string>
#include <chrono>
#include <fstream>

#include "../src/csr.h"
#include "../src/graph_algorithms.h"

using namespace std;
using namespace std::chrono;

// Helper to compare files word-by-word
bool compareFiles(const string& p1, const string& p2) {
    ifstream f1(p1), f2(p2);
    if (!f1.is_open() || !f2.is_open()) return false;
    string w1, w2;
    
    while (f1 >> w1 && f2 >> w2) {
        if (w1 != w2) return false;
    }
    return (bool)(f1 >> w1) == (bool)(f2 >> w2);
}

int main() {
    string testFilePath = "../tests/test_01.txt";
    string outFilePath = "../outputs/output_01.txt";
    string expectedFilePath = "../outputs/expected_01.txt";

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

    ofstream outFile(outFilePath);
    if (!outFile.is_open()) {
        cout << "Error: Could not create output file. Does the 'outputs' folder exist?\n";
        return 1;
    }
    streambuf* originalCoutBuffer = cout.rdbuf();
    cout.rdbuf(outFile.rdbuf());
    auto start = high_resolution_clock::now();
    if (choice == 1) {
        bfs(graph);
    } else if (choice == 2) {
        dfs(graph);
    } else if (choice == 3) {
        sssp(graph);
    }
    auto stop = high_resolution_clock::now();
    cout.rdbuf(originalCoutBuffer);
    outFile.close();

    ifstream readOut(outFilePath);
    if (readOut.is_open()) {
        cout << readOut.rdbuf();
        readOut.close();
    }

    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "Execution time: " << duration.count() << " ms\n\n";

    if (compareFiles(outFilePath, expectedFilePath)) {
        cout << "--- TEST CASE HAS PASSED ---\n";
    } else {
        cout << "--- TEST CASE HAS FAILED ---\n";
    }
    return 0;
}