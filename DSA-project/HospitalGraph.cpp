#include "HospitalGraph.h"

HospitalGraph::HospitalGraph(int cap) {
    nodeCount = 0;
    capacity = cap;
    nodes = new HospitalGraphNode*[capacity];
    for (int i = 0; i < capacity; i++) nodes[i] = NULL;
}

HospitalGraph::~HospitalGraph() {
    for (int i = 0; i < nodeCount; i++) delete nodes[i];
    delete[] nodes;
}

int HospitalGraph::addNode(string hospitalID, float x, float y) {
    if (nodeCount >= capacity) {
        capacity *= 2;
        HospitalGraphNode** newNodes = new HospitalGraphNode*[capacity];
        for (int i = 0; i < nodeCount; i++) newNodes[i] = nodes[i];
        for (int i = nodeCount; i < capacity; i++) newNodes[i] = NULL;
        delete[] nodes;
        nodes = newNodes;
    }
    nodes[nodeCount] = new HospitalGraphNode(nodeCount, hospitalID, x, y);
    return nodeCount++;
}

bool HospitalGraph::addEdge(int from, int to, int weight) {
    if (from >= 0 && from < nodeCount && to >= 0 && to < nodeCount) {
        nodes[from]->addEdge(to, weight);
        nodes[to]->addEdge(from, weight);
        return true;
    }
    return false;
}

int HospitalGraph::findMinDistance(int* distances, bool* visited) {
    int minDist = INT_MAX, minIndex = -1;
    for (int i = 0; i < nodeCount; i++) {
        if (!visited[i] && distances[i] < minDist) {
            minDist = distances[i];
            minIndex = i;
        }
    }
    return minIndex;
}

void HospitalGraph::reconstructPath(int* predecessors, int start, int end, string* path, int& pathLength) {
    int* temp = new int[nodeCount];
    int len = 0, curr = end;
    while (curr != -1 && curr != start) {
        temp[len++] = curr;
        curr = predecessors[curr];
    }
    if (curr == -1) {
        pathLength = 0;
        delete[] temp;
        return;
    }
    temp[len++] = start;
    pathLength = len;
    for (int i = 0; i < len; i++) path[i] = nodes[temp[len - 1 - i]]->getHospitalID();
    delete[] temp;
}

void HospitalGraph::dijkstra(int start, int end, string* path, int& pathLength, int& totalDistance) {
    int* dist = new int[nodeCount];
    bool* vis = new bool[nodeCount];
    int* pred = new int[nodeCount];
    for (int i = 0; i < nodeCount; i++) {
        dist[i] = INT_MAX;
        vis[i] = false;
        pred[i] = -1;
    }
    dist[start] = 0;
    for (int c = 0; c < nodeCount - 1; c++) {
        int u = findMinDistance(dist, vis);
        if (u == -1 || u == end) break;
        vis[u] = true;
        GraphEdge* e = nodes[u]->getEdgeHead();
        while (e) {
            int v = e->getTo();
            if (!vis[v] && dist[u] + e->getWeight() < dist[v]) {
                dist[v] = dist[u] + e->getWeight();
                pred[v] = u;
            }
            e = e->getNext();
        }
    }
    totalDistance = dist[end];
    reconstructPath(pred, start, end, path, pathLength);
    delete[] dist;
    delete[] vis;
    delete[] pred;
}

int HospitalGraph::findNearestHospital(float x, float y) {
    if (nodeCount == 0) return -1;
    int nearest = -1;
    float minDist = INT_MAX;
    for (int i = 0; i < nodeCount; i++) {
        float d = sqrt(pow(nodes[i]->getX() - x, 2) + pow(nodes[i]->getY() - y, 2));
        if (d < minDist) {
            minDist = d;
            nearest = i;
        }
    }
    return nearest;
}

void HospitalGraph::display() {
    cout << "Hospital Graph:" << endl;
    for (int i = 0; i < nodeCount; i++) {
        cout << "Node " << i << " (" << nodes[i]->getHospitalID() << "): ";
        GraphEdge* e = nodes[i]->getEdgeHead();
        while (e) {
            cout << "-> " << e->getTo() << " (w:" << e->getWeight() << ") ";
            e = e->getNext();
        }
        cout << endl;
    }
}