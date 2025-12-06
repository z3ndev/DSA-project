//Maaz Tahir
#include "TGraph.h"
#include <iostream>
using namespace std;

TGraph::TGraph(int maxNodes) {
    this->maxNodes = maxNodes;
    nodeCount = 0;

    nodes = new TGraphNode * [maxNodes];
    adjacencyList = new TGraphEdge * *[maxNodes];
    edgeCounts = new int[maxNodes];
    maxEdges = new int[maxNodes];

    for (int i = 0; i < maxNodes; i++) {
        nodes[i] = nullptr;
        adjacencyList[i] = nullptr;
        edgeCounts[i] = 0;
        maxEdges[i] = 0;
    }
}


TGraph::~TGraph() {
    for (int i = 0; i < nodeCount; i++) {
        if (nodes[i]) delete nodes[i];

        if (adjacencyList[i]) {
            for (int j = 0; j < edgeCounts[i]; j++)
                delete adjacencyList[i][j];
            delete[] adjacencyList[i];
        }
    }
    delete[] nodes;
    delete[] adjacencyList;
    delete[] edgeCounts;
    delete[] maxEdges;
}


int TGraph::getNodeIndex(const string& id) const {
    for (int i = 0; i < nodeCount; i++) {
        if (nodes[i]->id == id)
            return i;
    }
    return -1;
}

void TGraph::addNode(const TGraphNode& node) {
    if (nodeCount >= maxNodes) {
        cout << "Node limit reached.\n";
        return;
    }

    // Avoid duplicates
    if (getNodeIndex(node.id) != -1) {
        cout << "Node already exists.\n";
        return;
    }

    // Allocate the node
    nodes[nodeCount] = new TGraphNode(node);

    // Initialize adjacency list as null (no edges yet)
    adjacencyList[nodeCount] = nullptr;
    edgeCounts[nodeCount] = 0;
    maxEdges[nodeCount] = 0;  // capacity is 0 initially, will expand in addEdge

    nodeCount++;
}


void TGraph::addEdge(const string& sourceID, const string& destID, double weight) {
    int srcIndex = getNodeIndex(sourceID);
    int dstIndex = getNodeIndex(destID);

    if (srcIndex == -1 || dstIndex == -1) {
        cout << "Invalid edge: node not found.\n";
        return;
    }

    if (adjacencyList[srcIndex] == nullptr) {
        // First edge for this node, allocate initial array
        adjacencyList[srcIndex] = new TGraphEdge * [5]; // start with 5 edges
        maxEdges[srcIndex] = 5;
        edgeCounts[srcIndex] = 0;
    }

    int count = edgeCounts[srcIndex];
    int capacity = maxEdges[srcIndex];

    // Resize if needed
    if (count >= capacity) {
        int newCap = capacity * 2;
        TGraphEdge** temp = new TGraphEdge * [newCap];

        for (int i = 0; i < capacity; i++)
            temp[i] = adjacencyList[srcIndex][i];

        delete[] adjacencyList[srcIndex];
        adjacencyList[srcIndex] = temp;
        maxEdges[srcIndex] = newCap;
    }

    adjacencyList[srcIndex][edgeCounts[srcIndex]] = new TGraphEdge(destID, weight);
    edgeCounts[srcIndex]++;
}



TGraphEdge** TGraph::getNeighbors(const string& nodeID, int& count) const 
{
    int index = getNodeIndex(nodeID);

    if (index == -1 || adjacencyList[index] == nullptr) {
        count = 0;
        return nullptr;
    }

    count = edgeCounts[index];
    return adjacencyList[index];
}

void TGraph::printGraph() const {
    for (int i = 0; i < nodeCount; i++) {
        cout << nodes[i]->toString() << " -> ";
        for (int j = 0; j < edgeCounts[i]; j++) {
            cout << adjacencyList[i][j]->to
                << "(" << adjacencyList[i][j]->weight << ") ";
        }
        cout << endl;
    }
}



int TGraph::getNodeCount() const {
    return nodeCount;
}

void TGraph::getAllNodeIDs(string* arr) const {
    for (int i = 0; i < nodeCount; i++) {
        arr[i] = nodes[i]->id;
    }
}

void TGraph::removeEdge(const string& sourceID, const string& destID) {
    int srcIndex = getNodeIndex(sourceID);
    if (srcIndex == -1 || adjacencyList[srcIndex] == nullptr) return;

    int count = edgeCounts[srcIndex];

    for (int i = 0; i < count; i++) {
        if (adjacencyList[srcIndex][i]->to == destID) {
            delete adjacencyList[srcIndex][i]; // free memory

            // Shift left
            for (int j = i; j < count - 1; j++)
                adjacencyList[srcIndex][j] = adjacencyList[srcIndex][j + 1];

            edgeCounts[srcIndex]--;
            return;
        }
    }
}

TGraphNode* TGraph::getNodeByID(const string& id) const {
    int index = getNodeIndex(id);
    if (index == -1) return nullptr;
    return nodes[index];
}

bool TGraph::getNodeCoordinates(const string& id, double& lat, double& lon) const {
    int index = getNodeIndex(id);
    if (index == -1) return false;
    
    lat = nodes[index]->latitude;
    lon = nodes[index]->longitude;
    return true;
}

