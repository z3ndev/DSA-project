#ifndef SECTOR_H
#define SECTOR_H

#include <string>
#include "Street.h"
using namespace std;

class Sector {
public:
    string sectorName;
    Street* streets;  // first street in sector
    Sector* next;     // next sector in city

    Sector(const string& sname);
};

#endif
