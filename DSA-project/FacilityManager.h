// Abdullah Noor
#ifndef FACILITYMANAGER_H
#define FACILITYMANAGER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <string>
#include "FacilityNode.h"
#include "FacilityGraph.h"

using namespace std;

class FacilityManager {
private:
    static const int MAX_FACILITIES = 100;
    FacilityNode facilities[MAX_FACILITIES];  // Array for facility data storage
    int facilityCount;
    
    FacilityGraph* facilityGraph;  // Graph for Dijkstra routing

public:
    FacilityManager();
    ~FacilityManager();
    
    // Facility registration
    bool addFacility(const FacilityNode& facility);
    FacilityNode* searchFacilityByID(const string& facilityID);
    int getFacilityIndexByID(const string& facilityID);
    void listFacilities(const string& type = "");
    void displayFacilityDetails(const string& facilityID);
    
    // CSV loaders (loads both facility data AND graph)
    bool loadFacilitiesFromCSV(const string& filename);
    bool loadFacilityEdgesFromCSV(const string& filename);
    
    // Nearest facility (coordinate-based - Euclidean for cross-type search)
    FacilityNode* findNearestByCoord(double lat, double lon, const string& type = "", double* outDistance = nullptr);
    
    // Shortest path (graph-based - Dijkstra for facility-to-facility routing)
    bool findShortestPath(const string& startFacilityID, const string& endFacilityID, 
                          string* path, int& pathLength, int& totalDistance);
    
    // Getters
    int getFacilityCount() const { return facilityCount; }
    FacilityNode* getFacilityAt(int index);
    FacilityGraph* getGraph() { return facilityGraph; }
};

#endif