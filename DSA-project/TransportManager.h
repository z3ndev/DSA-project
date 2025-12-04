//Maaz Tahir
#pragma once
#include <string>
#include "TBus.h"
#include "BusHashTable.h"
#include "PassengerQueue.h"
#include "TravelHistory.h"
#include "TGraph.h"
#include "TDijkstra.h"

using namespace std;

class TransportManager {
private:
    BusHashTable* buses;     // Bus lookup
    TGraph* stopsGraph;      // Bus stops
    TDijkstra* dijkstra;     // Shortest path computations

public:
    TransportManager(int busTableCapacity = 100, int maxStops = 100);
    ~TransportManager();

    // Bus management
    void registerBus(TBus* bus);
    TBus* getBus(const string& busNo);
    void removeBus(const string& busNo);

    // Graph management
    void addStop(const string& stopID, const string& name, double lat, double lon);
    void addRouteEdge(const string& from, const string& to, double distance);

    // Travel history
    void moveBus(const string& busNo, const string& stopID);

    // Shortest path
    double getShortestDistance(const string& from, const string& to);

    // Debug / display
    void printAllBuses() const;
    void printBusHistory(const string& busNo) const;
};
