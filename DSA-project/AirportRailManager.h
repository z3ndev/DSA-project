//Abdullah Noor
#ifndef AIRPORTRAILMANAGER_H
#define AIRPORTRAILMANAGER_H

#include "AirportRailGraph.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

class AirportRailManager {
private:
    AirportRailGraph* graph;
    
    // Helper to convert string to lowercase
    string toLowercase(const string& str) const;
    
    // Node ID mapping (name -> index)
    string* nodeNames;
    int* nodeIDs;
    int nodeMapSize;
    int nodeMapCapacity;
    
    void addToNodeMap(const string& name, int id);
    int getNodeID(const string& name) const;

public:
    AirportRailManager(int capacity = 50);
    ~AirportRailManager();
    
    // CSV Loading
    bool loadNodesFromCSV(const string& filename);
    bool loadEdgesFromCSV(const string& filename);
    
    // Operations
    void displayGraph() const;
    bool findShortestRoute(const string& fromName, const string& toName, 
                          string* path, int& pathLength, int& totalDistance);
    
    // Getters
    AirportRailGraph* getGraph() { return graph; }
    int getNodeCount() const;
};

#endif