#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include "csr.h"

using namespace std;
const int INF = numeric_limits<int>::max();

void sssp(const Csr& graph, vector<int>& distances) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> forSssp;
    distances.assign(graph.csrGraph.numVertices, INF);
    int source = graph.csrGraph.sourceVertex;
    distances[source] = 0;
    forSssp.push({0, source});
    
    while (!forSssp.empty()) {
        int currentDist = forSssp.top().first;
        int vertice = forSssp.top().second;
        forSssp.pop();
        if (currentDist > distances[vertice]) {
            continue;
        }
        int neighbors = graph.csrGraph.rowPtr[vertice + 1] - graph.csrGraph.rowPtr[vertice];
        for (int i = graph.csrGraph.rowPtr[vertice]; i < graph.csrGraph.rowPtr[vertice] + neighbors; i++) {
            int neighbor = graph.csrGraph.colIdx[i];
            int weight = graph.csrGraph.values[i];
            if (distances[vertice] + weight < distances[neighbor]) {
                distances[neighbor] = distances[vertice] + weight;
                forSssp.push({distances[neighbor], neighbor});
            }
        }
    }
}