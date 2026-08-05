#ifndef GRAPH_ALGORITHMS_H
#define GRAPH_ALGORITHMS_H

#include "csr.h"
#include <vector>

void bfs(Csr graph);
void dfs(const Csr& graph, std::vector<int>& traversal);
void sssp(const Csr& graph, std::vector<int>& distances);

#endif // GRAPH_ALGORITHMS_H