#include <vector>
#include <algorithm>
#include "../../utility/csr.h"
#include "graph_algorithms.h"

using namespace std;

int triangleCountingOpt(Csr& csr, vector<vector<int>>& triangleSet) {
    CsrGraph& graph = csr.csrGraph; 
    int triangles = 0;
    int vertices = graph.numVertices;
    for (int i = 0; i < vertices; i++) {
        int start = graph.rowPtr[i];
        int end = graph.rowPtr[i + 1];
        std::sort(graph.colIdx.begin() + start, graph.colIdx.begin() + end);
    }
    for (int u = 0; u < vertices; u++) {
        int u_start = graph.rowPtr[u];
        int u_end = graph.rowPtr[u + 1];
        for (int i = u_start; i < u_end; i++) {
            int v = graph.colIdx[i];
            if (u >= v) continue;
            int v_start = graph.rowPtr[v];
            int v_end = graph.rowPtr[v + 1];
            int p_u = u_start;
            int p_v = v_start;
            while (p_u < u_end && p_v < v_end) {
                int w_u = graph.colIdx[p_u];
                int w_v = graph.colIdx[p_v];
                if (w_u == w_v) {
                    int w = w_u;
                    if (v < w) {
                        triangles++;
                        triangleSet.push_back({u, v, w});
                    }
                    p_u++;
                    p_v++;
                } 
                else if (w_u < w_v) {
                    p_u++;
                } 
                else {
                    p_v++;
                }
            }
        }
    }
    return triangles; 
}