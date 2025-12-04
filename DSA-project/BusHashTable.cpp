//Maaz Tahir
#include "BusHashTable.h"
#include <iostream>
using namespace std;

int BusHashTable::hashFunction(const string& busNo) const {
    long long hash = 0;
    long long p = 31;
    long long m = capacity;
    long long power = 1;

    for (char c : busNo) {
        int val;

        // Handle digits
        if (c >= '0' && c <= '9')
            val = c - '0' + 1;
        else if (c >= 'A' && c <= 'Z')
            val = c - 'A' + 11;
        else if (c >= 'a' && c <= 'z')
            val = c - 'a' + 37;
        else
            val = 5;

        hash = (hash + val * power) % m;
        power = (power * p) % m;
    }
    return hash % capacity;
}

BusHashTable::BusHashTable(int capacity) {
    this->capacity = capacity;
    table = new BusHashNode * [capacity];
    for (int i = 0; i < capacity; i++)
        table[i] = nullptr;
}

// Destructor FIXED � does NOT double delete
BusHashTable::~BusHashTable() {
    for (int i = 0; i < capacity; i++) {
        BusHashNode* current = table[i];
        while (current) {
            BusHashNode* temp = current;
            current = current->next;

            delete temp->bus;     // delete bus ONCE
            delete temp;
        }
    }
    delete[] table;
}

void BusHashTable::insert(TBus* bus) {
    int index = hashFunction(bus->getBusNo());
    BusHashNode* newNode = new BusHashNode(bus);
    newNode->next = table[index];
    table[index] = newNode;
}

// Return bus pointer, DO NOT DELETE HERE
TBus* BusHashTable::search(const string& busNo) {
    int index = hashFunction(busNo);
    BusHashNode* current = table[index];

    while (current) {
        if (current->bus->getBusNo() == busNo)
            return current->bus;
        current = current->next;
    }
    return nullptr;
}

// FIXED � NOW RETURNS removed TBus* (caller must delete)
TBus* BusHashTable::remove(const string& busNo) {
    int index = hashFunction(busNo);
    BusHashNode* current = table[index];
    BusHashNode* prev = nullptr;

    while (current) {
        if (current->bus->getBusNo() == busNo) {

            // unlink
            if (prev)
                prev->next = current->next;
            else
                table[index] = current->next;

            TBus* busPtr = current->bus;
            delete current; // only delete node

            return busPtr;  // caller will delete bus
        }
        prev = current;
        current = current->next;
    }

    return nullptr;
}

void BusHashTable::print() const {
    for (int i = 0; i < capacity; i++) {
        BusHashNode* current = table[i];

        if (current)
            cout << "Bucket " << i << ":\n";

        while (current) {
            current->bus->print();
            current = current->next;
        }
    }
}
