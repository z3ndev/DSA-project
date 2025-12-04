//Maaz Tahir
#pragma once
#include "BusHashNode.h"
#include <string>
using namespace std;

class BusHashTable {
private:
    BusHashNode** table;
    int capacity;

    int hashFunction(const string& busNo) const;

public:
    BusHashTable(int capacity = 101);
    ~BusHashTable();

    void insert(TBus* bus);
    TBus* search(const string& busNo);
    TBus* remove(const string& busNo);
    void print() const;
};
