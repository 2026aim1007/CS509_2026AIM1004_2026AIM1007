#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include "csr.h"

using namespace std;
const int INF = numeric_limits<int>::max();

void bfs(const Csr& graph, vector<int>& distances, vector<int>& traversal) {

    queue<int> forBfs;
    distances.assign(graph.csrGraph.numVertices, INF);
    int distance = 0;

    forBfs.push(graph.csrGraph.sourceVertex);
    distances[graph.csrGraph.sourceVertex] = 0;
    do {
        int vertice, neighbors;
        vertice = forBfs.front();
        forBfs.pop();
        traversal.push_back(vertice);
        
        neighbors = graph.csrGraph.rowPtr[vertice + 1] - graph.csrGraph.rowPtr[vertice];

        for (int i = graph.csrGraph.rowPtr[vertice]; i < graph.csrGraph.rowPtr[vertice] + neighbors; i++) {
            int neighbor = graph.csrGraph.colIdx[i];
            
            if (distances[neighbor] == INF) {
                forBfs.push(neighbor);
                distances[neighbor] = distances[vertice] + 1;
            }
        }
        
    }while (!(forBfs.empty()));
}