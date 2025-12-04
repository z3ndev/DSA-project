//Maaz Tahir
#include "BusHashNode.h"

BusHashNode::BusHashNode(TBus* bus) {
    this->bus = bus;
    next = nullptr;
}

BusHashNode::~BusHashNode() {
    // Bus deletion handled by BusHashTable
    next = nullptr;
}
