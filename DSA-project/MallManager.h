// Abdullah Noor
#ifndef MALLMANAGER_H
#define MALLMANAGER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <string>
#include "MallNode.h"
#include "MallGraph.h"

using namespace std;

class MallManager {
private:
    static const int MAX_MALLS = 50;
    MallNode malls[MAX_MALLS];  // Array for mall data storage
    int mallCount;
    
    MallGraph* mallGraph;  // Graph for Dijkstra routing

public:
    MallManager();
    ~MallManager();
    
    // Mall registration
    bool addMall(const MallNode& mall);
    MallNode* searchMallByID(const string& mallID);
    int getMallIndexByID(const string& mallID);
    void listMalls();
    void displayMallDetails(const string& mallID);
    
    // Product operations (hash table)
    bool addProductToMall(const string& mallID, const string& productName, const string& category, int price);
    void searchProductByName(const string& productName);
    void searchProductsByCategory(const string& category);
    
    // CSV loaders (loads both mall data AND graph)
    bool loadMallsFromCSV(const string& filename);
    bool loadProductsFromCSV(const string& filename);
    bool loadMallEdgesFromCSV(const string& filename);
    
    // Nearest mall (coordinate-based - Euclidean for cross-type search)
    MallNode* findNearestByCoord(double lat, double lon, double* outDistance = nullptr);
    
    // Shortest path (graph-based - Dijkstra for mall-to-mall routing)
    bool findShortestPath(const string& startMallID, const string& endMallID, 
                          string* path, int& pathLength, int& totalDistance);
    
    // Getters
    int getMallCount() const { return mallCount; }
    MallNode* getMallAt(int index);
    MallGraph* getGraph() { return mallGraph; }
};

#endif