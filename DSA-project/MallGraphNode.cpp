//Abdullah Noor
#include "MallGraphNode.h"
#include <iostream>
using namespace std;
MallGraphNode::MallGraphNode() : id(-1), mallID(""), x(0), y(0), edgeHead(NULL) {}
MallGraphNode::MallGraphNode(int i, string mid, float xCoord, float yCoord)
    : id(i), mallID(mid), x(xCoord), y(yCoord), edgeHead(NULL) {}
MallGraphNode::~MallGraphNode() {
    GraphEdge* current = edgeHead;
    while (current != NULL) {
        GraphEdge* next = current->getNext();
        delete current;
        current = next;
    }
}
int MallGraphNode::getID() { return id; }
string MallGraphNode::getMallID() { return mallID; }
float MallGraphNode::getX() { return x; }
float MallGraphNode::getY() { return y; }
GraphEdge* MallGraphNode::getEdgeHead() { return edgeHead; }
void MallGraphNode::setID(int i) { id = i; }
void MallGraphNode::setMallID(string mid) { mallID = mid; }
void MallGraphNode::setX(float xCoord) { x = xCoord; }
void MallGraphNode::setY(float yCoord) { y = yCoord; }
void MallGraphNode::setEdgeHead(GraphEdge* edge) { edgeHead = edge; }
void MallGraphNode::addEdge(int to, int weight) {
    GraphEdge* newEdge = new GraphEdge(to, weight);
    newEdge->setNext(edgeHead);
    edgeHead = newEdge;
}