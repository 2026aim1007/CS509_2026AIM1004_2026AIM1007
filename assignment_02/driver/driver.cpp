#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>

#include "../../utility/csr.h"
#include "../../utility/testing_utils.h"
#include "../src/graph_algorithms.h"

using namespace std;

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
        cout << "      CS509 Assgn 2 Driver (TC-Unopt, TC-Opt, BC, CC)\n";
        cout << "=================================================\n\n";
        cout << "Select Algorithm:\n";
        cout << "1. Triangle Counting (Unoptimized)\n";
        cout << "2. Triangle Counting (Optimized)\n";
        cout << "3. Betweenness Centrality (BC)\n";
        cout << "4. Connected Components (CC)\n";
        cout << "Enter choice (1-4): ";
        cin >> choice;
        char modeFlag;
        cout << "Run in Benchmark mode? (y/n - averages 5 runs): ";
        cin >> modeFlag;
        if (modeFlag == 'y' || modeFlag == 'Y') isBenchmarkMode = true;
    }

    if (choice < 1 || choice > 4) {
        cout << "Invalid choice. Exiting.\n";
        return 1;
    }
    int iterations = isBenchmarkMode ? 5 : 1;
    vector<string> graphSizes;
    if (runMode == "ALL") {
        if (choice == 3) {
            graphSizes = {"10", "100", "1000", "5000", "10000"}; 
        } else {
            graphSizes = {"10", "100", "10000", "50000", "100000"};
        }
    } else {
        graphSizes = {runMode};
    }

    for (const string& sizeStr : graphSizes) {
        cout << "\n>>> Running Test Case: " << sizeStr << " Vertices <<<\n";
        string algoPrefix = (choice == 1 || choice == 2) ? "tc" : (choice == 3) ? "bc" : "cc";
        string testPath = "tests/" + algoPrefix + "_" + sizeStr + ".txt";
        string outPath = "outputs/output_" + algoPrefix + "_" + sizeStr + ".txt";
        string expPath = "outputs/expected_" + algoPrefix + "_" + sizeStr + ".txt";
        Csr graph;
        graph.convert(testPath, false);
        if (graph.csrGraph.numVertices == 0) { 
            cout << "  [!] Error: Could not load " << testPath << "\n";
            continue;
        }
        double avgTimeMs = 0.0;
        ofstream outFile(outPath);
        if (choice == 1) {
            vector<vector<int>> triangles;
            int total = 0;
            auto algoLambda = [&]() { 
                triangles.clear(); 
                total = triangleCountingUnopt(graph, triangles); 
            };
            avgTimeMs = measureAverageExecutionTime(algoLambda, iterations);
            outFile << "Algorithm: Triangle Counting\nTotal triangles: " << total << "\n";
            if (sizeStr == "10" || sizeStr == "100") {
                outFile << "Triangles found:\n";
                for (const auto& t : triangles) outFile << "(" << t[0] << ", " << t[1] << ", " << t[2] << ")\n";
            }
        } 
        else if (choice == 2) {
            vector<vector<int>> triangles;
            int total = 0;
            auto algoLambda = [&]() { 
                triangles.clear(); 
                total = triangleCountingOpt(graph, triangles); 
            };
            avgTimeMs = measureAverageExecutionTime(algoLambda, iterations);
            outFile << "Algorithm: Triangle Counting\nTotal triangles: " << total << "\n";
            if (sizeStr == "10" || sizeStr == "100") {
                outFile << "Triangles found:\n";
                for (const auto& t : triangles) outFile << "(" << t[0] << ", " << t[1] << ", " << t[2] << ")\n";
            }
        }
        else if (choice == 3) {
            vector<double> centrality;
            auto algoLambda = [&]() { betweennessCentrality(graph, centrality); };
            avgTimeMs = measureAverageExecutionTime(algoLambda, iterations);
            outFile << "Algorithm: Betweenness Centrality\nVertex Centrality\n";
            outFile << fixed << setprecision(2);
            for (size_t i = 0; i < centrality.size(); i++) outFile << i << " " << centrality[i] << "\n";
        } 
        else if (choice == 4) {
            vector<int> components;
            int numComps = 0;
            auto algoLambda = [&]() { numComps = connectedComp(graph, components); };
            avgTimeMs = measureAverageExecutionTime(algoLambda, iterations);
            outFile << "Algorithm: Connected Components\nNumber of components: " << numComps << "\n";
            outFile << "Vertex Component\n";
            for (size_t i = 0; i < components.size(); i++) outFile << i << " " << components[i] << "\n";
        }
        outFile << "\n" << METRICS_ESCAPE_TOKEN << "\n";
        outFile << "Execution time: " << avgTimeMs << " ms\n";
        if (isBenchmarkMode) outFile << "(Averaged over " << iterations << " runs)\n";
        outFile.close();
        cout << "--- " << algoPrefix << " TEST SUMMARY ---\n";
        if (compareFilesWithEscape(outPath, expPath)) {
            cout << "Status: PASSED\n";
        } else {
            cout << "Status: FAILED (Check " << outPath << " against expected)\n";
        }
        cout << (isBenchmarkMode ? "Avg Time: " : "Time: ") << avgTimeMs << " ms\n";
    }
    return 0;
}