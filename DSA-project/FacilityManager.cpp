// Abdullah Noor
#include "FacilityManager.h"

// Helper function to convert string to lowercase
static string toLowercase(const string& str) {
    string result = str;
    for (size_t i = 0; i < result.length(); i++) {
        if (result[i] >= 'A' && result[i] <= 'Z') {
            result[i] = result[i] + ('a' - 'A');
        }
    }
    return result;
}

FacilityManager::FacilityManager() : facilityCount(0) {
    facilityGraph = new FacilityGraph(MAX_FACILITIES);
}

FacilityManager::~FacilityManager() {
    delete facilityGraph;
}

bool FacilityManager::addFacility(const FacilityNode& facility) {
    if (facilityCount >= MAX_FACILITIES) {
        cout << "Facility storage full.\n";
        return false;
    }
    
    // Add to facility data array
    facilities[facilityCount] = facility;
    
    // Add to graph for Dijkstra
    facilityGraph->addNode(facility.getID(), facility.getType(), facility.getX(), facility.getY());
    
    facilityCount++;
    return true;
}

FacilityNode* FacilityManager::searchFacilityByID(const string& facilityID) {
    // Case-insensitive search
    string lowerSearchID = toLowercase(facilityID);
    
    for (int i = 0; i < facilityCount; i++) {
        if (toLowercase(facilities[i].getID()) == lowerSearchID) {
            return &facilities[i];
        }
    }
    return NULL;
}

int FacilityManager::getFacilityIndexByID(const string& facilityID) {
    // Case-insensitive search
    string lowerSearchID = toLowercase(facilityID);
    
    for (int i = 0; i < facilityCount; i++) {
        if (toLowercase(facilities[i].getID()) == lowerSearchID) {
            return i;
        }
    }
    return -1;
}

void FacilityManager::listFacilities(const string& type) {
    cout << "\n===== Facility List";
    if (!type.empty()) {
        cout << " (Type: " << type << ")";
    }
    cout << " =====\n";
    
    int displayCount = 0;
    for (int i = 0; i < facilityCount; i++) {
        if (type.empty() || facilities[i].getType() == type) {
            cout << (++displayCount) << ") ID: " << facilities[i].getID()
                 << " | Type: " << facilities[i].getType()
                 << " | Coordinates: (" << facilities[i].getX() << ", " << facilities[i].getY() << ")\n";
        }
    }
    
    if (displayCount == 0) {
        cout << "No facilities found";
        if (!type.empty()) {
            cout << " of type '" << type << "'";
        }
        cout << ".\n";
    }
    cout << "=======================\n";
}

void FacilityManager::displayFacilityDetails(const string& facilityID) {
    FacilityNode* facility = searchFacilityByID(facilityID);
    if (facility) {
        facility->display();
    } else {
        cout << "Facility not found!\n";
    }
}

bool FacilityManager::loadFacilitiesFromCSV(const string& filename) {
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
        string id, type, name, sector, latStr, lonStr;

        getline(ss, id, ',');
        getline(ss, type, ',');
        getline(ss, name, ',');
        getline(ss, sector, ',');
        getline(ss, latStr, ',');
        getline(ss, lonStr);

        float latitude = 0.0f, longitude = 0.0f;
        try { latitude = stof(latStr); } catch (...) { latitude = 0.0f; }
        try { longitude = stof(lonStr); } catch (...) { longitude = 0.0f; }

        FacilityNode facility(id, type, latitude, longitude);
        addFacility(facility);
    }
    file.close();
    return true;
}

bool FacilityManager::loadFacilityEdgesFromCSV(const string& filename) {
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
        string fromFacilityID, toFacilityID, distanceStr;

        getline(ss, fromFacilityID, ',');
        getline(ss, toFacilityID, ',');
        getline(ss, distanceStr);

        int distance = 0;
        try { distance = stoi(distanceStr); } catch (...) { distance = 0; }

        int fromIndex = getFacilityIndexByID(fromFacilityID);
        int toIndex = getFacilityIndexByID(toFacilityID);

        if (fromIndex != -1 && toIndex != -1) {
            facilityGraph->addEdge(fromIndex, toIndex, distance);
        } else {
            cout << "Warning: Edge between " << fromFacilityID << " and " << toFacilityID << " skipped (facility not found)\n";
        }
    }
    file.close();
    return true;
}

FacilityNode* FacilityManager::findNearestByCoord(double lat, double lon, const string& type, double* outDistance) {
    if (facilityCount == 0) return NULL;

    FacilityNode* nearest = NULL;
    double minDistance = 1e18;

    for (int i = 0; i < facilityCount; i++) {
        // Filter by type if specified
        if (!type.empty() && facilities[i].getType() != type) {
            continue;
        }
        
        double distance = sqrt((lat - facilities[i].getX()) * (lat - facilities[i].getX()) +
                               (lon - facilities[i].getY()) * (lon - facilities[i].getY()));
        
        if (distance < minDistance) {
            minDistance = distance;
            nearest = &facilities[i];
        }
    }

    if (outDistance != NULL && nearest != NULL) {
        *outDistance = minDistance;
    }

    return nearest;
}

bool FacilityManager::findShortestPath(const string& startFacilityID, const string& endFacilityID, 
                                       string* path, int& pathLength, int& totalDistance) {
    int startIndex = getFacilityIndexByID(startFacilityID);
    int endIndex = getFacilityIndexByID(endFacilityID);

    if (startIndex == -1 || endIndex == -1) {
        cout << "One or both facilities not found!\n";
        return false;
    }

    facilityGraph->dijkstra(startIndex, endIndex, path, pathLength, totalDistance);
    
    if (pathLength == 0 || totalDistance == INT_MAX) {
        cout << "No path found between facilities.\n";
        return false;
    }
    
    return true;
}

FacilityNode* FacilityManager::getFacilityAt(int index) {
    if (index >= 0 && index < facilityCount) {
        return &facilities[index];
    }
    return NULL;
}