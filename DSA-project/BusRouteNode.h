//Maaz Tahir
#pragma once
#include <string>
using namespace std;

class BusRouteNode {
public:
    string stopID;
    BusRouteNode* next;

    BusRouteNode(const string& stopID);
};
