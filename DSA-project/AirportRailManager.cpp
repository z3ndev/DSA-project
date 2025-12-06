//Abdullah Noor
#include "AirportRailManager.h"

AirportRailManager::AirportRailManager(int capacity) {
    graph = new AirportRailGraph(capacity);
    nodeMapCapacity = capacity;
    nodeMapSize = 0;
    nodeNames = new string[nodeMapCapacity];
    nodeIDs = new int[nodeMapCapacity];
}

AirportRailManager::~AirportRailManager() {
    delete graph;
    delete[] nodeNames;
    delete[] nodeIDs;
}

string AirportRailManager::toLowercase(const string& str) const {
    string result = str;
    for (size_t i = 0; i < result.length(); i++) {
        if (result[i] >= 'A' && result[i] <= 'Z') {
            result[i] = result[i] + ('a' - 'A');
        }
    }
    return result;
}

void AirportRailManager::addToNodeMap(const string& name, int id) {
    if (nodeMapSize >= nodeMapCapacity) {
        // Resize
        nodeMapCapacity *= 2;
        string* newNames = new string[nodeMapCapacity];
        int* newIDs = new int[nodeMapCapacity];
        for (int i = 0; i < nodeMapSize; i++) {
            newNames[i] = nodeNames[i];
            newIDs[i] = nodeIDs[i];
        }
        delete[] nodeNames;
        delete[] nodeIDs;
        nodeNames = newNames;
        nodeIDs = newIDs;
    }
    nodeNames[nodeMapSize] = name;
    nodeIDs[nodeMapSize] = id;
    nodeMapSize++;
}

int AirportRailManager::getNodeID(const string& name) const {
    string lowerName = toLowercase(name);
    for (int i = 0; i < nodeMapSize; i++) {
        if (toLowercase(nodeNames[i]) == lowerName) {
            return nodeIDs[i];
        }
    }
    return -1;
}

bool AirportRailManager::loadNodesFromCSV(const string& filename) {
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
        string name, type, xStr, yStr;

        getline(ss, name, ',');
        getline(ss, type, ',');
        getline(ss, xStr, ',');
        getline(ss, yStr);

        // Trim whitespace
        size_t start = name.find_first_not_of(" \t\r\n");
        size_t end = name.find_last_not_of(" \t\r\n");
        if (start != string::npos && end != string::npos) {
            name = name.substr(start, end - start + 1);
        }
        
        start = type.find_first_not_of(" \t\r\n");
        end = type.find_last_not_of(" \t\r\n");
        if (start != string::npos && end != string::npos) {
            type = type.substr(start, end - start + 1);
        }

        float x = 0.0f, y = 0.0f;
        try { x = stof(xStr); } catch (...) { x = 0.0f; }
        try { y = stof(yStr); } catch (...) { y = 0.0f; }

        int nodeID = graph->addNode(name, type, x, y);
        addToNodeMap(name, nodeID);
    }
    
    file.close();
    return true;
}

bool AirportRailManager::loadEdgesFromCSV(const string& filename) {
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
        string fromName, toName, weightStr;

        getline(ss, fromName, ',');
        getline(ss, toName, ',');
        getline(ss, weightStr);

        // Trim whitespace
        size_t start = fromName.find_first_not_of(" \t\r\n");
        size_t end = fromName.find_last_not_of(" \t\r\n");
        if (start != string::npos && end != string::npos) {
            fromName = fromName.substr(start, end - start + 1);
        }
        
        start = toName.find_first_not_of(" \t\r\n");
        end = toName.find_last_not_of(" \t\r\n");
        if (start != string::npos && end != string::npos) {
            toName = toName.substr(start, end - start + 1);
        }

        int weight = 0;
        try { weight = stoi(weightStr); } catch (...) { weight = 0; }

        int fromID = getNodeID(fromName);
        int toID = getNodeID(toName);

        if (fromID != -1 && toID != -1) {
            graph->addEdge(fromID, toID, weight);
        } else {
            cout << "Warning: Edge between " << fromName << " and " << toName 
                 << " skipped (node not found)\n";
        }
    }
    
    file.close();
    return true;
}

void AirportRailManager::displayGraph() const {
    graph->display();
}

bool AirportRailManager::findShortestRoute(const string& fromName, const string& toName, 
                                           string* path, int& pathLength, int& totalDistance) {
    int fromID = getNodeID(fromName);
    int toID = getNodeID(toName);
    
    if (fromID == -1 || toID == -1) {
        cout << "One or both locations not found!\n";
        return false;
    }
    
    graph->shortestRoute(fromID, toID, path, pathLength, totalDistance);
    
    if (pathLength == 0 || totalDistance == INT_MAX) {
        cout << "No route found between locations.\n";
        return false;
    }
    
    return true;
}

int AirportRailManager::getNodeCount() const {
    return nodeMapSize;
}