#include <vector>
#include "../../utility/csr.h"
#include "../../utility/bfs.h"
#include "graph_algorithms.h"

using namespace std;

void betweennessCentrality(Csr& csr, vector<double>& centrality) {
    int V = csr.csrGraph.numVertices;
    centrality.assign(V, 0.0);
    for (int s = 0; s < V; s++) {
        vector<int> distances;
        vector<int> traversal;
        bfs(csr, s, distances, traversal);
        vector<vector<int>> P(V);           // Predecessors list
        vector<double> sigma(V, 0.0);       // Shortest path count
        vector<double> delta(V, 0.0);       // Dependency score
        sigma[s] = 1.0;
        for (int v : traversal) {
            int start = csr.csrGraph.rowPtr[v];
            int end = csr.csrGraph.rowPtr[v + 1];
            for (int i = start; i < end; i++) {
                int w = csr.csrGraph.colIdx[i];
                if (distances[w] == distances[v] + 1) {
                    sigma[w] += sigma[v];
                    P[w].push_back(v);
                }
            }
        }
        for (int i = traversal.size() - 1; i >= 0; i--) {
            int w = traversal[i];
            for (int v : P[w]) {
                if (sigma[w] != 0.0) { // Math safety check
                    delta[v] += (sigma[v] / sigma[w]) * (1.0 + delta[w]);
                }
            }
            if (w != s) {
                centrality[w] += delta[w];
            }
        }
    }
    for (int i = 0; i < V; i++) {
        centrality[i] /= 2.0;
    }
}