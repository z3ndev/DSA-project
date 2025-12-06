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

    // Helper function to convert string to lowercase
    string toLowercase(const string& str) const {
        string result = str;
        for (size_t i = 0; i < result.length(); i++) {
            if (result[i] >= 'A' && result[i] <= 'Z') {
                result[i] = result[i] + ('a' - 'A');
            }
        }
        return result;
    }

    int hashFunction(string key) {
        // Convert key to lowercase for case-insensitive hashing
        key = toLowercase(key);
        
        int p = 31;
        int hashValue = 0;
        long long pPower = 1;

        for (char c : key) {
            // Handle all characters safely (already lowercase)
            int charValue = (c >= 'a' && c <= 'z') ? (c - 'a' + 1) : 
                           (c >= '0' && c <= '9') ? (c - '0' + 27) : 
                           1; // Default value for special chars
            
            hashValue = (hashValue + charValue * pPower) % size;
            pPower = (pPower * p) % size;
        }
        
        // Ensure non-negative result
        return (hashValue % size + size) % size;
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
        int index = hashFunction(productName); // Already converts to lowercase
        ProductNode* newNode = new ProductNode(productName, category, price);
        newNode->setNext(table[index]);
        table[index] = newNode;
    }

    ProductNode* searchByName(string productName) {
        int index = hashFunction(productName); // Already converts to lowercase
        ProductNode* current = table[index];
        
        // Case-insensitive comparison
        string lowerSearchName = toLowercase(productName);

        while (current) {
            if (toLowercase(current->getProductName()) == lowerSearchName)
                return current;
            current = current->getNext();
        }
        return NULL;
    }

    void searchByCategory(string category) {
        cout << "Products in category " << category << ":\n";
        bool found = false;
        
        // Case-insensitive comparison
        string lowerCategory = toLowercase(category);

        for (int i = 0; i < size; i++) {
            ProductNode* current = table[i];
            while (current) {
                if (toLowercase(current->getCategory()) == lowerCategory) {
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
