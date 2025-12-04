//Maaz Tahir
#pragma once
#include "TGraphNode.h"
#include "TGraphEdge.h"
using namespace std;


class TGraph {
private:

    TGraphNode** nodes;
    int nodeCount;
    int maxNodes;

    TGraphEdge*** adjacencyList;
    int* edgeCounts;
    int* maxEdges;

    int getNodeIndex(const string& id) const;

public:
    TGraph(int maxNodes = 100);
    ~TGraph();

    void addNode(const TGraphNode& node);

    void addEdge(const string& sourceID, const string& destID, double weight);

    TGraphEdge** getNeighbors(const string& nodeID, int& count) const;

    void printGraph() const;

    int getNodeCount() const;
    void getAllNodeIDs(string* arr) const;

    void removeEdge(const string& sourceID, const string& destID);
};
