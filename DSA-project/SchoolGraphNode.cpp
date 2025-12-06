//Abdullah Noor
#include "SchoolGraphNode.h"
#include <iostream>
using namespace std;

SchoolGraphNode::SchoolGraphNode() :id(-1), schoolID(""), x(0.0), y(0.0), edgeHead(NULL) {}
SchoolGraphNode::SchoolGraphNode(int i, string sid, float xCoord, float yCoord) :id(i), schoolID(sid), x(xCoord), y(yCoord), edgeHead(NULL) {}
SchoolGraphNode::~SchoolGraphNode() {
    GraphEdge* current = edgeHead;
    while (current != nullptr) {
        GraphEdge* next = current->getNext();
        delete current;
        current = next;
    }
}
int SchoolGraphNode::getID() { return id; }
string SchoolGraphNode::getSchoolID() { return schoolID; }
float SchoolGraphNode::getX() { return x; }
float SchoolGraphNode::getY() { return y; }
GraphEdge* SchoolGraphNode::getEdgeHead() { return edgeHead; }
void SchoolGraphNode::setID(int i) { id = i; }
void SchoolGraphNode::setSchoolID(string sid) { schoolID = sid; }
void SchoolGraphNode::setX(float xCoord) { x = xCoord; }
void SchoolGraphNode::setY(float yCoord) { y = yCoord; }
void SchoolGraphNode::setEdgeHead(GraphEdge* edge) { edgeHead = edge; }
void SchoolGraphNode::addEdge(int to, int weight) {
    GraphEdge* newEdge = new GraphEdge(to, weight);
    newEdge->setNext(edgeHead);
    edgeHead = newEdge;
}