#include <iostream>
#include "../../utility/csr.h"

using namespace std;

int triangleCountingUnopt(Csr& csr, vector<vector<int>>& triangleSet) {
    CsrGraph graph = csr.csrGraph;
    int rawTriangles = 0;
    int vertices = graph.numVertices;

    for (int vertice = 0; vertice < vertices; vertice++) {
        int start = graph.rowPtr[vertice], end = graph.rowPtr[vertice + 1];
        for (int i = start; i < end; i++) {
            int neighbor = graph.colIdx[i];
            
            int neighborStart = graph.rowPtr[neighbor];
            int neighborEnd = graph.rowPtr[neighbor + 1];
            for (int j = i + 1; j < end; j++) {
                int neighbor2 = graph.colIdx[j];
                bool connected = false;

                for (int linear = neighborStart; linear < neighborEnd; linear++) {
                    if (graph.colIdx[linear] == neighbor2) {
                        connected = true;
                        break;
                    }
                }
                
                if (connected) {
                    rawTriangles++;
                    if (vertice < neighbor && neighbor < neighbor2) {
                        triangleSet.push_back({vertice, neighbor, neighbor2});
                    }
                }
            }
        }
    }
    return rawTriangles / 3;
}