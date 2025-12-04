//Maaz Tahir
#include "TransportManager.h"
#include <iostream>
using namespace std;

TransportManager::TransportManager(int busTableCapacity, int maxStops) 
{
    buses = new BusHashTable(busTableCapacity);
    stopsGraph = new TGraph(maxStops);
    dijkstra = new TDijkstra(stopsGraph);
}

TransportManager::~TransportManager()
{
    delete buses;
    delete dijkstra;
    delete stopsGraph;
}

// --- Bus management ---
void TransportManager::registerBus(TBus* bus) 
{
    buses->insert(bus);
}

TBus* TransportManager::getBus(const string& busNo) 
{
    return buses->search(busNo);
}

void TransportManager::removeBus(const string& busNo)
{
    TBus* bus = buses->remove(busNo);
    if (bus) delete bus;
}

// --- Graph management ---
void TransportManager::addStop(const string& stopID, const string& name, double lat, double lon)
{
    stopsGraph->addNode(TGraphNode(stopID, name, lat, lon));
}

void TransportManager::addRouteEdge(const string& from, const string& to, double distance) 
{
    stopsGraph->addEdge(from, to, distance);
}

// --- Travel history ---
void TransportManager::moveBus(const string& busNo, const string& stopID) 
{
    TBus* bus = getBus(busNo);
    if (!bus) {
        cout << "Bus " << busNo << " not found.\n";
        return;
    }

    // Add stop to bus travel history
    bus->getTravelHistory()->push(stopID);
    bus->setCurrentStop(stopID);
}

// --- Shortest path ---
double TransportManager::getShortestDistance(const string& from, const string& to) {
    int nodeCount = stopsGraph->getNodeCount();
    if (nodeCount == 0) return -1;

    string* ids = new string[nodeCount];
    double* dist = new double[nodeCount];
    stopsGraph->getAllNodeIDs(ids);

    dijkstra->compute(from, ids, dist, nodeCount);

    double result = -1;
    for (int i = 0; i < nodeCount; i++) {
        if (ids[i] == to) {
            result = dist[i];
            break;
        }
    }

    delete[] ids;
    delete[] dist;
    return result;
}

// --- Debug / Display ---
void TransportManager::printAllBuses() const {
    buses->print();
}

void TransportManager::printBusHistory(const string& busNo) const {
    TBus* bus = buses->search(busNo);
    if (!bus) {
        cout << "Bus " << busNo << " not found.\n";
        return;
    }
    cout << "Travel History for Bus " << busNo << ": ";
    bus->getTravelHistory()->printHistory();
}
