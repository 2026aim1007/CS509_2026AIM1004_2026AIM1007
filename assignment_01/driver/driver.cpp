#include <iostream>
#include <string>
#include <chrono>
#include <fstream>
#include <vector>
#include <limits>

#include "../src/csr.h"
#include "../src/graph_algorithms.h"

using namespace std;
using namespace std::chrono;
const int INF = numeric_limits<int>::max();

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
    cout << "=================================================\n";
    cout << "      CS509 Graph Algorithms Automated Driver    \n";
    cout << "=================================================\n\n";
    
    cout << "Select Algorithm to Run:\n";
    cout << "1. BFS (Breadth-First Search)\n";
    cout << "2. DFS (Depth-First Search)\n";
    cout << "3. SSSP (Single-Source Shortest Path - Dijkstra)\n";
    cout << "Enter choice (1-3): ";
    
    int choice;
    cin >> choice;
    cout << "\n";
    
    if (choice < 1 || choice > 3) {
        cout << "Invalid choice. Exiting.\n";
        return 1;
    }
    vector<string> graphSizes = {"10", "100", "10000", "50000", "100000"};
    for (const string& sizeStr : graphSizes) {
        cout << ">>> Running Test Case: " << sizeStr << " Vertices <<<\n";
        string testFilePath, outFilePath, expectedFilePath, algoName;
        bool isWeighted = false;

        if (choice == 1) {
            algoName = "BFS";
            testFilePath = "tests/unweighted" + sizeStr + ".txt";
            outFilePath = "outputs/output_bfs_" + sizeStr + ".txt";
            expectedFilePath = "outputs/expected_bfs_" + sizeStr + ".txt";
        } else if (choice == 2) {
            algoName = "DFS";
            testFilePath = "tests/unweighted" + sizeStr + ".txt";
            outFilePath = "outputs/output_dfs_" + sizeStr + ".txt";
            expectedFilePath = "outputs/expected_dfs_" + sizeStr + ".txt";
        } else if (choice == 3) {
            algoName = "SSSP";
            isWeighted = true;
            testFilePath = "tests/sssp" + sizeStr + ".txt";
            outFilePath = "outputs/output_sssp_" + sizeStr + ".txt";
            expectedFilePath = "outputs/expected_sssp_" + sizeStr + ".txt";
        }

        Csr graph;
        graph.convert(testFilePath, isWeighted);
        if (graph.csrGraph.numVertices == 0) {
            cout << "  [!] Error: Could not load graph from " << testFilePath << "\n\n";
            continue;
        }

        vector<int> traversal;
        vector<int> distances;
        auto start = high_resolution_clock::now();
        if (choice == 1) {
            // bfs(graph, traversal, distances);
        } else if (choice == 2) {
            dfs(graph, traversal);
        } else if (choice == 3) {
            sssp(graph, distances);
        }
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);
        ofstream outFile(outFilePath);
        if (!outFile.is_open()) {
            cout << "  [!] Error: Could not create output file.\n\n";
            continue;
        }
        int source = graph.csrGraph.sourceVertex;
        bool printToTerminal = (sizeStr == "10" || sizeStr == "100");
        if (!printToTerminal) {
            cout << "(Graph is too large to print to terminal. Writing results directly to " << outFilePath << "...)\n";
        }
        if (choice == 1) {
            outFile << "Algorithm: BFS\nSource: " << source << "\nTraversal: ";
            if (printToTerminal) cout << "Algorithm: BFS\nSource: " << source << "\nTraversal: ";
            for (int v : traversal) { 
                outFile << v << " "; 
                if (printToTerminal) cout << v << " "; 
            }
            outFile << "\nDistances:\n";
            if (printToTerminal) cout << "\nDistances:\n";
            for (size_t i = 0; i < distances.size(); i++) {
                outFile << i << " " << distances[i] << "\n";
                if (printToTerminal) cout << i << " " << distances[i] << "\n";
            }
        } 
        else if (choice == 2) {
            outFile << "Algorithm: DFS\nSource: " << source << "\nTraversal: ";
            if (printToTerminal) cout << "Algorithm: DFS\nSource: " << source << "\nTraversal: ";
            for (int v : traversal) { 
                outFile << v << " "; 
                if (printToTerminal) cout << v << " "; 
            }
            outFile << "\n"; 
            if (printToTerminal) cout << "\n";
        } 
        else if (choice == 3) {
            outFile << "Algorithm: SSSP\nSource: " << source << "\nVertex\tDistance\n";
            if (printToTerminal) cout << "Algorithm: SSSP\nSource: " << source << "\nVertex\tDistance\n";
            for (size_t i = 0; i < distances.size(); i++) {
                if (distances[i] == INF) {
                    outFile << i << "\tINF\n"; 
                    if (printToTerminal) cout << i << "\tINF\n";
                } else {
                    outFile << i << "\t" << distances[i] << "\n"; 
                    if (printToTerminal) cout << i << "\t" << distances[i] << "\n";
                }
            }
        }
        
        outFile.close();
        cout << "--- " << algoName << " TEST SUMMARY (" << sizeStr << " Vertices) ---\n";
        if (compareFiles(outFilePath, expectedFilePath)) {
            cout << "Status: PASSED\n";
        } else {
            cout << "Status: FAILED\n";
            cout << "Reason: " << outFilePath << " does not match expected output.\n";
        }
        cout << "Execution time: " << duration.count() << " ms\n";
        cout << "=================================================\n\n";
    }
    return 0;
}