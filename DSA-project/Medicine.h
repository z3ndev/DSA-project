#ifndef MEDICINE_H
#define MEDICINE_H

#include <string>
using namespace std;

class Medicine {
public:
    string name;
    string formula;
    int price;

    Medicine() {
        name = "";
        formula = "";
        price = 0;
    }
};

#endif