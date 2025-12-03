#include "MedicineFormulaHashTable.h"
#include <iostream>
using namespace std;

MedicineFormulaHashTable::MedicineFormulaHashTable() {
    for (int i = 0; i < TABLE_SIZE; i++) table[i] = nullptr;
}

// Convert string to lowercase
string MedicineFormulaHashTable::toLowercase(const string& str) const {
    string result = str;
    for (size_t i = 0; i < result.length(); i++) {
        if (result[i] >= 'A' && result[i] <= 'Z') {
            result[i] = result[i] + ('a' - 'A');
        }
    }
    return result;
}

int MedicineFormulaHashTable::computeHash(const string& key) {
    long long hash = 0;
    long long p = 31;
    long long power = 1;

    for (size_t i = 0; i < key.length(); i++) {
        hash = (hash + (key[i] - 'a' + 1) * power) % TABLE_SIZE;
        power = (power * p) % TABLE_SIZE;
    }
    return (int)(hash % TABLE_SIZE);
}

void MedicineFormulaHashTable::insert(const Medicine& med) {
    // Convert formula to lowercase for hashing
    string lowerFormula = toLowercase(med.formula);
    int index = computeHash(lowerFormula);
    
    // Store the original medicine object with original formula
    Node* newNode = new Node(med);
    newNode->next = table[index];
    table[index] = newNode;
}

Medicine* MedicineFormulaHashTable::searchByFormula(const string& formula) {
    // Convert search term to lowercase
    string lowerFormula = toLowercase(formula);
    int index = computeHash(lowerFormula);
    
    Node* curr = table[index];
    while (curr) {
        // Compare lowercase versions
        if (toLowercase(curr->med.formula) == lowerFormula) {
            return &curr->med;
        }
        curr = curr->next;
    }
    return nullptr;
}

MedicineFormulaHashTable::~MedicineFormulaHashTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* curr = table[i];
        while (curr) {
            Node* next = curr->next;
            delete curr;
            curr = next;
        }
    }
}
