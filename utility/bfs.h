#ifndef BFS_H
#define BFS_H
#include <vector>
#include "csr.h"

void bfs(const Csr& graph, int source, std::vector<int>& distances, std::vector<int>& traversal);

#endif