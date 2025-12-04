//Maaz Tahir
#pragma once
#include <string>
#include "TravelHistory.h"
using namespace std;

class TBus {
private:
    string busNo;
    string company;
    string currentStop;

    string* route;
    int routeSize;

    TravelHistory* travelHistory; // add stack for travel history

public:
    TBus();
    TBus(const string& busNo, const string& comp, const string& currStop);
    ~TBus();

    // Setters
    void setBusNo(const string& no);
    void setCompany(const string& comp);
    void setCurrentStop(const string& stopID);

    // Route
    void setRoute(string* stops, int size);
    void addRouteStop(const string& stopID);
    int getRouteSize() const;
    string getRouteStop(int index) const;

    // Getters
    string getBusNo() const;
    string getCompany() const;
    string getCurrentStop() const;
    TravelHistory* getTravelHistory() const; // add getter

    // Display
    void print() const;
};
