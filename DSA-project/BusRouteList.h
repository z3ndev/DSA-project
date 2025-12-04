//Maaz Tahir
#pragma once
#include "BusRouteNode.h"
#include <iostream>
using namespace std;

class BusRouteList {
private:
    BusRouteNode* head;
    BusRouteNode* tail;
    int size;

public:
    BusRouteList();
    ~BusRouteList();

    void addStop(const string& stopID);
    int getSize() const;
    void print() const;
};
