#ifndef PHARMACY_H
#define PHARMACY_H

#include <string>
#include "Medicine.h"
using namespace std;

class Pharmacy {
public:
    string id;
    string name;
    string sector;
    Medicine med;

    Pharmacy() {
        id = "";
        name = "";
        sector = "";
    }
};
#endif
