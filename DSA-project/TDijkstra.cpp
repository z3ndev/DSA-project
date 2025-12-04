//Maaz Tahir
#include "TDijkstra.h"

TDijkstra::TDijkstra(TGraph* g)
{
    graph = g;
}

// Runs Dijkstra and fills outDist[] for each outIDs[i]
void TDijkstra::compute(const string& sourceID, string* outIDs, double* outDist, int nodeCount)
{
    for (int i = 0; i < nodeCount; i++)
        outDist[i] = 1e18;   // Infinity

    // Find source index
    int sourceIndex = -1;
    for (int i = 0; i < nodeCount; i++) {
        if (outIDs[i] == sourceID) {
            sourceIndex = i;
            break;
        }
    }
    if (sourceIndex == -1) return;

    outDist[sourceIndex] = 0;

    TMinHeap heap(nodeCount * 3);
    heap.insert(sourceID, 0);

    while (!heap.isEmpty()) {
        string currID;
        double currDist;
        heap.extractMin(currID, currDist);

        int neighCount = 0;
        TGraphEdge** edges = graph->getNeighbors(currID, neighCount);  // <-- pointer array

        if (edges == nullptr) continue;

        for (int i = 0; i < neighCount; i++) {
            string nextID = edges[i]->to;     // access via pointer
            double weight = edges[i]->weight;

            // Find index of nextID
            int nextIndex = -1;
            for (int j = 0; j < nodeCount; j++) {
                if (outIDs[j] == nextID) {
                    nextIndex = j;
                    break;
                }
            }
            if (nextIndex == -1) continue;

            double newDist = currDist + weight;

            if (newDist < outDist[nextIndex]) {
                outDist[nextIndex] = newDist;
                heap.insert(nextID, newDist);
            }
        }
    }
}

double TDijkstra::getShortestDistance(const string& sourceID, const string& destID)
{
    int nodeCount = graph->getNodeCount();
    if (nodeCount <= 0) return -1;

    string* ids = new string[nodeCount];
    double* dist = new double[nodeCount];

    graph->getAllNodeIDs(ids);

    compute(sourceID, ids, dist, nodeCount);

    double result = -1;
    for (int i = 0; i < nodeCount; i++) {
        if (ids[i] == destID) {
            result = dist[i];
            break;
        }
    }

    delete[] ids;
    delete[] dist;

    return result;
}
