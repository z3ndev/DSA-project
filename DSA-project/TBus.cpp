//Maaz Tahir
#include "TBus.h"
#include <iostream>
using namespace std;

TBus::TBus() {
    busNo = "";
    company = "";
    currentStop = "";
    route = nullptr;
    routeSize = 0;
    travelHistory = new TravelHistory(100); // default max 100 stops
}

TBus::TBus(const string& busNo, const string& comp, const string& currStop) {
    this->busNo = busNo;
    this->company = comp;
    this->currentStop = currStop;
    route = nullptr;
    routeSize = 0;
    travelHistory = new TravelHistory(100);
}

TBus::~TBus() {
    delete[] route;
    delete travelHistory;
}

// Setters
void TBus::setBusNo(const string& no) {
    busNo = no;
}

void TBus::setCompany(const string& comp) {
    company = comp;
}

void TBus::setCurrentStop(const string& stopID) {
    currentStop = stopID;
    if (travelHistory)
        travelHistory->push(stopID); // record in travel history
}

// Route functions
void TBus::setRoute(string* stops, int size) {
    delete[] route;
    routeSize = size;
    route = new string[size];
    for (int i = 0; i < size; i++)
        route[i] = stops[i];
}

void TBus::addRouteStop(const string& stopID) {
    string* temp = new string[routeSize + 1];
    for (int i = 0; i < routeSize; i++)
        temp[i] = route[i];
    temp[routeSize] = stopID;
    delete[] route;
    route = temp;
    routeSize++;
}

int TBus::getRouteSize() const {
    return routeSize;
}

string TBus::getRouteStop(int index) const {
    if (index < 0 || index >= routeSize)
        return "";
    return route[index];
}

// Getters
string TBus::getBusNo() const { return busNo; }
string TBus::getCompany() const { return company; }
string TBus::getCurrentStop() const { return currentStop; }
TravelHistory* TBus::getTravelHistory() const { return travelHistory; }

// Display
void TBus::print() const {
    cout << "Bus No: " << busNo
        << ", Company: " << company
        << ", Current Stop: " << currentStop << "\n";
    cout << "Route: ";
    for (int i = 0; i < routeSize; i++) {
        cout << route[i];
        if (i < routeSize - 1)
            cout << " -> ";
    }
    cout << "\n";
}
