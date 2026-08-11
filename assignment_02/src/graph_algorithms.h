#ifndef GRAPH_ALGORITHMS_H
#define GRAPH_ALGORITHMS_H

#include <iostream>
#include <queue>
#include "../../utility/csr.h"

using namespace std;

int connectedComp(Csr& csr, vector<int>& componentIds);
int triangleCountingUnopt(Csr& csr, vector<vector<int>>& triangleSet);

#endif