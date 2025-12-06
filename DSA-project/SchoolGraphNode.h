//Abdullah Noor
#ifndef SCHOOLGRAPHNODE_H
#define SCHOOLGRAPHNODE_H

#include "GraphEdge.h"
#include <string>
using namespace std;

class SchoolGraphNode {
private:
    int id;
    string schoolID;
    float x, y;
    GraphEdge* edgeHead;
public:
    SchoolGraphNode();
    SchoolGraphNode(int i, string sid, float xCoord, float yCoord);
    ~SchoolGraphNode();
    int getID();
    string getSchoolID();
    float getX();
    float getY();
    GraphEdge* getEdgeHead();
    void setID(int i);
    void setSchoolID(string sid);
    void setX(float xCoord);
    void setY(float yCoord);
    void setEdgeHead(GraphEdge* edge);
    void addEdge(int to, int weight);
};
#endif