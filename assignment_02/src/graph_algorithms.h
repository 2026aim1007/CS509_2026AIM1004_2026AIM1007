#ifndef GRAPH_ALGORITHMS_H
#define GRAPH_ALGORITHMS_H

#include <vector>
#include "../../utility/csr.h"

using namespace std;

int connectedComp(Csr& csr, vector<int>& componentIds);
int triangleCountingUnopt(Csr& csr, vector<vector<int>>& triangleSet);
int triangleCountingOpt(Csr& csr, vector<vector<int>>& triangleSet);
void betweennessCentrality(Csr& csr, vector<double>& centrality);

#endif