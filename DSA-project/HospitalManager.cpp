#include "HospitalManager.h"
#include <fstream>
#include <sstream>
#include <iostream>

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
        // Parse specializations
        if (getline(ss, token)) {
            if (!token.empty() && token.front() == '"' && token.back() == '"') {
                token = token.substr(1, token.length() - 2);
            }
            stringstream specStream(token);
            string spec;
            while (getline(specStream, spec, ',')) {
                size_t start = spec.find_first_not_of(" \t\r\n");
                size_t end = spec.find_last_not_of(" \t\r\n");
                if (start != string::npos && end != string::npos) {
                    h.addSpecialization(spec.substr(start, end - start + 1));
                }
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
        // Parse specializations
        if (getline(ss, token)) {
            if (!token.empty() && token.front() == '"' && token.back() == '"') {
                token = token.substr(1, token.length() - 2);
            }
            stringstream specStream(token);
            string spec;
            while (getline(specStream, spec, ',')) {
                size_t start = spec.find_first_not_of(" \t\r\n");
                size_t end = spec.find_last_not_of(" \t\r\n");
                if (start != string::npos && end != string::npos) {
                    h.addSpecialization(spec.substr(start, end - start + 1));
                }
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
        cerr << "Hospital storage full." << endl;
        return false;
    }

    hospitals[hospitalCount] = h;
    hospitals[hospitalCount].graphNodeIndex = hospitalCount;
    emergencyHeap.insert(&hospitals[hospitalCount]);
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
        cout << "\n";
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
    addHospital(h);
    rebuildHeap();
    cout << "Hospital added successfully!\n";
}