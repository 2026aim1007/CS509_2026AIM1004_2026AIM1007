#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include "../utility/csr.h"

using namespace std;

// ==============================================================================
// PIPELINE A: FastMap -> K-Means (No File I/O)
// ==============================================================================
// Assuming fastMap() populates an extern/global vector<vector<double>> result;
extern vector<vector<double>> result; 

void runFastMapToKMeansPipeline(int n, int targetK_dims, int clusters, int maxIter, double tol, vector<vector<double>>& originalDistances) {
    // 1. Run FastMap to reduce distance matrix to coordinates
    fastMap(n, targetK_dims, originalDistances);
    
    // 2. The output 'result' is now an N x targetK_dims matrix.
    // Feed it directly into K-Means as the 'points' input!
    vector<int> assignments;
    vector<vector<double>> centroids;
    int actualIter;
    bool converged;
    double wcss;
    
    kMeans(n, targetK_dims, clusters, maxIter, tol, result, assignments, centroids, actualIter, converged, wcss);
    
    cout << "Pipeline successful! Final WCSS: " << wcss << "\n";
}

// ==============================================================================
// PIPELINE B: 3D Points -> K-Nearest Neighbors (KNN) -> CSR Graph
// ==============================================================================
CsrGraph buildKNNGraphFromPoints(const vector<vector<double>>& points, int k_neighbors) {
    int n = points.size();
    vector<vector<pair<double, int>>> distances(n);

    // 1. Calculate all pairwise distances
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            double distSq = 0;
            for (size_t d = 0; d < points[i].size(); d++) {
                double diff = points[i][d] - points[j][d];
                distSq += diff * diff;
            }
            distances[i].push_back({distSq, j});
        }
    }

    // 2. Build Intermediate Adjacency List for top K neighbors
    vector<vector<int>> adj(n);
    int totalEdges = 0;
    for (int i = 0; i < n; i++) {
        // Sort to find the closest k neighbors
        sort(distances[i].begin(), distances[i].end());
        for (int j = 0; j < k_neighbors && j < (int)distances[i].size(); j++) {
            adj[i].push_back(distances[i][j].second);
            totalEdges++;
        }
    }

    // 3. Convert Adjacency List to CSR
    CsrGraph knnGraph;
    knnGraph.numVertices = n;
    knnGraph.numEdges = totalEdges;
    knnGraph.rowPtr.reserve(n + 1);
    
    int index = 0;
    for (int i = 0; i < n; i++) {
        knnGraph.rowPtr.push_back(index);
        for (int neighbor : adj[i]) {
            knnGraph.colIdx.push_back(neighbor);
            index++;
        }
    }
    knnGraph.rowPtr.push_back(index);
    return knnGraph;
}