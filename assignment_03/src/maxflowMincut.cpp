#include <iostream>
#include <vector>
#include <queue>
#include "../../utility/csr.h"
#include "maxflowMincut.h"

using namespace std;

MFMC maxFlowMinCut(Csr& csr) {
    vector<vector<ResEdge>> resGraph(csr.csrGraph.numVertices);

    for (int i = 0; i < csr.csrGraph.numVertices; i++) {
        int start = csr.csrGraph.rowPtr[i], end = csr.csrGraph.rowPtr[i + 1];
        for (int j = start; j < end; j++) {
            int neighbor = csr.csrGraph.colIdx[j];
            int cap = csr.csrGraph.values[j];
            resGraph[i].push_back({neighbor, (int)resGraph[neighbor].size(), cap, 0});
            resGraph[neighbor].push_back({i, (int)resGraph[i].size() - 1, 0, 0});
        }
    }

    vector<int> level(csr.csrGraph.numVertices);

    auto bfs = [&]() -> bool {
        fill(level.begin(), level.end(), -1);
        level[csr.csrGraph.sourceVertex] = 0;
        queue<int> q;
        q.push(csr.csrGraph.sourceVertex);
        while(!q.empty()) {
            int val = q.front();
            q.pop();
            for (ResEdge& edge : resGraph[val]) {
                if (level[edge.to] == -1 && (edge.capacity - edge.flow) > 0) {
                    level[edge.to] = level[val] + 1;
                    q.push(edge.to);
                }
            }
        }
        return level[csr.csrGraph.sinkVertex] != -1;
    };

    vector<int> ptr(csr.csrGraph.numVertices);
    auto dfs = [&](auto self, int u, int pushed) -> int {
        if (pushed == 0 || u == csr.csrGraph.sinkVertex) return pushed;
        for (int& i = ptr[u]; i < (int)resGraph[u].size(); ++i) {
            ResEdge& edge = resGraph[u][i];
            int v = edge.to;
            if (level[u] + 1 != level[v] || (edge.capacity - edge.flow == 0)) continue;
            int flowPushed = self(self, v, min(pushed, edge.capacity - edge.flow));
            if (flowPushed == 0) continue;
            resGraph[u][i].flow += flowPushed; 
            resGraph[v][edge.idxNeighbor].flow -= flowPushed;
            return flowPushed;
        }
        return 0;
    };

    long maxFlow = 0;
    while (bfs()) {
        fill(ptr.begin(), ptr.end(), 0);
        while (int pushed = dfs(dfs, csr.csrGraph.sourceVertex, 1e9)) {
            maxFlow += pushed;
        }   
    }

    vector<bool> visited(csr.csrGraph.numVertices, false);
    queue<int> q;
    q.push(csr.csrGraph.sourceVertex);
    visited[csr.csrGraph.sourceVertex] = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (ResEdge edge : resGraph[u]) {
            if ((edge.capacity - edge.flow) > 0 && !visited[edge.to]) {
                visited[edge.to] = true;
                q.push(edge.to);
            }
        }
    }

    vector<int> sourceSide, sinkSide;
    for (int i = 0; i < csr.csrGraph.numVertices; i++) {
        if (visited[i]) sourceSide.push_back(i);
        else sinkSide.push_back(i);
    }

    using cut = pair<int, pair<int, int>>;
    vector<cut> cutEdges;
    long minCut = 0;
    for (int sourceEdges : sourceSide) {
        for (ResEdge edge : resGraph[sourceEdges]) {
            if (edge.capacity > 0 && !visited[edge.to]) {
                cutEdges.push_back({edge.capacity, {sourceEdges, edge.to}});
                minCut += edge.capacity;
            }
        }
    }

    return {maxFlow, minCut, sourceSide, sinkSide, cutEdges};
}