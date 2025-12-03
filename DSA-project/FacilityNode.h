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
    FacilityNode(string i, string t, float xCoord, float yCoord) :id(i), type(t), x(xCoord), y(yCoord), next(NULL) {}

    string getID() { return id; }
    string getType() { return type; }
    float getX() { return x; }
    float getY() { return y; }
    FacilityNode* getNext() { return next; }

    void setNext(FacilityNode* node) { next = node; }

    void display() {
        cout << "Facility ID: " << id << endl;
        cout << "Type: " << type << endl;
        cout << "Coordinates: (" << x << ", " << y << ")\n";
    }
};

#endif
