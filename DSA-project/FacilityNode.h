// Abdullah Noor
#ifndef FACILITYNODE_H
#define FACILITYNODE_H

#include <iostream>
using namespace std;

class FacilityNode {
private:
    string id, type;
    float x, y;
    FacilityNode* next;

public:
    // Default constructor
    FacilityNode() : id(""), type(""), x(0), y(0), next(NULL) {}
    
    // Parameterized constructor
    FacilityNode(string i, string t, float xCoord, float yCoord) 
        : id(i), type(t), x(xCoord), y(yCoord), next(NULL) {}

    string getID() const { return id; }
    string getType() const { return type; }
    float getX() const { return x; }
    float getY() const { return y; }
    FacilityNode* getNext() { return next; }

    void setNext(FacilityNode* node) { next = node; }

    void display() const {
        cout << "Facility ID: " << id << endl;
        cout << "Type: " << type << endl;
        cout << "Coordinates: (" << x << ", " << y << ")\n";
    }
};

#endif
