//Abdullah Noor
#ifndef FACILITYGRAPHNODE_H
#define FACILITYGRAPHNODE_H

#include "GraphEdge.h"
#include <iostream>
using namespace std;

class FacilityGraphNode {
private:
    int id;
    string facilityID, type;
    float x, y;
    GraphEdge* edgeHead;
public:
    FacilityGraphNode();
    FacilityGraphNode(int i, string fid, string t, float xCoord, float yCoord);
    ~FacilityGraphNode();

    int getID() { return id; }
    string getFacilityID() { return facilityID; }
    string getType() { return type; }
    float getX() { return x; }
    float getY() { return y; }
    GraphEdge* getEdgeHead() { return edgeHead; }
    void setID(int i);
    void setFacilityID(string fid);
    void setType(string t);
    void setX(float xCoord);
    void setY(float yCoord);
    void setEdgeHead(GraphEdge* edge);
    void addEdge(int to, int weight);
};
#endif