//Abdullah Noor
#include "AirportRailGraphNode.h"

AirportRailGraphNode::AirportRailGraphNode() :id(-1), name(""), type(""), x(0), y(0), edgeHead(NULL) {}
AirportRailGraphNode::AirportRailGraphNode(int i, string n, string t, float xCoord, float yCoord) :id(i), name(n), type(t), x(xCoord), y(yCoord), edgeHead(NULL) {}
AirportRailGraphNode::~AirportRailGraphNode() {
    GraphEdge* curr = edgeHead;
    while (curr != NULL) {
        GraphEdge* nxt = curr->getNext(); delete curr; curr = nxt;
    }
}
void AirportRailGraphNode::setID(int i) { id = i; }
void AirportRailGraphNode::setName(string n) { name = n; }
void AirportRailGraphNode::setType(string t) { type = t; }
void AirportRailGraphNode::setX(float xCoord) { x = xCoord; }
void AirportRailGraphNode::setY(float yCoord) { y = yCoord; }
void AirportRailGraphNode::setEdgeHead(GraphEdge* edge) { edgeHead = edge; }
void AirportRailGraphNode::addEdge(int to, int weight) {
    GraphEdge* newEdge = new GraphEdge(to, weight);
    newEdge->setNext(edgeHead);
    edgeHead = newEdge;
}