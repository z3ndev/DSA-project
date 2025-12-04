//Maaz Tahir
#include "BusRouteNode.h"

BusRouteNode::BusRouteNode(const string& stopID) {
    this->stopID = stopID;
    next = nullptr;
}
