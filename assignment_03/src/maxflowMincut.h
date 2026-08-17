#ifndef MAXFLOW_MINCUT_H
#define MAXFLOW_MINCUT_H

#include <iostream>
#include <vector>
#include <queue>
#include "../../utility/csr.h"

using namespace std;

using cut = pair<int, pair<int, int>>;

struct ResEdge {
    int to;
    int idxNeighbor;
    int capacity;
    int flow;
};

struct MFMC {
    int maxFlow;
    int minCutCapacity;
    vector<int> source, sink;
    vector<cut> cutEdges;

    MFMC(int max, int min, vector<int> s, vector<int> t, vector<cut> edges) : maxFlow(max), minCutCapacity(min), source(s), sink(t), cutEdges(edges) {};
};

MFMC maxFlowMinCut(Csr& csr);

#endif //MAXFLOW_MINCUT_H