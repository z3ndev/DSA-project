// Abdullah Noor

#ifndef PRODUCTNODE_H
#define PRODUCTNODE_H

#include <iostream>
using namespace std;

class ProductNode {
private:
    string productName, category;
    int price;
    ProductNode* next;

public:
    ProductNode(string name, string cat, int p) :productName(name), category(cat), price(p), next(NULL) {}

    string getProductName() { return productName; }
    string getCategory() { return category; }
    int getPrice() { return price; }
    ProductNode* getNext() { return next; }

    void setNext(ProductNode* node) { next = node; }

    void display() {
        cout << "  Name: " << productName
            << ", Category: " << category
            << ", Price: " << price << endl;
    }
};

#endif