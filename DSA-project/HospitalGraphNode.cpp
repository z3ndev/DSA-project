#include "HospitalGraphNode.h"

HospitalGraphNode::HospitalGraphNode() : id(-1), hospitalID(""), x(0), y(0), edgeHead(NULL) {}

HospitalGraphNode::HospitalGraphNode(int i, string hid, float xCoord, float yCoord) 
    : id(i), hospitalID(hid), x(xCoord), y(yCoord), edgeHead(NULL) {}

HospitalGraphNode::~HospitalGraphNode() {
    GraphEdge* curr = edgeHead;
    while (curr != NULL) {
        GraphEdge* nxt = curr->getNext();
        delete curr;
        curr = nxt;
    }
}

void HospitalGraphNode::setID(int i) { id = i; }
void HospitalGraphNode::setHospitalID(string hid) { hospitalID = hid; }
void HospitalGraphNode::setX(float xCoord) { x = xCoord; }
void HospitalGraphNode::setY(float yCoord) { y = yCoord; }
void HospitalGraphNode::setEdgeHead(GraphEdge* edge) { edgeHead = edge; }

void HospitalGraphNode::addEdge(int to, int weight) {
    GraphEdge* newEdge = new GraphEdge(to, weight);
    newEdge->setNext(edgeHead);
    edgeHead = newEdge;
}