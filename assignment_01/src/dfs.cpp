#include <iostream>
#include <vector>
#include "csr.h"

using namespace std;

void dfsHelper(int vertice, Csr& graph, vector<bool>& visited, vector<int>& traversal) {
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

void dfs(Csr graph) {
    vector<int> traversal;
    vector<bool> visited(graph.csrGraph.numVertices, false);
    dfsHelper(graph.csrGraph.sourceVertex, graph, visited, traversal);
    cout << "Algorithm: DFS\n";
    cout << "Source: " << graph.csrGraph.sourceVertex << "\n";
    cout << "Traversal: ";
    for (int entry : traversal) {
        cout << entry << " ";
    }
    cout << "\n";
}