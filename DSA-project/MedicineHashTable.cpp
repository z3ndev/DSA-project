#include "MedicineHashTable.h"
#include <iostream>
#include <algorithm>
using namespace std;

// Constructor
MedicineHashTable::MedicineHashTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        table[i] = nullptr;
    }
}

// Convert string to lowercase
string MedicineHashTable::toLowercase(const string& str) const {
    string result = str;
    for (size_t i = 0; i < result.length(); i++) {
        if (result[i] >= 'A' && result[i] <= 'Z') {
            result[i] = result[i] + ('a' - 'A');
        }
    }
    return result;
}

// Polynomial rolling hash
int MedicineHashTable::computeHash(const string& key) {
    long long hash = 0;
    long long p = 31;
    long long power = 1;

    for (size_t i = 0; i < key.length(); i++) {
        hash = (hash + (key[i] - 'a' + 1) * power) % TABLE_SIZE;
        power = (power * p) % TABLE_SIZE;
    }

    return (int)(hash % TABLE_SIZE);
}

// Insert medicine (separate chaining)
void MedicineHashTable::insert(const Medicine& med) {
    // Convert name to lowercase for hashing
    string lowerName = toLowercase(med.name);
    int index = computeHash(lowerName);

    // Store the original medicine object with original name
    Node* newNode = new Node(med);
    newNode->next = table[index];
    table[index] = newNode;
}

// Search by name (case-insensitive)
Medicine* MedicineHashTable::searchByName(const string& name) {
    // Convert search term to lowercase
    string lowerName = toLowercase(name);
    int index = computeHash(lowerName);

    Node* curr = table[index];
    while (curr != nullptr) {
        // Compare lowercase versions
        if (toLowercase(curr->med.name) == lowerName) {
            return &curr->med;
        }
        curr = curr->next;
    }

    return nullptr; // not found
}

// Destructor
MedicineHashTable::~MedicineHashTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* curr = table[i];
        while (curr != nullptr) {
            Node* next = curr->next;
            delete curr;
            curr = next;
        }
    }
}
