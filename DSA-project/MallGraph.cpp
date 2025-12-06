//Abdullah Noor
#include "MallGraph.h"
#include <iostream>
using namespace std;
MallGraph::MallGraph(int cap) :nodeCount(0), capacity(cap) {
    nodes = new MallGraphNode * [capacity];
    for (int i = 0; i < capacity; i++) nodes[i] = NULL;
}
MallGraph::~MallGraph() {
    for (int i = 0; i < nodeCount; i++) delete nodes[i];
    delete[] nodes;
}
int MallGraph::addNode(string mallID, float x, float y) {
    if (nodeCount >= capacity) {
        capacity *= 2;
        MallGraphNode** newNodes = new MallGraphNode * [capacity];
        for (int i = 0; i < nodeCount; i++) newNodes[i] = nodes[i];
        for (int i = nodeCount; i < capacity; i++) newNodes[i] = NULL;
        delete[] nodes;
        nodes = newNodes;
    }
    nodes[nodeCount] = new MallGraphNode(nodeCount, mallID, x, y);
    return nodeCount++;
}
bool MallGraph::addEdge(int from, int to, int weight) {
    if (from >= 0 && from < nodeCount && to >= 0 && to < nodeCount) {
        nodes[from]->addEdge(to, weight);
        nodes[to]->addEdge(from, weight);
        return true;
    }
    return false;
}
int MallGraph::findMinDistance(int* distances, bool* visited) {
    int minDistance = INT_MAX;
    int minIndex = -1;
    for (int i = 0; i < nodeCount; i++) if (!visited[i] && distances[i] < minDistance) { minDistance = distances[i]; minIndex = i; }
    return minIndex;
}
void MallGraph::reconstructPath(int* predecessors, int start, int end, string* path, int& pathLength) {
    int* tempPath = new int[nodeCount];
    int tempLength = 0;
    int current = end;
    while (current != -1 && current != start) { tempPath[tempLength++] = current; current = predecessors[current]; }
    if (current == -1) { pathLength = 0; delete[] tempPath; return; }
    tempPath[tempLength++] = start;
    pathLength = tempLength;
    for (int i = 0; i < pathLength; i++) path[i] = nodes[tempPath[pathLength - 1 - i]]->getMallID();
    delete[] tempPath;
}
void MallGraph::dijkstra(int start, int end, string* path, int& pathLength, int& totalDistance) {
    int* distances = new int[nodeCount];
    bool* visited = new bool[nodeCount];
    int* predecessors = new int[nodeCount];
    for (int i = 0; i < nodeCount; i++) { distances[i] = INT_MAX; visited[i] = false; predecessors[i] = -1; }
    distances[start] = 0;
    for (int count = 0; count < nodeCount - 1; count++) {
        int u = findMinDistance(distances, visited);
        if (u == -1) break;
        if (u == end) break;
        visited[u] = true;
        GraphEdge* edge = nodes[u]->getEdgeHead();
        while (edge != NULL) {
            int v = edge->getTo();
            if (!visited[v] && distances[u] + edge->getWeight() < distances[v]) {
                distances[v] = distances[u] + edge->getWeight();
                predecessors[v] = u;
            }
            edge = edge->getNext();
        }
    }
    totalDistance = distances[end];
    reconstructPath(predecessors, start, end, path, pathLength);
    delete[] distances;
    delete[] visited;
    delete[] predecessors;
}
int MallGraph::findNearestMall(float x, float y) {
    if (nodeCount == 0) return -1;
    int nearestIndex = 0;
    float minDistance = sqrt(pow(nodes[0]->getX() - x, 2) + pow(nodes[0]->getY() - y, 2));
    for (int i = 1; i < nodeCount; i++) {
        float distance = sqrt(pow(nodes[i]->getX() - x, 2) + pow(nodes[i]->getY() - y, 2));
        if (distance < minDistance) { minDistance = distance; nearestIndex = i; }
    }
    return nearestIndex;
}
void MallGraph::display() {
    cout << "Mall Graph:" << endl;
    for (int i = 0; i < nodeCount; i++) {
        cout << "Node " << i << " (" << nodes[i]->getMallID() << "): ";
        GraphEdge* edge = nodes[i]->getEdgeHead();
        while (edge != NULL) { cout << "-> " << edge->getTo() << " (w:" << edge->getWeight() << ") "; edge = edge->getNext(); }
        cout << endl;
    }
}