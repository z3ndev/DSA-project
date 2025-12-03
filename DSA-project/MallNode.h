// Abdullah Noor
#ifndef MALLNODE_H
#define MALLNODE_H

#include <iostream>
using namespace std;
#include "ProductHashTable.h"

class MallNode {
private:
    string mallID, name, sector;
    ProductHashTable* productTable;
    MallNode* next;

public:
    MallNode(string id, string n, string s) :mallID(id), name(n), sector(s), next(NULL) {
        productTable = new ProductHashTable();
    }

    ~MallNode() {
        delete productTable;
    }

    string getMallID() { return mallID; }
    string getName() { return name; }
    string getSector() { return sector; }
    ProductHashTable* getProductTable() { return productTable; }
    MallNode* getNext() { return next; }

    void setNext(MallNode* node) { next = node; }

    void display() {
        cout << "Mall ID: " << mallID << endl;
        cout << "Name: " << name << endl;
        cout << "Sector: " << sector << endl;
        cout << "Products:" << endl;
        productTable->displayAll();
    }
};
#endif