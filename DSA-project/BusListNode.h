//Maaz Tahir
#pragma once
#include "TBus.h"

class BusListNode {
public:
    TBus* bus;
    BusListNode* next;

    BusListNode(TBus* bus);
    ~BusListNode();
};