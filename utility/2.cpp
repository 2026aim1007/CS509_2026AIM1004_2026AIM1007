#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include "../../utility/csr.h"

using namespace std;

// ==============================================================================
// OPTIMIZATION A: K-Means++ Initialization
// ==============================================================================
vector<vector<double>> initKMeansPlusPlus(const vector<vector<double>>& points, int k) {
    int n = points.size();
    int d = points[0].size();
    vector<vector<double>> centroids;
    
    // 1. Pick the first centroid completely randomly
    centroids.push_back(points[rand() % n]);
    
    // 2. Iteratively pick the remaining K-1 centroids
    for (int c = 1; c < k; c++) {
        double maxMinDist = -1.0;
        int bestPointIdx = 0;
        
        for (int i = 0; i < n; i++) {
            // Find distance from point i to its *closest* existing centroid
            double minDistToCentroid = 1e15;
            for (const auto& centroid : centroids) {
                double distSq = 0;
                for (int j = 0; j < d; j++) {
                    double diff = points[i][j] - centroid[j];
                    distSq += diff * diff;
                }
                minDistToCentroid = min(minDistToCentroid, distSq);
            }
            
            // We want the point that is farthest away from all existing centroids
            if (minDistToCentroid > maxMinDist) {
                maxMinDist = minDistToCentroid;
                bestPointIdx = i;
            }
        }
        centroids.push_back(points[bestPointIdx]);
    }
    return centroids;
}

// ==============================================================================
// OPTIMIZATION B: Pull-Based PageRank (Using Transposed Graph)
// ==============================================================================
CsrGraph transposeDirectedCSR(const CsrGraph& graph) {
    int V = graph.numVertices;
    CsrGraph tGraph;
    tGraph.numVertices = V;
    tGraph.numEdges = graph.numEdges;
    tGraph.rowPtr.assign(V + 1, 0);
    tGraph.colIdx.assign(graph.numEdges, 0);
    
    // 1. Count incoming degrees
    vector<int> inDegree(V, 0);
    for (int i = 0; i < graph.numEdges; i++) {
        inDegree[graph.colIdx[i]]++;
    }
    
    // 2. Set row pointers for transposed graph
    for (int i = 0; i < V; i++) {
        tGraph.rowPtr[i + 1] = tGraph.rowPtr[i] + inDegree[i];
    }
    
    // 3. Populate incoming edges
    vector<int> currentOffset = tGraph.rowPtr;
    for (int u = 0; u < V; u++) {
        for (int i = graph.rowPtr[u]; i < graph.rowPtr[u+1]; i++) {
            int v = graph.colIdx[i]; // Edge u -> v
            tGraph.colIdx[currentOffset[v]++] = u; // Store as v <- u
        }
    }
    return tGraph;
}

void pullPageRank(const CsrGraph& inGraph, const vector<int>& originalOutDegrees, double d, double tol, int maxIter) {
    int V = inGraph.numVertices;
    vector<double> ranks(V, 1.0 / V);
    vector<double> next_ranks(V, 0.0);
    
    for(int iter = 0; iter < maxIter; iter++) {
        double dangling_sum = 0.0;
        for (int i = 0; i < V; i++) {
            if (originalOutDegrees[i] == 0) dangling_sum += ranks[i];
        }
        double base = (1.0 - d) / V + (dangling_sum * d) / V;
        
        // PULL logic: Look at incoming edges to calculate my own rank
        for (int v = 0; v < V; v++) {
            double sum_in = 0.0;
            for (int i = inGraph.rowPtr[v]; i < inGraph.rowPtr[v+1]; i++) {
                int u = inGraph.colIdx[i]; // u points to v
                sum_in += ranks[u] / originalOutDegrees[u];
            }
            next_ranks[v] = base + d * sum_in;
        }
        
        // Check convergence (omitted for brevity)
        ranks = next_ranks;
    }
}