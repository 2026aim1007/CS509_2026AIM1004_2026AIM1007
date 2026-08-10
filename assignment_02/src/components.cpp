#include <iostream>
#include <queue>
#include "../../assignment_01/src/csr.h"

using namespace std;

int connectedComp(Csr& csr, vector<int>& componentIds) {
    CsrGraph graph = csr.csrGraph;
    int vertices =  graph.numVertices;
    int componentId = 0;
    componentIds.assign(vertices, -1);

    queue<int> bfs;
    for (int vertice = 0; vertice < vertices; vertice++) {
        if (componentIds[vertice] != -1) continue;
        bfs.push(vertice);
        componentIds[vertice] = componentId;

        while(!bfs.empty()) {
            int element = bfs.front();
            bfs.pop();

            int start = graph.rowPtr[element], end = graph.rowPtr[element + 1];
            for (int i = start; i < end; i++) {
                if (componentIds[graph.colIdx[i]] == -1) {
                    bfs.push(graph.colIdx[i]);
                    componentIds[graph.colIdx[i]] = componentId;
                }
            }
        }
        componentId++;
    }
    return componentId;
}