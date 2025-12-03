#ifndef MEDICINE_FORMULA_HASH_TABLE_H
#define MEDICINE_FORMULA_HASH_TABLE_H

#include "Medicine.h"

class MedicineFormulaHashTable {
private:
    struct Node {
        Medicine med;
        Node* next;
        Node(const Medicine& m) {
            med = m;
            next = nullptr;
        }
    };

    static const int TABLE_SIZE = 101;
    Node* table[TABLE_SIZE];

    int computeHash(const std::string& key);
    std::string toLowercase(const std::string& str) const;

public:
    MedicineFormulaHashTable();
    void insert(const Medicine& med);
    Medicine* searchByFormula(const std::string& formula);
    ~MedicineFormulaHashTable();
};

#endif
