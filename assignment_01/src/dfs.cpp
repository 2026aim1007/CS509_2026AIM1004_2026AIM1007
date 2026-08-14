#include <iostream>
#include <vector>
#include <stack>
#include "csr.h"

using namespace std;

void dfs(const Csr& graph, vector<int>& traversal) {
    traversal.clear();
    vector<bool> visited(graph.csrGraph.numVertices, false);
    stack<int> s;
    s.push(graph.csrGraph.sourceVertex);
    while (!s.empty()) {
        int vertice = s.top();
        s.pop();
        if (!visited[vertice]) {
            visited[vertice] = true;
            traversal.push_back(vertice);
            int startIdx = graph.csrGraph.rowPtr[vertice];
            int endIdx = graph.csrGraph.rowPtr[vertice + 1];
            for (int i = endIdx - 1; i >= startIdx; i--) {
                int neighbor = graph.csrGraph.colIdx[i];
                if (!visited[neighbor]) {
                    s.push(neighbor);
                }
            }
        }
    }
}