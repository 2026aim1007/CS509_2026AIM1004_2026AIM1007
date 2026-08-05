#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <cstdlib>
#include <limits>
#include <algorithm>

using namespace std;

const int INF = numeric_limits<int>::max();
void runBFS(int V, int source, const vector<vector<int>>& adj, string outPath) {
    queue<int> q;
    vector<int> distances(V, -1);
    vector<int> traversal;

    q.push(source);
    distances[source] = 0;
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        traversal.push_back(u);
        
        for (int v : adj[u]) {
            if (distances[v] == -1) {
                q.push(v);
                distances[v] = distances[u] + 1;
            }
        }
    }
    ofstream outFile(outPath);
    outFile << "Algorithm: BFS\nSource: " << source << "\nTraversal: ";
    for (int v : traversal) outFile << v << " ";
    outFile << "\nDistances:\n";
    for (int i = 0; i < V; i++) outFile << i << " " << distances[i] << "\n";
    outFile.close();
}

void dfsHelper(int u, const vector<vector<int>>& adj, vector<bool>& visited, vector<int>& traversal) {
    visited[u] = true;
    traversal.push_back(u);
    for (int v : adj[u]) {
        if (!visited[v]) dfsHelper(v, adj, visited, traversal);
    }
}

void runDFS(int V, int source, const vector<vector<int>>& adj, string outPath) {
    vector<int> traversal;
    vector<bool> visited(V, false);
    dfsHelper(source, adj, visited, traversal);

    ofstream outFile(outPath);
    outFile << "Algorithm: DFS\nSource: " << source << "\nTraversal: ";
    for (int v : traversal) outFile << v << " ";
    outFile << "\n";
    outFile.close();
}

void runSSSP(int V, int source, const vector<vector<pair<int, int>>>& adj, string outPath) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> distances(V, INF);
    
    distances[source] = 0;
    pq.push({0, source});
    
    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        
        if (d > distances[u]) continue;
        
        for (auto edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;
            if (distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                pq.push({distances[v], v});
            }
        }
    }

    ofstream outFile(outPath);
    outFile << "Algorithm: SSSP\nSource: " << source << "\nVertex\tDistance\n";
    for (int i = 0; i < V; i++) {
        if (distances[i] == INF) outFile << i << "\tINF\n";
        else outFile << i << "\t" << distances[i] << "\n";
    }
    outFile.close();
}

void generateUnweighted(int V, string testId) {
    vector<vector<int>> adj(V);
    int E = 0;
    int source = 0;
    for (int i = 1; i < V; i++) {
        int u = i;
        int v = rand() % i; 
        adj[u].push_back(v);
        adj[v].push_back(u);
        E++;
    }
    for (int i = 0; i < V; i++) {
        int extraEdges = rand() % 3;
        for (int e = 0; e < extraEdges; e++) {
            int u = rand() % V;
            int v = rand() % V;
            if (u != v) {
                adj[u].push_back(v);
                adj[v].push_back(u);
                E++;
            }
        }
    }
    string testPath = "tests/unweighted" + testId + ".txt";
    ofstream tFile(testPath);
    tFile << V << " " << E << "\n";
    for (int i = 0; i < V; i++) {
        tFile << i << " " << adj[i].size();
        for (int neighbor : adj[i]) tFile << " " << neighbor;
        tFile << "\n";
    }
    tFile << "SOURCE " << source << "\n";
    tFile.close();
    runBFS(V, source, adj, "outputs/expected_bfs_" + testId + ".txt");
    runDFS(V, source, adj, "outputs/expected_dfs_" + testId + ".txt");
    cout << "Generated: " << testPath << " (and BFS/DFS expected outputs)\n";
}

void generateWeighted(int V, string testId) {
    vector<vector<pair<int, int>>> adj(V);
    int E = 0;
    int source = 0;

    for (int i = 1; i < V; i++) {
        int u = i;
        int v = rand() % i; 
        int w = (rand() % 20) + 1;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
        E++;
    }

    for (int i = 0; i < V; i++) {
        int extraEdges = rand() % 3;
        for (int e = 0; e < extraEdges; e++) {
            int u = rand() % V;
            int v = rand() % V;
            int w = (rand() % 20) + 1;
            if (u != v) {
                adj[u].push_back({v, w});
                adj[v].push_back({u, w});
                E++;
            }
        }
    }

    string testPath = "tests/sssp" + testId + ".txt";
    ofstream tFile(testPath);
    tFile << V << " " << E << "\n";
    for (int i = 0; i < V; i++) {
        tFile << i << " " << adj[i].size();
        for (auto edge : adj[i]) tFile << " " << edge.first << " " << edge.second;
        tFile << "\n";
    }
    tFile << "SOURCE " << source << "\n";
    tFile.close();

    runSSSP(V, source, adj, "outputs/expected_sssp_" + testId + ".txt");
    cout << "Generated: " << testPath << " (and SSSP expected output)\n";
}

int main() {
    srand(42);
    cout << "Generating Graph Test Cases...\n";
    generateUnweighted(10, "10");
    generateUnweighted(100, "100");
    generateUnweighted(10000, "10000");
    generateUnweighted(50000, "50000");
    generateUnweighted(100000, "100000");
    generateWeighted(10, "10");
    generateWeighted(100, "100");
    generateWeighted(10000, "10000");
    generateWeighted(50000, "50000");
    generateWeighted(100000, "100000");
    return 0;
}