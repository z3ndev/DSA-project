#ifndef HOSPITAL_H
#define HOSPITAL_H
#include <iostream>
#include <string>
using namespace std;

class Hospital {
private:
    static const int MAX_SPEC = 10;     // Max 10 specializations
    string specializations[MAX_SPEC];
    int specCount;

public:
    string id;
    string name;
    string sector;
    int emergencyBeds;
    int graphNodeIndex;  // Index in graph for Dijkstra algorithm
    double latitude;
    double longitude;

    Hospital() {
        id = "";
        name = "";
        sector = "";
        emergencyBeds = 0;
        specCount = 0;
        graphNodeIndex = -1;  // -1 indicates not assigned to graph
        latitude = 0.0;
        longitude = 0.0;
    }

    void addSpecialization(const string& s) {
        if (specCount < MAX_SPEC) {
            specializations[specCount++] = s;
        }
    }

    int getSpecializationCount() const {
        return specCount;
    }

    string getSpecialization(int index) const {
        if (index >= 0 && index < specCount)
            return specializations[index];
        return "";
    }

    // Display all specializations
    void displaySpecializations() const {
        for (int i = 0; i < specCount; i++) {
            cout << specializations[i];
            if (i < specCount - 1) cout << ", ";
        }
    }
};

#endif

