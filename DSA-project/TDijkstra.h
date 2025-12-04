//Maaz Tahir
#pragma once
#include <string>
#include "TGraph.h"
#include "TMinHeap.h"

using namespace std;

/*Dijkstra algorithm for shortest paths in transport graph.Uses TMinHeap (min-heap) and arrays only.
*/

class TDijkstra {
private:
    TGraph* graph;

public:
    TDijkstra(TGraph* g);

    void compute(const string& sourceID, string* outIDs, double* outDist, int nodeCount);
    double getShortestDistance(const string& sourceID, const string& destID);
};
