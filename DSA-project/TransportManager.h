//Maaz Tahir
#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include "TBus.h"
#include "BusHashTable.h"
#include "BusList.h"
#include "PassengerQueue.h"
#include "TravelHistory.h"
#include "TGraph.h"
#include "TDijkstra.h"

using namespace std;

class TransportManager {
private:
    BusHashTable* buses;     // Bus lookup (O(1) hash)
    BusList* busList;        // Bus iteration and nearest search
    TGraph* stopsGraph;      // Bus stops graph
    TDijkstra* dijkstra;     // Shortest path

    // ADD THIS - Helper function for case-insensitive comparison
    string toLowercase(const string& str) const;

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
    
    // Find nearest bus (Euclidean distance)
    TBus* findNearestBus(double passengerLat, double passengerLon, double* outDistance = nullptr);
    
    // CSV Loading
    bool loadStopsFromCSV(const string& filename);
    bool loadStopEdgesFromCSV(const string& filename);
    bool loadBusesFromCSV(const string& filename);

    // Display
    void printAllBuses() const;
    void printBusHistory(const string& busNo) const;
    void printAllStops() const;
    
    // Getters
    TGraph* getGraph() { return stopsGraph; }
    BusList* getBusList() { return busList; }
    int getStopCount() const { return stopsGraph->getNodeCount(); }
    int getBusCount() const { return busList->getCount(); }
};
