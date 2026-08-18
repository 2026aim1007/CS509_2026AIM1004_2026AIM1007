#include <iostream>
#include <queue>
#include "../../utility/csr.h"
#include "graph_algorithms.h"

using namespace std;

int connectedComp(Csr& csr, vector<int>& componentIds) {
    int vertices =  csr.csrGraph.numVertices;
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

            int start = csr.csrGraph.rowPtr[element], end = csr.csrGraph.rowPtr[element + 1];
            for (int i = start; i < end; i++) {
                if (componentIds[csr.csrGraph.colIdx[i]] == -1) {
                    bfs.push(csr.csrGraph.colIdx[i]);
                    componentIds[csr.csrGraph.colIdx[i]] = componentId;
                }
            }
        }
        componentId++;
    }

    return componentId;
}