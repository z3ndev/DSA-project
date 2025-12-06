//Abdullah Noor
#ifndef AIRPORTRAILGRAPHNODE_H
#define AIRPORTRAILGRAPHNODE_H

#include "GraphEdge.h"
#include <iostream>
using namespace std;
class AirportRailGraphNode {
private:
    int id;
    string name, type;
    float x, y;
    GraphEdge* edgeHead;

public:
    AirportRailGraphNode();
    AirportRailGraphNode(int i, string n, string t, float xCoord, float yCoord);
    ~AirportRailGraphNode();
    int getID() { return id; }
    string getName() { return name; }
    string getType() { return type; }
    float getX() { return x; }
    float getY() { return y; }
    GraphEdge* getEdgeHead() { return edgeHead; }
    void setID(int i);
    void setName(string n);
    void setType(string t);
    void setX(float xCoord);
    void setY(float yCoord);
    void setEdgeHead(GraphEdge* edge);
    void addEdge(int to, int weight);
};
#endif