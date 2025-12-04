#ifndef HOSPITALMANAGER_H
#define HOSPITALMANAGER_H

#include "Hospital.h"
#include "EmergencyHeap.h"
#include <string>

using namespace std;

class HospitalManager {
private:
    static const int MAX_HOSPITALS = 50;
    Hospital hospitals[MAX_HOSPITALS];
    int hospitalCount;

    EmergencyHeap emergencyHeap;

public:
    HospitalManager();

    // Load hospitals from CSV file
    bool loadFromCSV(const char* filename);

    // Add a hospital
    bool addHospital(const Hospital& h);
    
    // Add hospital interactively (runtime input)
    void addHospitalInteractive();

    // List all hospitals
    void listHospitals();

    // Get hospital with most emergency beds (using heap)
    Hospital* getHospitalWithMostBeds();
    
    // Get ALL hospitals with maximum emergency beds
    void getHospitalsWithMostBeds(Hospital** results, int& count);

    // Update emergency beds for a hospital (with validation)
    bool updateEmergencyBeds(const string& hospitalId, int newBedCount);

    // Search hospital by ID
    Hospital* searchById(const string& id);
    
    // Check if hospital ID already exists (case-insensitive)
    bool hospitalIdExists(const string& id);

    // Get total hospital count
    int getCount() const { return hospitalCount; }

    // Get hospital by index
    Hospital* getHospitalAt(int index);

    // Rebuild the emergency heap (call after updates)
    void rebuildHeap();
};

#endif
