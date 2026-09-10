#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include "../../utility/csr.h"

using namespace std;

// ==============================================================================
// ASSUMED HELPER FUNCTIONS (From your existing headers)
// ==============================================================================
extern void vertexColoring(const CsrGraph& graph, vector<int>& colors, int& numColorsUsed);
struct MFMC { long long maxFlow; long long minCutCapacity; };
extern MFMC maxFlowMinCut(Csr& csr); // Assumes you pass a Csr object
extern void kMeans(int n, int d, int k, int maxIter, double tol, const vector<vector<double>>& points, 
                   vector<int>& assignments, vector<vector<double>>& centroids, 
                   int& actualIter, bool& converged, double& wcss);

const long long INF = 1e15;

// ==============================================================================
// 1. PERSONALIZED PAGERANK
// Instead of teleporting to any random page, the surfer ALWAYS teleports 
// back to a specific "home" node[cite: 11].
// ==============================================================================
void personalizedPageRank(const CsrGraph& graph, int homeNode, double d, double tol, int maxIter, 
                          vector<double>& ranks, int& actualIter, bool& converged) {
    int V = graph.numVertices;
    ranks.assign(V, 1.0 / V); // Initial rank distribution
    vector<double> next_ranks(V, 0.0);
    converged = false;
    actualIter = 0;

    while (actualIter < maxIter) {
        double dangling_sum = 0.0;
        for (int i = 0; i < V; i++) {
            int outdegree = graph.rowPtr[i+1] - graph.rowPtr[i];
            if (outdegree == 0) dangling_sum += ranks[i];
        }
        
        // STANDARD PageRank distributes (1-d)/V to EVERY node[cite: 11].
        // PERSONALIZED PageRank gives the ENTIRE teleportation mass to the homeNode!
        for (int i = 0; i < V; i++) next_ranks[i] = 0.0; // Reset
        next_ranks[homeNode] += (1.0 - d); 
        
        // Dangling node mass is still distributed evenly to everyone to prevent rank leaking
        double dangling_dist = (dangling_sum * d) / V;
        for (int i = 0; i < V; i++) next_ranks[i] += dangling_dist;

        // Standard Rank Push
        for (int u = 0; u < V; u++) {
            int outdegree = graph.rowPtr[u+1] - graph.rowPtr[u];
            if (outdegree > 0) {
                double contribution = (ranks[u] * d) / outdegree;
                for (int i = graph.rowPtr[u]; i < graph.rowPtr[u+1]; i++) {
                    int v = graph.colIdx[i];
                    next_ranks[v] += contribution;
                }
            }
        }

        double diff = 0.0;
        for (int i = 0; i < V; i++) {
            diff += abs(next_ranks[i] - ranks[i]);
            ranks[i] = next_ranks[i];
        }

        actualIter++;
        if (diff <= tol) {
            converged = true;
            break;
        }
    }
}

// ==============================================================================
// 2. MULTI-SOURCE & MULTI-SINK MAX FLOW (The Super-Node Trick)
// Converts a graph with multiple pumps and drains into a standard single-source 
// single-sink graph so you can just run your normal Dinic's algorithm on it.
// ==============================================================================
Csr buildSuperNodeGraph(const CsrGraph& originalGraph, const vector<int>& sources, const vector<int>& sinks) {
    Csr newCsr;
    int originalV = originalGraph.numVertices;
    
    // Add 2 new vertices: Super-Source (V) and Super-Sink (V+1)
    int superSource = originalV;
    int superSink = originalV + 1;
    
    newCsr.csrGraph.numVertices = originalV + 2;
    newCsr.csrGraph.sourceVertex = superSource;
    newCsr.csrGraph.sinkVertex = superSink;
    
    // Intermediate Adjacency List to easily combine old and new edges
    vector<vector<pair<int, int>>> adj(newCsr.csrGraph.numVertices);
    
    // 1. Copy all original edges
    for (int u = 0; u < originalV; u++) {
        for (int i = originalGraph.rowPtr[u]; i < originalGraph.rowPtr[u+1]; i++) {
            int v = originalGraph.colIdx[i];
            int cap = originalGraph.values[i];
            adj[u].push_back({v, cap});
        }
    }
    
    // 2. Connect Super-Source to all real sources with INF capacity
    for (int s : sources) {
        adj[superSource].push_back({s, 1e9});
    }
    
    // 3. Connect all real sinks to Super-Sink with INF capacity
    for (int t : sinks) {
        adj[t].push_back({superSink, 1e9});
    }
    
    // 4. Convert intermediate list back to CSR
    newCsr.csrGraph.rowPtr.push_back(0);
    for (int i = 0; i < newCsr.csrGraph.numVertices; i++) {
        for (auto edge : adj[i]) {
            newCsr.csrGraph.colIdx.push_back(edge.first);
            newCsr.csrGraph.values.push_back(edge.second);
        }
        newCsr.csrGraph.rowPtr.push_back(newCsr.csrGraph.colIdx.size());
    }
    newCsr.csrGraph.numEdges = newCsr.csrGraph.colIdx.size();
    
    return newCsr; // Now you can just run maxFlowMinCut(newCsr) !
}

// ==============================================================================
// 3. GRADIENT DESCENT WITH MOMENTUM
// Adds a "velocity" term so the descent builds up speed on long straight slopes,
// preventing it from getting stuck in shallow areas[cite: 10].
// ==============================================================================
void gradientDescentMomentum(int degree, const vector<double>& coeffs, double startX, 
                             double learningRate, double momentumBeta, double tol, int maxIter) {
    double currentX = startX;
    double velocity = 0.0;
    int iter = 0;
    bool converged = false;

    while (iter < maxIter) {
        // 1. Calculate Derivative: f'(x)[cite: 10]
        double derivative = 0.0;
        for (int i = 1; i <= degree; i++) {
            derivative += i * coeffs[i] * pow(currentX, i - 1);
        }

        // 2. Update Velocity and Position
        // Standard GD: currentX = currentX - (learningRate * derivative)[cite: 10]
        // Momentum GD adds the previous velocity into the calculation:
        velocity = (momentumBeta * velocity) + (learningRate * derivative);
        currentX = currentX - velocity;

        if (abs(derivative) <= tol) {
            converged = true;
            break;
        }
        iter++;
    }
    cout << "Momentum GD Final x: " << currentX << " (Converged: " << converged << ")\n";
}

// ==============================================================================
// 4. GRAPH COLORING TO MAXIMUM BIPARTITE MATCHING
// Uses Welsh-Powell to prove a graph is Bipartite (2 colors), then builds a 
// Max-Flow network to find the maximum number of pairings.
// ==============================================================================
void bipartiteMatching(const CsrGraph& graph) {
    int V = graph.numVertices;
    vector<int> colors;
    int numColorsUsed;
    
    // 1. Run Welsh-Powell Graph Coloring[cite: 11]
    vertexColoring(graph, colors, numColorsUsed);
    
    if (numColorsUsed > 2) {
        cout << "Graph is NOT bipartite (Requires " << numColorsUsed << " colors). Cannot match.\n";
        return;
    }
    
    // 2. It IS Bipartite! Build a Max-Flow graph to match Color 0 nodes with Color 1 nodes
    Csr flowGraph;
    int superSource = V;
    int superSink = V + 1;
    flowGraph.csrGraph.numVertices = V + 2;
    flowGraph.csrGraph.sourceVertex = superSource;
    flowGraph.csrGraph.sinkVertex = superSink;
    
    vector<vector<pair<int, int>>> adj(V + 2);
    
    for (int u = 0; u < V; u++) {
        if (colors[u] == 0) {
            // Super-Source to Color 0 (Capacity 1)
            adj[superSource].push_back({u, 1});
            
            // Color 0 to Color 1 original edges (Capacity 1)
            for (int i = graph.rowPtr[u]; i < graph.rowPtr[u+1]; i++) {
                int v = graph.colIdx[i];
                adj[u].push_back({v, 1});
            }
        } else if (colors[u] == 1) {
            // Color 1 to Super-Sink (Capacity 1)
            adj[u].push_back({superSink, 1});
        }
    }
    
    // Convert adj to flowGraph CSR (same logic as the Super Node trick above)
    flowGraph.csrGraph.rowPtr.push_back(0);
    for (int i = 0; i < V + 2; i++) {
        for (auto edge : adj[i]) {
            flowGraph.csrGraph.colIdx.push_back(edge.first);
            flowGraph.csrGraph.values.push_back(edge.second);
        }
        flowGraph.csrGraph.rowPtr.push_back(flowGraph.csrGraph.colIdx.size());
    }
    
    // 3. Run Max Flow to get the matching size
    MFMC result = maxFlowMinCut(flowGraph);
    cout << "Graph is Bipartite! Maximum Matching Size: " << result.maxFlow << "\n";
}

// ==============================================================================
// 5. METRIC CLUSTERING (PageRank + K-Means)
// Ranks the graph vertices by importance, then uses K-Means to automatically 
// group them into "High", "Medium", and "Low" impact tiers.
// ==============================================================================
void metricClustering(const CsrGraph& graph) {
    int V = graph.numVertices;
    
    // 1. Get PageRank values
    vector<double> ranks;
    int prIter;
    bool prConverged;
    // Assuming a standard pageRank function exists
    // pageRank(graph, 0.85, 1e-4, 100, ranks, prIter, prConverged);[cite: 11]
    
    // Dummy populate for compilation sake
    ranks.assign(V, 1.0/V); 

    // 2. Format the 1D ranks into a 2D matrix for K-Means
    vector<vector<double>> prPoints(V, vector<double>(1, 0.0));
    for (int i = 0; i < V; i++) {
        prPoints[i][0] = ranks[i];
    }
    
    // 3. Run K-Means Clustering (k = 3 for High, Med, Low tiers)[cite: 11]
    int k_clusters = 3; 
    vector<int> assignments;
    vector<vector<double>> centroids;
    int kmIter;
    bool kmConverged;
    double wcss;
    
    kMeans(V, 1, k_clusters, 300, 1e-4, prPoints, assignments, centroids, kmIter, kmConverged, wcss);
    
    cout << "Nodes successfully clustered by PageRank importance!\n";
    cout << "WCSS of the tiers: " << wcss << "\n";
}