//Abdullah Noor
#include "GraphEdge.h"
#include <iostream>
using namespace std;

GraphEdge::GraphEdge(int t, int w) :to(t), weight(w), next(NULL) {}
GraphEdge::~GraphEdge() {}
int GraphEdge::getTo() { return to; }
int GraphEdge::getWeight() { return weight; }
GraphEdge* GraphEdge::getNext() { return next; }
void GraphEdge::setNext(GraphEdge* edge) { next = edge; }