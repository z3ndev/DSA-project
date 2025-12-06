//Maaz Tahir
#pragma once
#include "BusListNode.h"
#include "TGraph.h"
#include <string>
#include <iostream>
#include <cmath>
using namespace std;

class BusList {
private:
    BusListNode* head;
    BusListNode* tail;
    int count;

public:
    BusList();
    ~BusList();

    // Add operations
    void addBus(TBus* bus);
    void insertAtBeginning(TBus* bus);
    void insertAtEnd(TBus* bus);

    // Remove operations
    bool removeBus(const string& busNo);
    TBus* removeFirst();
    TBus* removeLast();

    // Search operations
    TBus* searchByBusNo(const string& busNo);
    TBus* findNearestBusByStop(const string& stopID);
    
    // Find nearest bus to passenger coordinates (Euclidean distance)
    TBus* findNearestBusByCoordinates(double lat, double lon, 
                                      double* outDistance = nullptr,
                                      TGraph* stopsGraph = nullptr);

    // Utility
    bool isEmpty() const;
    int getCount() const;
    void clear();

    // Display
    void printAll() const;
    void printBusDetails(const string& busNo) const;

    // Iterator support
    BusListNode* getHead() const { return head; }
};