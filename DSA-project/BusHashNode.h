//Maaz Tahir
#pragma once
#include "TBus.h"

class BusHashNode {
public:
    TBus* bus;
    BusHashNode* next;

    BusHashNode(TBus* bus);
    ~BusHashNode();
};
