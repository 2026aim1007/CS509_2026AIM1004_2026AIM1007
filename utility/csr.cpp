#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include "csr.h"

using namespace std;

void Csr::convert(string path) {
    ifstream file(path);
    if (!file.is_open()) return;

    csrGraph.rowPtr.clear();
    csrGraph.colIdx.clear();
    csrGraph.values.clear();

    int index = 0;
    file >> csrGraph.numVertices >> csrGraph.numEdges;
    csrGraph.rowPtr.reserve(csrGraph.numVertices + 1);
    csrGraph.colIdx.reserve(2 * csrGraph.numEdges);
    csrGraph.values.reserve(2 * csrGraph.numEdges);

    for (int vertice = 0; vertice < csrGraph.numVertices; vertice++) {
        int v, degree;
        file >> v >> degree;
        csrGraph.rowPtr.push_back(index);

        for (int i = 0; i < degree; i++) {
            int neighbor;
            file >> neighbor;
            csrGraph.colIdx.push_back(neighbor);
            index++;
        }
    }
    csrGraph.rowPtr.push_back(index);

    string extra;
    if (file >> extra){
        file >> csrGraph.sourceVertex;
    }

    file.close();
}

void Csr::convert(string path, bool isWeighted) {
    ifstream file(path);
    if (!file.is_open()) return;

    csrGraph.rowPtr.clear();
    csrGraph.colIdx.clear();
    csrGraph.values.clear();

    int index = 0;
    file >> csrGraph.numVertices >> csrGraph.numEdges;
    csrGraph.rowPtr.reserve(csrGraph.numVertices + 1);
    csrGraph.colIdx.reserve(2 * csrGraph.numEdges);
    csrGraph.values.reserve(2 * csrGraph.numEdges);

    for (int vertice = 0; vertice < csrGraph.numVertices; vertice++) {
        int v, degree;
        file >> v >> degree;
        csrGraph.rowPtr.push_back(index);

        for (int i = 0; i < degree; i++) {
            int neighbor, weight;
            file >> neighbor;
            file >> weight;
            csrGraph.colIdx.push_back(neighbor);
            csrGraph.values.push_back(weight);
            index++;
        }
    }
    csrGraph.rowPtr.push_back(index);

    string extra;
    if (file >> extra){
        file >> csrGraph.sourceVertex;
        if (file >> extra) {
            file >> csrGraph.sinkVertex;
        }
    }

    file.close();
}

void Csr::convertFromEdgeList(string path) {
    ifstream file(path);
    if (!file.is_open()) {
        cerr << "Error: Could not open edge list file " << path << endl;
        return;
    }
    char graphType;
    if (!(file >> graphType)) return;
    vector<vector<pair<int, int>>> adj; 
    int max_vid = -1;
    int num_input_edges = 0;
    int u, v, weight;
    while (file >> u >> v >> weight) {
        max_vid = max({max_vid, u, v});
        if (max_vid >= (int)adj.size()) {
            adj.resize(max_vid + 1);
        }
        adj[u].push_back({v, weight});
        num_input_edges++;
        if (graphType == 'U' && u != v) {
            adj[v].push_back({u, weight});
        }
    }
    csrGraph.numVertices = max_vid + 1;
    csrGraph.numEdges = num_input_edges; 
    csrGraph.rowPtr.clear();
    csrGraph.colIdx.clear();
    csrGraph.values.clear();
    csrGraph.rowPtr.reserve(csrGraph.numVertices + 1);
    int index = 0;
    for (int i = 0; i < csrGraph.numVertices; i++) {
        csrGraph.rowPtr.push_back(index);
        for (auto& edge : adj[i]) {
            csrGraph.colIdx.push_back(edge.first);
            csrGraph.values.push_back(edge.second);
            index++;
        }
    }
    csrGraph.rowPtr.push_back(index);
    csrGraph.sourceVertex = 0;
    csrGraph.sinkVertex = -1;

    file.close();
}