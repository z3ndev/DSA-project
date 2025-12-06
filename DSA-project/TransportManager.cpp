//Maaz Tahir
#include "TransportManager.h"
#include <iostream>
using namespace std;

// ADD THIS - Helper function for case-insensitive comparison
string TransportManager::toLowercase(const string& str) const {
    string result = str;
    for (size_t i = 0; i < result.length(); i++) {
        if (result[i] >= 'A' && result[i] <= 'Z') {
            result[i] = result[i] + ('a' - 'A');
        }
    }
    return result;
}

TransportManager::TransportManager(int busTableCapacity, int maxStops) 
{
    buses = new BusHashTable(busTableCapacity);
    busList = new BusList();
    stopsGraph = new TGraph(maxStops);
    dijkstra = new TDijkstra(stopsGraph);
}

TransportManager::~TransportManager()
{
    delete busList;
    delete buses;
    delete dijkstra;
    delete stopsGraph;
}

// --- Bus management ---
void TransportManager::registerBus(TBus* bus) 
{
    buses->insert(bus);
    busList->addBus(bus);
}

TBus* TransportManager::getBus(const string& busNo) 
{
    // UPDATED - Case-insensitive search
    string lowerBusNo = toLowercase(busNo);
    
    // Search through BusList with case-insensitive comparison
    BusListNode* current = busList->getHead();
    while (current != nullptr) {
        if (toLowercase(current->bus->getBusNo()) == lowerBusNo) {
            return current->bus;
        }
        current = current->next;
    }
    return nullptr;
}

void TransportManager::removeBus(const string& busNo)
{
    buses->remove(busNo);
    busList->removeBus(busNo);
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
    TBus* bus = getBus(busNo);  // Already case-insensitive
    if (!bus) {
        cout << "Bus " << busNo << " not found.\n";
        return;
    }
    
    // UPDATED - Case-insensitive stop validation
    string lowerStopID = toLowercase(stopID);
    
    // Check if stop exists in graph
    double lat, lon;
    bool stopExists = false;
    
    // Search through all nodes
    int nodeCount = stopsGraph->getNodeCount();
    string* allStops = new string[nodeCount];
    stopsGraph->getAllNodeIDs(allStops);
    
    for (int i = 0; i < nodeCount; i++) {
        if (toLowercase(allStops[i]) == lowerStopID) {
            stopExists = true;
            // Use the actual stop ID from graph (preserves original case)
            bus->getTravelHistory()->push(allStops[i]);
            bus->setCurrentStop(allStops[i]);
            cout << "Bus " << busNo << " moved to " << allStops[i] << endl;
            break;
        }
    }
    
    delete[] allStops;
    
    if (!stopExists) {
        cout << "Stop " << stopID << " not found in the system!\n";
    }
}

// --- Shortest path ---
double TransportManager::getShortestDistance(const string& from, const string& to) {
    int nodeCount = stopsGraph->getNodeCount();
    if (nodeCount == 0) return -1;

    string* ids = new string[nodeCount];
    double* dist = new double[nodeCount];
    stopsGraph->getAllNodeIDs(ids);
    
    // UPDATED - Case-insensitive search for stops
    string lowerFrom = toLowercase(from);
    string lowerTo = toLowercase(to);
    
    string actualFrom = "", actualTo = "";
    
    for (int i = 0; i < nodeCount; i++) {
        if (toLowercase(ids[i]) == lowerFrom) {
            actualFrom = ids[i];
        }
        if (toLowercase(ids[i]) == lowerTo) {
            actualTo = ids[i];
        }
    }
    
    if (actualFrom.empty() || actualTo.empty()) {
        delete[] ids;
        delete[] dist;
        return -1;
    }

    dijkstra->compute(actualFrom, ids, dist, nodeCount);

    double result = -1;
    for (int i = 0; i < nodeCount; i++) {
        if (ids[i] == actualTo) {
            result = dist[i];
            break;
        }
    }

    delete[] ids;
    delete[] dist;
    return result;
}

// --- Find Nearest Bus ---
TBus* TransportManager::findNearestBus(double passengerLat, double passengerLon, double* outDistance) {
    return busList->findNearestBusByCoordinates(passengerLat, passengerLon, outDistance, stopsGraph);
}

// --- CSV Loading Methods ---

bool TransportManager::loadStopsFromCSV(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file: " << filename << endl;
        return false;
    }

    string line;
    getline(file, line); // Skip header

    while (getline(file, line)) {
        if (line.empty()) continue;
        
        stringstream ss(line);
        string stopID, name, coordStr;

        getline(ss, stopID, ',');
        getline(ss, name, ',');
        getline(ss, coordStr);

        // Parse coordinates (quoted "lat, lon")
        if (!coordStr.empty() && coordStr.front() == '"' && coordStr.back() == '"') {
            coordStr = coordStr.substr(1, coordStr.length() - 2);
        }

        double latitude = 0.0, longitude = 0.0;
        stringstream coordStream(coordStr);
        string latStr, lonStr;
        if (getline(coordStream, latStr, ',') && getline(coordStream, lonStr)) {
            size_t start = latStr.find_first_not_of(" \t\r\n");
            size_t end = latStr.find_last_not_of(" \t\r\n");
            if (start != string::npos && end != string::npos) {
                latStr = latStr.substr(start, end - start + 1);
            }
            start = lonStr.find_first_not_of(" \t\r\n");
            end = lonStr.find_last_not_of(" \t\r\n");
            if (start != string::npos && end != string::npos) {
                lonStr = lonStr.substr(start, end - start + 1);
            }
            try { latitude = stod(latStr); } catch (...) { latitude = 0.0; }
            try { longitude = stod(lonStr); } catch (...) { longitude = 0.0; }
        }

        addStop(stopID, name, latitude, longitude);
    }
    file.close();
    return true;
}

bool TransportManager::loadStopEdgesFromCSV(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file: " << filename << endl;
        return false;
    }

    string line;
    getline(file, line); // Skip header

    while (getline(file, line)) {
        if (line.empty()) continue;
        
        stringstream ss(line);
        string fromStopID, toStopID, distanceStr;

        getline(ss, fromStopID, ',');
        getline(ss, toStopID, ',');
        getline(ss, distanceStr);

        double distance = 0.0;
        try { distance = stod(distanceStr); } catch (...) { distance = 0.0; }

        addRouteEdge(fromStopID, toStopID, distance);
    }
    file.close();
    return true;
}

bool TransportManager::loadBusesFromCSV(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file: " << filename << endl;
        return false;
    }

    string line;
    getline(file, line); // Skip header

    while (getline(file, line)) {
        if (line.empty()) continue;
        
        stringstream ss(line);
        string busNo, company, currentStop, routeStr;

        getline(ss, busNo, ',');
        getline(ss, company, ',');
        getline(ss, currentStop, ',');
        getline(ss, routeStr);

        // Remove quotes from route if present
        if (!routeStr.empty() && routeStr.front() == '"' && routeStr.back() == '"') {
            routeStr = routeStr.substr(1, routeStr.length() - 2);
        }

        TBus* bus = new TBus(busNo, company, currentStop);

        // Parse route (format: "Stop1 > Stop2 > Stop3")
        stringstream routeStream(routeStr);
        string stopID;
        
        while (getline(routeStream, stopID, '>')) {
            size_t start = stopID.find_first_not_of(" \t\r\n");
            size_t end = stopID.find_last_not_of(" \t\r\n");
            if (start != string::npos && end != string::npos) {
                stopID = stopID.substr(start, end - start + 1);
                bus->addRouteStop(stopID);
            }
        }

        registerBus(bus);
    }
    file.close();
    return true;
}

// --- Display ---
void TransportManager::printAllBuses() const {
    busList->printAll();
}

void TransportManager::printBusHistory(const string& busNo) const {
    // UPDATED - Use case-insensitive search
    TransportManager* nonConstThis = const_cast<TransportManager*>(this);
    TBus* bus = nonConstThis->getBus(busNo);
    
    if (!bus) {
        cout << "Bus " << busNo << " not found.\n";
        return;
    }
    cout << "\n=== Travel History for Bus " << busNo << " ===\n";
    bus->getTravelHistory()->printHistory();
}

void TransportManager::printAllStops() const {
    cout << "\n===== All Bus Stops =====\n";
    stopsGraph->printGraph();
    cout << "=========================\n";
}
