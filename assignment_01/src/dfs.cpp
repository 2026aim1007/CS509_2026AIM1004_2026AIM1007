#include <iostream>
#include <vector>
#include "csr.h"

using namespace std;

void dfsHelper(int vertice, const Csr& graph, vector<bool>& visited, vector<int>& traversal) {
    visited[vertice] = true;
    traversal.push_back(vertice);
    
    int neighbors = graph.csrGraph.rowPtr[vertice + 1] - graph.csrGraph.rowPtr[vertice];
    
    for (int i = graph.csrGraph.rowPtr[vertice]; i < graph.csrGraph.rowPtr[vertice] + neighbors; i++) {
        int neighbor = graph.csrGraph.colIdx[i];
        if (!visited[neighbor]) {
            dfsHelper(neighbor, graph, visited, traversal);
        }
    }
}

void dfs(const Csr& graph, vector<int>& traversal) {
    traversal.clear();
    vector<bool> visited(graph.csrGraph.numVertices, false);
    dfsHelper(graph.csrGraph.sourceVertex, graph, visited, traversal);
}