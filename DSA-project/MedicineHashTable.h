#ifndef MEDICINEHASHTABLE_H
#define MEDICINEHASHTABLE_H

#include <string>
#include "Medicine.h"
using namespace std;

class MedicineHashTable {
private:
    struct Node {
        Medicine med;
        Node* next;

        Node(const Medicine& m) {
            med = m;
            next = nullptr;
        }
    };

    static const int TABLE_SIZE = 101;  // prime number
    Node* table[TABLE_SIZE];

    int computeHash(const string& key);
    string toLowercase(const string& str) const;

public:
    MedicineHashTable();

    void insert(const Medicine& med);
    Medicine* searchByName(const string& name);
    ~MedicineHashTable();
};

#endif
