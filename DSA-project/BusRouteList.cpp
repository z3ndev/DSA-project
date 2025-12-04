//Maaz Tahir
#include "BusRouteList.h"

BusRouteList::BusRouteList() {
    head = nullptr;
    tail = nullptr;
    size = 0;
}

BusRouteList::~BusRouteList() {
    BusRouteNode* current = head;
    while (current) {
        BusRouteNode* temp = current;
        current = current->next;
        delete temp;
    }
}

void BusRouteList::addStop(const string& stopID) {
    BusRouteNode* newNode = new BusRouteNode(stopID);
    if (!head) {
        head = tail = newNode;
    }
    else {
        tail->next = newNode;
        tail = newNode;
    }
    size++;
}

int BusRouteList::getSize() const {
    return size;
}

void BusRouteList::print() const {
    BusRouteNode* current = head;
    while (current) {
        cout << current->stopID;
        if (current->next) cout << " -> ";
        current = current->next;
    }
}
