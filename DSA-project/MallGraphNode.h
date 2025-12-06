//Abdullah Noor
#ifndef MALLGRAPHNODE_H
#define MALLGRAPHNODE_H
#include "GraphEdge.h"
#include <iostream>
using namespace std;

class MallGraphNode {
private:
    int id;
    string mallID;
    float x, y;
    GraphEdge* edgeHead;
public:
    MallGraphNode();
    MallGraphNode(int i, string mid, float xCoord, float yCoord);
    ~MallGraphNode();
    int getID();
    string getMallID();
    float getX();
    float getY();
    GraphEdge* getEdgeHead();
    void setID(int i);
    void setMallID(string mid);
    void setX(float xCoord);
    void setY(float yCoord);
    void setEdgeHead(GraphEdge* edge);
    void addEdge(int to, int weight);
};
#endif