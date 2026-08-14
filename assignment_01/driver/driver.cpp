#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <limits>

#include "../src/csr.h"
#include "../src/graph_algorithms.h"
#include "../../utility/testing_utils.h" 

using namespace std;
const int INF = numeric_limits<int>::max();

int main(int argc, char* argv[]) {
    int choice;
    string runMode = "ALL";
    bool isBenchmarkMode = false;
    if (argc >= 3) {
        choice = stoi(argv[1]);
        runMode = argv[2];
        if (argc >= 4 && string(argv[3]) == "--test") {
            isBenchmarkMode = true;
        }
    } else {
        cout << "=================================================\n";
        cout << "      CS509 Graph Algorithms Automated Driver    \n";
        cout << "=================================================\n\n";
        
        cout << "Select Algorithm to Run:\n";
        cout << "1. BFS (Breadth-First Search)\n";
        cout << "2. DFS (Depth-First Search)\n";
        cout << "3. SSSP (Single-Source Shortest Path - Dijkstra)\n";
        cout << "Enter choice (1-3): ";
        cin >> choice;
        
        char modeFlag;
        cout << "Run in Benchmark mode? (y/n - averages 5 runs): ";
        cin >> modeFlag;
        if (modeFlag == 'y' || modeFlag == 'Y') isBenchmarkMode = true;
        cout << "\n";
    }

    if (choice < 1 || choice > 3) {
        cout << "Invalid choice. Exiting.\n";
        return 1;
    }
    int iterations = isBenchmarkMode ? 5 : 1;
    vector<string> graphSizes;
    if (runMode == "ALL") {
        graphSizes = {"10", "100", "10000", "50000", "100000"};
    } else {
        graphSizes = {runMode};
    }
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
        if (isWeighted) {
            graph.convert(testFilePath, true);
        } else {
            graph.convert(testFilePath);
        }
        if (graph.csrGraph.numVertices == 0) {
            cout << "  [!] Error: Could not load graph from " << testFilePath << "\n\n";
            continue;
        }
        vector<int> traversal;
        vector<int> distances;
        double avgTimeMs = 0.0;
        if (choice == 1) {
            auto algoLambda = [&]() {
                traversal.clear();
                distances.clear();
                bfs(graph, distances, traversal);
            };
            avgTimeMs = measureAverageExecutionTime(algoLambda, iterations);
        } else if (choice == 2) {
            auto algoLambda = [&]() {
                traversal.clear();
                dfs(graph, traversal);
            };
            avgTimeMs = measureAverageExecutionTime(algoLambda, iterations);
        } else if (choice == 3) {
            auto algoLambda = [&]() {
                distances.clear();
                sssp(graph, distances);
            };
            avgTimeMs = measureAverageExecutionTime(algoLambda, iterations);
        }
        ofstream outFile(outFilePath);
        if (!outFile.is_open()) {
            cout << "  [!] Error: Could not create output file.\n\n";
            continue;
        }
        int source = graph.csrGraph.sourceVertex;
        if (choice == 1) {
            outFile << "Algorithm: BFS\nSource: " << source << "\nTraversal: ";
            for (int v : traversal) { 
                outFile << v << " "; 
            }
            outFile << "\nDistances:\n";
            for (size_t i = 0; i < distances.size(); i++) {
                outFile << i << " " << distances[i] << "\n";
            }
        } 
        else if (choice == 2) {
            outFile << "Algorithm: DFS\nSource: " << source << "\nTraversal: ";
            for (int v : traversal) { 
                outFile << v << " "; 
            }
            outFile << "\n"; 
        } 
        else if (choice == 3) {
            outFile << "Algorithm: SSSP\nSource: " << source << "\nVertex\tDistance\n";
            for (size_t i = 0; i < distances.size(); i++) {
                if (distances[i] == INF) {
                    outFile << i << "\tINF\n"; 
                } else {
                    outFile << i << "\t" << distances[i] << "\n"; 
                }
            }
        }
        outFile << "\n" << METRICS_ESCAPE_TOKEN << "\n";
        outFile << "Execution time: " << avgTimeMs << " ms\n";
        if (isBenchmarkMode) outFile << "(Averaged over " << iterations << " runs)\n";
        outFile.close();
        cout << "--- " << algoName << " TEST SUMMARY (" << sizeStr << " Vertices) ---\n";
        if (compareFilesWithEscape(outFilePath, expectedFilePath)) {
            cout << "Status: PASSED\n";
        } else {
            cout << "Status: FAILED (Check " << outFilePath << " against expected)\n";
        }
        cout << (isBenchmarkMode ? "Avg Time: " : "Time: ") << avgTimeMs << " ms\n";
        cout << "=================================================\n\n";
    }
    return 0;
}