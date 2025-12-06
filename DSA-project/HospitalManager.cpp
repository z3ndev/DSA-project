#include "HospitalManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>
#include <climits>

using namespace std;

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

HospitalManager::HospitalManager() : hospitalCount(0) {
    hospitalGraph = new HospitalGraph(MAX_HOSPITALS);
}

HospitalManager::~HospitalManager() {
    delete hospitalGraph;
}

bool HospitalManager::loadFromCSV(const char* filename) {
    ifstream fin(filename);
    if (!fin.is_open()) {
        cerr << "Failed to open " << filename << endl;
        return false;
    }

    string line;
    // Skip header
    if (!getline(fin, line)) {
        fin.close();
        return false;
    }

    // Check if this is actually a header
    bool headerConsumed = (line.find("HospitalID") != string::npos);

    if (!headerConsumed) {
        // Process first line as data
        stringstream ss(line);
        string token;
        Hospital h;

        if (getline(ss, token, ',')) h.id = token;
        if (getline(ss, token, ',')) h.name = token;
        if (getline(ss, token, ',')) h.sector = token;
        if (getline(ss, token, ',')) {
            try {
                h.emergencyBeds = stoi(token);
            } catch (...) { h.emergencyBeds = 0; }
        }
        // Parse specializations (quoted, comma-separated)
        if (getline(ss, token, ',')) {
            string specializationField = token;
            // If starts with quote, read until closing quote
            if (!specializationField.empty() && specializationField.front() == '"') {
                if (specializationField.back() != '"') {
                    string rest;
                    while (getline(ss, rest, ',')) {
                        specializationField += "," + rest;
                        if (!rest.empty() && rest.back() == '"') break;
                    }
                }
                // Remove surrounding quotes
                if (specializationField.front() == '"' && specializationField.back() == '"') {
                    specializationField = specializationField.substr(1, specializationField.length() - 2);
                }
            }
            // Parse individual specializations
            stringstream specStream(specializationField);
            string spec;
            while (getline(specStream, spec, ',')) {
                size_t start = spec.find_first_not_of(" \t\r\n");
                size_t end = spec.find_last_not_of(" \t\r\n");
                if (start != string::npos && end != string::npos) {
                    h.addSpecialization(spec.substr(start, end - start + 1));
                }
            }
        }
        // Parse coordinates (quoted, "lat, lon")
        if (getline(ss, token)) {
            if (!token.empty() && token.front() == '"' && token.back() == '"') {
                token = token.substr(1, token.length() - 2);
            }
            stringstream coordStream(token);
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
                try { h.latitude = stod(latStr); } catch (...) { h.latitude = 0.0; }
                try { h.longitude = stod(lonStr); } catch (...) { h.longitude = 0.0; }
            }
        }
        addHospital(h);
    }

    // Process remaining lines
    while (getline(fin, line)) {
        if (line.length() == 0) continue;

        stringstream ss(line);
        string token;
        Hospital h;

        if (getline(ss, token, ',')) h.id = token;
        if (getline(ss, token, ',')) h.name = token;
        if (getline(ss, token, ',')) h.sector = token;
        if (getline(ss, token, ',')) {
            try {
                h.emergencyBeds = stoi(token);
            } catch (...) { h.emergencyBeds = 0; }
        }
        // Parse specializations (quoted, comma-separated)
        if (getline(ss, token, ',')) {
            string specializationField = token;
            // If starts with quote, read until closing quote
            if (!specializationField.empty() && specializationField.front() == '"') {
                if (specializationField.back() != '"') {
                    string rest;
                    while (getline(ss, rest, ',')) {
                        specializationField += "," + rest;
                        if (!rest.empty() && rest.back() == '"') break;
                    }
                }
                // Remove surrounding quotes
                if (specializationField.front() == '"' && specializationField.back() == '"') {
                    specializationField = specializationField.substr(1, specializationField.length() - 2);
                }
            }
            // Parse individual specializations
            stringstream specStream(specializationField);
            string spec;
            while (getline(specStream, spec, ',')) {
                size_t start = spec.find_first_not_of(" \t\r\n");
                size_t end = spec.find_last_not_of(" \t\r\n");
                if (start != string::npos && end != string::npos) {
                    h.addSpecialization(spec.substr(start, end - start + 1));
                }
            }
        }
        // Parse coordinates (quoted, "lat, lon")
        if (getline(ss, token)) {
            if (!token.empty() && token.front() == '"' && token.back() == '"') {
                token = token.substr(1, token.length() - 2);
            }
            stringstream coordStream(token);
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
                try { h.latitude = stod(latStr); } catch (...) { h.latitude = 0.0; }
                try { h.longitude = stod(lonStr); } catch (...) { h.longitude = 0.0; }
            }
        }
        addHospital(h);
    }

    fin.close();
    rebuildHeap();
    return true;
}

bool HospitalManager::addHospital(const Hospital& h) {
    if (hospitalCount >= MAX_HOSPITALS) {
        return false;
    }
    
    hospitals[hospitalCount] = h;
    emergencyHeap.insert(&hospitals[hospitalCount]);  // FIXED: Pass pointer
    
    // Add to graph for Dijkstra
    hospitalGraph->addNode(h.id, (float)h.latitude, (float)h.longitude);
    
    hospitalCount++;
    return true;
}

void HospitalManager::listHospitals() {
    cout << "\n===== Hospital List =====\n";
    for (int i = 0; i < hospitalCount; i++) {
        cout << i + 1 << ") ID: " << hospitals[i].id 
             << " | Name: " << hospitals[i].name 
             << " | Sector: " << hospitals[i].sector
             << " | Emergency Beds: " << hospitals[i].emergencyBeds 
             << " | Specializations: ";
        hospitals[i].displaySpecializations();
        cout << " | Coordinates: (" << hospitals[i].latitude << ", " << hospitals[i].longitude << ")\n";
    }
    cout << "=========================\n";
}

Hospital* HospitalManager::getHospitalWithMostBeds() {
    return emergencyHeap.getMax();
}

// Get ALL hospitals with maximum emergency beds
void HospitalManager::getHospitalsWithMostBeds(Hospital** results, int& count) {
    count = 0;
    if (hospitalCount == 0) return;
    
    // Find maximum bed count
    int maxBeds = -1;
    for (int i = 0; i < hospitalCount; i++) {
        if (hospitals[i].emergencyBeds > maxBeds) {
            maxBeds = hospitals[i].emergencyBeds;
        }
    }
    
    // Collect all hospitals with max beds
    for (int i = 0; i < hospitalCount; i++) {
        if (hospitals[i].emergencyBeds == maxBeds) {
            results[count++] = &hospitals[i];
        }
    }
}

bool HospitalManager::updateEmergencyBeds(const string& hospitalId, int newBedCount) {
    // Validate: Don't allow negative beds
    if (newBedCount < 0) {
        cout << "Error: Emergency beds cannot be negative!\n";
        return false;
    }
    
    // Convert search ID to lowercase for comparison
    string lowerSearchId = toLowercase(hospitalId);
    
    for (int i = 0; i < hospitalCount; i++) {
        if (toLowercase(hospitals[i].id) == lowerSearchId) {
            hospitals[i].emergencyBeds = newBedCount;
            rebuildHeap(); // Rebuild heap after update
            return true;
        }
    }
    return false;
}

Hospital* HospitalManager::searchById(const string& id) {
    string lowerSearchId = toLowercase(id);
    
    for (int i = 0; i < hospitalCount; i++) {
        if (toLowercase(hospitals[i].id) == lowerSearchId) {
            return &hospitals[i];
        }
    }
    return nullptr;
}

bool HospitalManager::hospitalIdExists(const string& id) {
    string lowerSearchId = toLowercase(id);
    
    for (int i = 0; i < hospitalCount; i++) {
        if (toLowercase(hospitals[i].id) == lowerSearchId) {
            return true;
        }
    }
    return false;
}

Hospital* HospitalManager::getHospitalAt(int index) {
    if (index >= 0 && index < hospitalCount) {
        return &hospitals[index];
    }
    return nullptr;
}

void HospitalManager::rebuildHeap() {
    EmergencyHeap newHeap;
    for (int i = 0; i < hospitalCount; i++) {
        newHeap.insert(&hospitals[i]);
    }
    emergencyHeap = newHeap;
}

void HospitalManager::addHospitalInteractive() {
    if (hospitalCount >= MAX_HOSPITALS) {
        cout << "Cannot add more hospitals. Storage full.\n";
        return;
    }
    Hospital h;
    cout << "Enter Hospital ID: ";
    getline(cin, h.id);
    
    // Check if hospital ID already exists (case-insensitive)
    if (hospitalIdExists(h.id)) {
        cout << "Error: A hospital with this ID already exists!\n";
        return;
    }
    
    cout << "Enter Hospital Name: ";
    getline(cin, h.name);
    
    cout << "Enter Sector: ";
    getline(cin, h.sector);
    
    int beds;
    while (true) {
        cout << "Enter number of Emergency Beds (>= 0): ";
        cin >> beds;
        cin.ignore(1000, '\n'); // Clear input buffer
        if (beds >= 0) {
            h.emergencyBeds = beds;
            break;
        } else {
            cout << "Error: Emergency beds cannot be negative!\n";
        }
    }
    cout << "Enter Specializations (comma separated): ";
    string specsLine;
    getline(cin, specsLine);
    stringstream specStream(specsLine);
    string spec;
    while (getline(specStream, spec, ',')) {
        size_t start = spec.find_first_not_of(" \t\r\n");
        size_t end = spec.find_last_not_of(" \t\r\n");
        if (start != string::npos && end != string::npos) {
            h.addSpecialization(spec.substr(start, end - start + 1));
        }
    }

    cout << "Enter Latitude: ";
    cin >> h.latitude;
    cout << "Enter Longitude: ";
    cin >> h.longitude;
    cin.ignore(1000, '\n');

    addHospital(h);
    rebuildHeap();
    cout << "Hospital added successfully!\n";
}

Hospital* HospitalManager::findNearestByCoord(double lat, double lon, double* outDistance) {
    if (hospitalCount == 0) return nullptr;

    Hospital* nearest = &hospitals[0];
    double minDistance = sqrt((lat - hospitals[0].latitude) * (lat - hospitals[0].latitude) +
                              (lon - hospitals[0].longitude) * (lon - hospitals[0].longitude));

    for (int i = 1; i < hospitalCount; i++) {
        double distance = sqrt((lat - hospitals[i].latitude) * (lat - hospitals[i].latitude) +
                               (lon - hospitals[i].longitude) * (lon - hospitals[i].longitude));
        if (distance < minDistance) {
            minDistance = distance;
            nearest = &hospitals[i];
        }
    }

    if (outDistance != nullptr) {
        *outDistance = minDistance;
    }

    return nearest;
}

bool HospitalManager::loadHospitalEdgesFromCSV(const string& filename) {
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
        string fromHospitalID, toHospitalID, distanceStr;

        getline(ss, fromHospitalID, ',');
        getline(ss, toHospitalID, ',');
        getline(ss, distanceStr);

        int distance = 0;
        try { distance = stoi(distanceStr); } catch (...) { distance = 0; }

        // Use existing search method to find indices
        int fromIndex = -1, toIndex = -1;
        for (int i = 0; i < hospitalCount; i++) {
            if (toLowercase(hospitals[i].id) == toLowercase(fromHospitalID)) {
                fromIndex = i;
            }
            if (toLowercase(hospitals[i].id) == toLowercase(toHospitalID)) {
                toIndex = i;
            }
        }

        if (fromIndex != -1 && toIndex != -1) {
            hospitalGraph->addEdge(fromIndex, toIndex, distance);
        } else {
            cout << "Warning: Edge between " << fromHospitalID << " and " << toHospitalID << " skipped (hospital not found)\n";
        }
    }
    file.close();
    return true;
}

bool HospitalManager::findShortestPath(const string& startHospitalID, const string& endHospitalID, 
                                       string* path, int& pathLength, int& totalDistance) {
    // Find indices using existing methods
    int startIndex = -1, endIndex = -1;
    for (int i = 0; i < hospitalCount; i++) {
        if (toLowercase(hospitals[i].id) == toLowercase(startHospitalID)) {
            startIndex = i;
        }
        if (toLowercase(hospitals[i].id) == toLowercase(endHospitalID)) {
            endIndex = i;
        }
    }

    if (startIndex == -1 || endIndex == -1) {
        cout << "One or both hospitals not found!\n";
        return false;
    }

    hospitalGraph->dijkstra(startIndex, endIndex, path, pathLength, totalDistance);
    
    if (pathLength == 0 || totalDistance == INT_MAX) {
        cout << "No path found between hospitals.\n";
        return false;
    }
    
    return true;
}