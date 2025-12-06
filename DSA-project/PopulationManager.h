#ifndef POPULATION_MANAGER_H
#define POPULATION_MANAGER_H

#include "Sector.h"
#include "CNICHashTable.h"
#include <string>
using namespace std;

class PopulationManager {
public:
    Sector* city; // linked list of sectors
    CNICHashTable cnicHash;

    PopulationManager();
    
    // Load data from CSV
    bool loadFromCSV(const char* filename);
    
    // Add citizen (now with gender, relation, parentCNIC, coordinates)
    void addCitizen(const string& CNIC, const string& name, int age,
        const string& sectorName, const string& streetNo,
        const string& houseNo, const string& occupation, const string& gender,
        const string& relation = "", const string& parentCNIC = "",
        double latitude = 0.0, double longitude = 0.0);
    
    // Search operations
    Citizen* searchByCNIC(const string& cnic);
    
    // Display operations
    void displayAllCitizens();
    void displayHousehold(const string& sectorName, const string& streetNo, 
                         const string& houseNo);
    void displayFamilyTree(const string& headCNIC);
    
    // Report generation
    void generateAgeDistribution();
    void generateOccupationSummary();
    void generatePopulationDensity();
    void generateGenderRatio();

private:
    Sector* findOrCreateSector(const string& name);
    Street* findOrCreateStreet(Sector* s, const string& streetNo);
    Household* findOrCreateHouse(Street* st, const string& houseNo);
    void displayFamilyTreeRecursive(const string& parentCNIC, int level);
};

#endif
