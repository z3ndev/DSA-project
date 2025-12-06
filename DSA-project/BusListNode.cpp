//Maaz Tahir
#include "BusListNode.h"

BusListNode::BusListNode(TBus* bus) {
    this->bus = bus;
    this->next = nullptr;
}

BusListNode::~BusListNode() {
    // Don't delete bus here - managed by the list
}