// Abdullah Noor
#ifndef MALLNODE_H
#define MALLNODE_H

#include <iostream>
using namespace std;
#include "ProductHashTable.h"

class MallNode {
private:
    string mallID, name, sector;
    double latitude, longitude;
    ProductHashTable* productTable;

public:
    MallNode(string id = "", string n = "", string s = "", double lat = 0.0, double lon = 0.0) 
        :mallID(id), name(n), sector(s), latitude(lat), longitude(lon) {
        productTable = new ProductHashTable();
    }
    
    // Copy constructor - DEEP COPY
    MallNode(const MallNode& other) 
        : mallID(other.mallID), name(other.name), sector(other.sector), 
          latitude(other.latitude), longitude(other.longitude) {
        // Create a new product table (deep copy)
        productTable = new ProductHashTable();
        // Note: Products are NOT copied - each mall starts with empty product list
        // If you need to copy products, you'd need to add a copy method to ProductHashTable
    }
    
    // Assignment operator - DEEP COPY
    MallNode& operator=(const MallNode& other) {
        if (this != &other) {
            mallID = other.mallID;
            name = other.name;
            sector = other.sector;
            latitude = other.latitude;
            longitude = other.longitude;
            
            // Delete old table and create new one
            delete productTable;
            productTable = new ProductHashTable();
            // Note: Products are NOT copied
        }
        return *this;
    }

    ~MallNode() {
        delete productTable;
    }

    string getMallID() const { return mallID; }
    string getName() const { return name; }
    string getSector() const { return sector; }
    double getLatitude() const { return latitude; }
    double getLongitude() const { return longitude; }
    ProductHashTable* getProductTable() { return productTable; }

    void display() const {
        cout << "Mall ID: " << mallID << endl;
        cout << "Name: " << name << endl;
        cout << "Sector: " << sector << endl;
        cout << "Coordinates: (" << latitude << ", " << longitude << ")" << endl;
        cout << "Products:" << endl;
        productTable->displayAll();
    }
};
#endif