#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>

#include "../src/gradientDescent.h"
#include "../../utility/testing_utils.h"
#include "../../utility/csr.h"
#include "../src/maxflowMincut.h"

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
        cout << "      CS509 Assignment 3 Automated Driver        \n";
        cout << "=================================================\n\n";
        cout << "Select Algorithm:\n";
        cout << "1. Gradient Descent\n";
        cout << "2. Maxflow-Mincut\n";
        cout << "Enter choice (1-2): ";
        cin >> choice;
        char modeFlag;
        cout << "Run in Benchmark mode? (y/n - averages 5 runs): ";
        cin >> modeFlag;
        if (modeFlag == 'y' || modeFlag == 'Y') isBenchmarkMode = true;
        cout << "\n";
    }
    if (choice < 1 || choice > 2) {
        cout << "Invalid choice. Exiting.\n";
        return 1;
    }
    int iterations = isBenchmarkMode ? 5 : 1;
    if (choice == 1) {
        vector<string> testCases = (runMode == "ALL") ? vector<string>{"01", "02", "03", "04", "05"} : vector<string>{runMode};
        for (const string& testNum : testCases) {
            cout << ">>> Running Test Case: gd_" << testNum << " <<<\n";
            string testFilePath = "tests/gd_" + testNum + ".txt";
            string outFilePath = "outputs/output_gd_" + testNum + ".txt";
            ifstream inFile(testFilePath);
            if (!inFile.is_open()) {
                cout << "  [!] Error: Could not load " << testFilePath << "\n\n";
                continue;
            }
            string label;
            int degree = 0, max_iterations = 0;
            double initial_x = 0.0, learning_rate = 0.0, tolerance = 0.0;
            vector<double> coeffs;
            inFile >> label >> degree; 
            inFile >> label; 
            coeffs.resize(degree + 1);
            for (int i = 0; i <= degree; ++i) inFile >> coeffs[i]; 
            inFile >> label >> initial_x;    
            inFile >> label >> learning_rate; 
            inFile >> label >> tolerance;     
            inFile >> label >> max_iterations;
            inFile.close();
            double final_x = 0.0, final_fx = 0.0;
            int actual_iterations = 0;
            bool converged = false;
            auto algoLambda = [&]() {
                runGradientDescent(coeffs, initial_x, learning_rate, tolerance, max_iterations, final_x, final_fx, actual_iterations, converged);
            };
            double avgTimeMs = measureAverageExecutionTime(algoLambda, iterations);
            ofstream outFile(outFilePath);
            if (outFile.is_open()) {
                outFile << "Algorithm: Gradient Descent\n";
                outFile << "Degree: " << degree << "\n";
                outFile << fixed << setprecision(6);
                outFile << "Final x: approximately " << final_x << "\n";
                outFile << "Final f(x): approximately " << final_fx << "\n";
                outFile << "Iterations: " << actual_iterations << "\n";
                outFile << "Converged: " << (converged ? "true" : "false") << "\n";
                outFile << "\n" << METRICS_ESCAPE_TOKEN << "\n";
                outFile << "Execution time: " << avgTimeMs << " ms\n";
                if (isBenchmarkMode) outFile << "(Averaged over " << iterations << " runs)\n";
                outFile.close();
            }

            cout << "--- Gradient Descent TEST SUMMARY (gd_" << testNum << ") ---\n";
            string expectedFilePath = "outputs/expected_gd_" + testNum + ".txt";
            if (compareFilesWithEscape(outFilePath, expectedFilePath)) {
                cout << "Status: PASSED\n";
            } else {
                cout << "Status: FAILED (Check " << outFilePath << " against expected)\n";
            }
            cout << "Degree: " << degree << " | Iterations: " << actual_iterations << " | Converged: " << (converged ? "true" : "false") << "\n";
            cout << (isBenchmarkMode ? "Avg Time: " : "Time: ") << avgTimeMs << " ms\n";
            cout << "=================================================\n\n";
        }
    }
    else if (choice == 2) {
        vector<string> testCases = (runMode == "ALL") ? vector<string>{"10", "100", "1000", "10000", "50000", "100000"} : vector<string>{runMode};
        for (const string& testNum : testCases) {
            cout << ">>> Running Test Case: maxflow_" << testNum << " <<<\n";
            string testFilePath = "tests/maxflow_" + testNum + ".txt";
            string outFilePath = "outputs/output_maxflow_" + testNum + ".txt";

            Csr csr;
            csr.convert(testFilePath, true);
            auto algoLambda = [&]() {
                maxFlowMinCut(csr);
            };
            double avgTimeMs = measureAverageExecutionTime(algoLambda, iterations);

            MFMC mfmc = maxFlowMinCut(csr);
            ofstream outFile(outFilePath);
            if (outFile.is_open()) {
                outFile << "Algorithm: Maxflow-Mincut\n";
                outFile << "Source: " << csr.csrGraph.sourceVertex << "\n";
                outFile << "Sink: " << csr.csrGraph.sinkVertex << "\n";
                outFile << "Maximum flow: " << mfmc.maxFlow << "\n";
                outFile << "Minimum cut capacity: " << mfmc.minCutCapacity << "\n";
                outFile << "Source side: ";
                for (int vertice : mfmc.source) {
                    outFile << vertice << " ";
                }
                outFile << "\n";
                outFile << "Sink side: ";
                for (int vertice : mfmc.sink) {
                    outFile << vertice << " ";
                }
                outFile << "\n";
                outFile << "Cut edges:\n";
                for (auto edge : mfmc.cutEdges) {
                    outFile << edge.second.first << " " << edge.second.second << " " << edge.first << "\n";
                }
                outFile << "\n" << METRICS_ESCAPE_TOKEN << "\n";
                outFile << "Execution time: " << avgTimeMs << " ms\n";
                if (isBenchmarkMode) outFile << "(Averaged over " << iterations << " runs)\n";
                outFile.close();
            }

            cout << "--- MaxFlow-MinCut TEST SUMMARY (maxflow_" << testNum << ") ---\n";
            string expectedFilePath = "outputs/expected_maxflow_" + testNum + ".txt";
            if (compareFilesWithEscape(outFilePath, expectedFilePath)) {
                cout << "Status: PASSED\n";
            } else {
                cout << "Status: FAILED (Check " << outFilePath << " against expected)\n";
            }
            cout << "Maximum flow: " << mfmc.maxFlow << " | Minimum cut capacity: " << mfmc.minCutCapacity << " | MaxFlow equals MinCut: " << (mfmc.maxFlow == mfmc.minCutCapacity ? "true" : "false") << "\n";
            cout << (isBenchmarkMode ? "Avg Time: " : "Time: ") << avgTimeMs << " ms\n";
            cout << "=================================================\n\n";
        }
    }

    return 0;
}