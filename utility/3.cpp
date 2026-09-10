#include <iostream>
#include <vector>
#include <cmath>
#include "../../utility/csr.h"
#include "../../utility/bfs.h" // Assuming you have your old BFS

using namespace std;

// Assuming these structs/functions exist in your headers:
struct Edge { int u, v, weight; };
long long kruskalMST(const Csr& graph, vector<Edge>& mstEdges);
long long primMST(const Csr& graph, vector<Edge>& mstEdges);
struct MFMC { long long maxFlow; long long minCutCapacity; };
MFMC maxFlowMinCut(Csr& csr);
void vertexColoring(const CsrGraph& graph, vector<int>& colors, int& numColorsUsed);

void performAllValidations(Csr& csrGraphData) {
    cout << "========================\nGraph Validation\n========================\n";

    // ==============================================================================
    // VALIDATION 1: Kruskal <-> Prim (Assignment 3)
    // ==============================================================================
    vector<Edge> kruskalEdges, primEdges;
    long long kWeight = kruskalMST(csrGraphData, kruskalEdges);
    long long pWeight = primMST(csrGraphData, primEdges);
    
    bool mstPass = (kWeight == pWeight) && (kruskalEdges.size() == csrGraphData.csrGraph.numVertices - 1);
    cout << "Kruskal <-> Prim:      " << (mstPass ? "PASS" : "FAIL") << "\n";

    // ==============================================================================
    // VALIDATION 2: Max-Flow <-> Min-Cut (Assignment 3)
    // ==============================================================================
    MFMC flowResult = maxFlowMinCut(csrGraphData);
    bool flowPass = (flowResult.maxFlow == flowResult.minCutCapacity);
    cout << "MaxFlow <-> MinCut:    " << (flowPass ? "PASS" : "FAIL") << "\n";

    // ==============================================================================
    // VALIDATION 3: Vertex Coloring Validity (Assignment 4)
    // ==============================================================================
    vector<int> colors;
    int numColors;
    vertexColoring(csrGraphData.csrGraph, colors, numColors);
    
    bool coloringPass = true;
    for (int u = 0; u < csrGraphData.csrGraph.numVertices; u++) {
        for (int i = csrGraphData.csrGraph.rowPtr[u]; i < csrGraphData.csrGraph.rowPtr[u+1]; i++) {
            int v = csrGraphData.csrGraph.colIdx[i];
            if (u != v && colors[u] == colors[v]) {
                coloringPass = false; // Two adjacent nodes share the same color!
                break;
            }
        }
    }
    cout << "Vertex Coloring:       " << (coloringPass ? "PASS" : "FAIL") << "\n";

    // ==============================================================================
    // VALIDATION 4: K-Means Monotonicity (Assignment 4)
    // ==============================================================================
    // To do this, you would modify your kMeans loop to store WCSS in a vector:
    // vector<double> wcssHistory; 
    // bool kMeansPass = true;
    // for (size_t i = 1; i < wcssHistory.size(); i++) {
    //     if (wcssHistory[i] > wcssHistory[i-1] + 1e-9) { 
    //         kMeansPass = false; // WCSS went UP, which violates K-Means math
    //         break;
    //     }
    // }
    // cout << "K-Means Monotonicity:  " << (kMeansPass ? "PASS" : "FAIL") << "\n";

    cout << "========================\n";
    if (mstPass && flowPass && coloringPass) {
        cout << "Overall:               PASS\n";
    } else {
        cout << "Overall:               FAIL\n";
    }
    cout << "========================\n";
}