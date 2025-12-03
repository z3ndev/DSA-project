#ifndef CNIC_HASHTABLE_H
#define CNIC_HASHTABLE_H

#include "Citizen.h"

class CNICNode {
public:
    Citizen* data;
    CNICNode* next;
    CNICNode(Citizen* c);
};

class CNICHashTable {
private:
    static const int TABLE_SIZE = 50;
    CNICNode* table[TABLE_SIZE];
    int hashFunction(const string& cnic);

public:
    CNICHashTable();
    void insert(Citizen* c);
    Citizen* search(const string& cnic);
};

#endif
