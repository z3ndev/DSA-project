#ifndef HOSPITALGRAPHNODE_H
#define HOSPITALGRAPHNODE_H

#include "GraphEdge.h"
#include <iostream>
using namespace std;

class HospitalGraphNode {
private:
    int id;
    string hospitalID;
    float x, y;
    GraphEdge* edgeHead;
public:
    HospitalGraphNode();
    HospitalGraphNode(int i, string hid, float xCoord, float yCoord);
    ~HospitalGraphNode();

    int getID() { return id; }
    string getHospitalID() { return hospitalID; }
    float getX() { return x; }
    float getY() { return y; }
    GraphEdge* getEdgeHead() { return edgeHead; }
    void setID(int i);
    void setHospitalID(string hid);
    void setX(float xCoord);
    void setY(float yCoord);
    void setEdgeHead(GraphEdge* edge);
    void addEdge(int to, int weight);
};
#endif