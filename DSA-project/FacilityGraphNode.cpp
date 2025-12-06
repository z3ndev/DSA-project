//Abdullah Noor
#include "FacilityGraphNode.h"

FacilityGraphNode::FacilityGraphNode() :id(-1), facilityID(""), type(""), x(0), y(0), edgeHead(NULL) {}
FacilityGraphNode::FacilityGraphNode(int i, string fid, string t, float xCoord, float yCoord) :id(i), facilityID(fid), type(t), x(xCoord), y(yCoord), edgeHead(NULL) {}
FacilityGraphNode::~FacilityGraphNode() {
    GraphEdge* curr = edgeHead;
    while (curr != NULL) {
        GraphEdge* nxt = curr->getNext(); delete curr; curr = nxt;
    }
}
void FacilityGraphNode::setID(int i) { id = i; }
void FacilityGraphNode::setFacilityID(string fid) { facilityID = fid; }
void FacilityGraphNode::setType(string t) { type = t; }
void FacilityGraphNode::setX(float xCoord) { x = xCoord; }
void FacilityGraphNode::setY(float yCoord) { y = yCoord; }
void FacilityGraphNode::setEdgeHead(GraphEdge* edge) { edgeHead = edge; }
void FacilityGraphNode::addEdge(int to, int weight) {
    GraphEdge* newEdge = new GraphEdge(to, weight);
    newEdge->setNext(edgeHead);
    edgeHead = newEdge;
}