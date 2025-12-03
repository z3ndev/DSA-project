// Abdullah Noor
#ifndef PRODUCTHASHTABLE_H
#define PRODUCTHASHTABLE_H

#include <iostream>
using namespace std;
#include "ProductNode.h"

class ProductHashTable {
private:
    ProductNode** table;
    int size;

    int hashFunction(string key)  {
        int p = 31;
        int hashValue = 0, pPower = 1;

        for (char c : key) {
            hashValue = (hashValue + (c - 'a' + 1) * pPower) % size;
            pPower = (pPower * p) % size;
        }
        return hashValue;
    }

public:
    ProductHashTable(int s = 100) :size(s) {
        table = new ProductNode * [size];
        for (int i = 0; i < size; i++)
            table[i] = NULL;
    }

    ~ProductHashTable() {
        for (int i = 0; i < size; i++) {
            ProductNode* current = table[i];
            while (current) {
                ProductNode* next = current->getNext();
                delete current;
                current = next;
            }
        }
        delete[] table;
    }

    void insert(string productName, string category, int price) {
        int index = hashFunction(productName);
        ProductNode* newNode = new ProductNode(productName, category, price);
        newNode->setNext(table[index]);
        table[index] = newNode;
    }

    ProductNode* searchByName(string productName) {
        int index = hashFunction(productName);
        ProductNode* current = table[index];

        while (current) {
            if (current->getProductName() == productName)
                return current;
            current = current->getNext();
        }
        return NULL;
    }

    void searchByCategory(string category) {
        cout << "Products in category " << category << ":\n";
        bool found = false;

        for (int i = 0; i < size; i++) {
            ProductNode* current = table[i];
            while (current) {
                if (current->getCategory() == category) {
                    current->display();
                    found = true;
                }
                current = current->getNext();
            }
        }

        if (!found)
            cout << "  No products found in this category.\n";
    }

    void displayAll() {
        for (int i = 0; i < size; i++) {
            ProductNode* current = table[i];
            while (current) {
                current->display();
                current = current->getNext();
            }
        }
    }
};

#endif
