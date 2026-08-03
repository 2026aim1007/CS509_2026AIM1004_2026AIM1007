#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

struct CSRGraph {
    int numVertices = 0;
    int numEdges = 0;
    int sourceVertex = 0;

    vector<int> rowPtr;
    vector<int> colIdx;
    vector<int> values;
};

class CsrConversion {
    public:
        CSRGraph csrGraph;

        void convert(string path) {
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
            file >> extra;
            file >> csrGraph.sourceVertex;

            file.close();
    
        }

        void convert(string path, bool isWeighted) {
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

            string extra;
            file >> extra;
            file >> csrGraph.sourceVertex;

            file.close();
        }

};