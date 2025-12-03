#ifndef STREET_H
#define STREET_H

#include <string>
#include "Household.h"
using namespace std;

class Street {
public:
    string streetNo;
    Household* houses;  // first house in the street
    Street* next;       // next street in the sector

    Street(const string& sn);
};

#endif
