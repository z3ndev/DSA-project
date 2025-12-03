#include "Sector.h"

Sector::Sector(const string& sname) {
    sectorName = sname;
    streets = nullptr;
    next = nullptr;
}
