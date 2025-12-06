#include "PopulationManager.h"
#include <fstream>
#include <sstream>
#include <iostream>

PopulationManager::PopulationManager() {
    city = nullptr;
}

// Load citizens from CSV file
bool PopulationManager::loadFromCSV(const char* filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    string line;
    // Skip header line
    getline(file, line);

    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string cnic, name, ageStr, sector, street, house, occupation, gender, relation, parentCNIC, latStr, lonStr;

        // Parse CSV: CNIC, Name, Age, Sector, Street, HouseNo, Occupation, Gender, Relation, ParentCNIC, Latitude, Longitude
        getline(ss, cnic, ',');
        getline(ss, name, ',');
        getline(ss, ageStr, ',');
        getline(ss, sector, ',');
        getline(ss, street, ',');
        getline(ss, house, ',');
        getline(ss, occupation, ',');
        getline(ss, gender, ',');
        getline(ss, relation, ',');
        getline(ss, parentCNIC, ',');
        getline(ss, latStr, ',');
        getline(ss, lonStr);

        // Convert age to int
        int age = 0;
        try { age = stoi(ageStr); } catch (...) { age = 0; }

        // Convert coordinates to double
        double latitude = 0.0, longitude = 0.0;
        try { latitude = stod(latStr); } catch (...) { latitude = 0.0; }
        try { longitude = stod(lonStr); } catch (...) { longitude = 0.0; }

        // Add citizen with all fields
        addCitizen(cnic, name, age, sector, street, house, occupation, gender, relation, parentCNIC, latitude, longitude);
    }

    file.close();
    return true;
}

void PopulationManager::addCitizen(const string& CNIC, const string& name, int age,
    const string& sectorName, const string& streetNo,
    const string& houseNo, const string& occupation, const string& gender,
    const string& relation, const string& parentCNIC, double latitude, double longitude) {
    // 1. Create Citizen with all fields including coordinates
    Citizen* c = new Citizen(CNIC, name, age, occupation, gender, relation, parentCNIC, latitude, longitude);

    // 2. Insert into CNIC hash
    cnicHash.insert(c);

    // 3. Insert into N-ary tree: Sector → Street → House
    Sector* s = findOrCreateSector(sectorName);
    Street* st = findOrCreateStreet(s, streetNo);
    Household* h = findOrCreateHouse(st, houseNo);
    h->addMember(c);
}

Sector* PopulationManager::findOrCreateSector(const string& name) {
    Sector* cur = city;
    Sector* prev = nullptr;
    while (cur != nullptr) {
        if (cur->sectorName == name) return cur;
        prev = cur;
        cur = cur->next;
    }
    Sector* newSector = new Sector(name);
    if (prev == nullptr) city = newSector;
    else prev->next = newSector;
    return newSector;
}

Street* PopulationManager::findOrCreateStreet(Sector* s, const string& streetNo) {
    Street* cur = s->streets;
    Street* prev = nullptr;
    while (cur != nullptr) {
        if (cur->streetNo == streetNo) return cur;
        prev = cur;
        cur = cur->next;
    }
    Street* newStreet = new Street(streetNo);
    if (prev == nullptr) s->streets = newStreet;
    else prev->next = newStreet;
    return newStreet;
}

Household* PopulationManager::findOrCreateHouse(Street* st, const string& houseNo) {
    Household* cur = st->houses;
    Household* prev = nullptr;
    while (cur != nullptr) {
        if (cur->houseNo == houseNo) return cur;
        prev = cur;
        cur = cur->nextSibling;
    }
    Household* newHouse = new Household(houseNo);
    if (prev == nullptr) st->houses = newHouse;
    else prev->nextSibling = newHouse;
    return newHouse;
}

// Search citizen by CNIC
Citizen* PopulationManager::searchByCNIC(const string& cnic) {
    return cnicHash.search(cnic);
}

// Display all citizens
void PopulationManager::displayAllCitizens() {
    cout << "\n=== ALL CITIZENS ===\n";
    Sector* s = city;
    int totalCount = 0;

    while (s != nullptr) {
        cout << "\nSector: " << s->sectorName << "\n";
        Street* st = s->streets;

        while (st != nullptr) {
            cout << "  Street: " << st->streetNo << "\n";
            Household* h = st->houses;

            while (h != nullptr) {
                cout << "    House: " << h->houseNo << " (" << h->memberCount << " members)\n";
                for (int i = 0; i < h->memberCount; i++) {
                    Citizen* c = h->members[i];
                    cout << "      - " << c->name << " (Age: " << c->age 
                         << ", Gender: " << c->gender
                         << ", CNIC: " << c->CNIC 
                         << ", Occupation: " << c->occupation
                         << ", Relation: " << c->relation;
                    if (!c->parentCNIC.empty()) {
                        cout << ", Parent: " << c->parentCNIC;
                    }
                    cout << ", Coords: (" << c->latitude << ", " << c->longitude << ")";
                    cout << ")\n";
                    totalCount++;
                }
                h = h->nextSibling;
            }
            st = st->next;
        }
        s = s->next;
    }
    cout << "\nTotal Citizens: " << totalCount << "\n";
}

// Display family tree starting from a head
void PopulationManager::displayFamilyTree(const string& headCNIC) {
    Citizen* head = searchByCNIC(headCNIC);
    if (!head) {
        cout << "Citizen with CNIC " << headCNIC << " not found.\n";
        return;
    }
    
    cout << "\n=== FAMILY TREE ===\n";
    cout << head->name << " (" << head->CNIC << ") - " << head->relation << "\n";
    displayFamilyTreeRecursive(headCNIC, 1);
}

void PopulationManager::displayFamilyTreeRecursive(const string& parentCNIC, int level) {
    // Find all citizens with this parent
    Sector* s = city;
    while (s != nullptr) {
        Street* st = s->streets;
        while (st != nullptr) {
            Household* h = st->houses;
            while (h != nullptr) {
                for (int i = 0; i < h->memberCount; i++) {
                    Citizen* c = h->members[i];
                    if (c->parentCNIC == parentCNIC) {
                        // Print with indentation
                        for (int j = 0; j < level; j++) cout << "  ";
                        cout << "└─ " << c->name << " (" << c->CNIC << ") - " << c->relation << "\n";
                        // Recursively print their children
                        displayFamilyTreeRecursive(c->CNIC, level + 1);
                    }
                }
                h = h->nextSibling;
            }
            st = st->next;
        }
        s = s->next;
    }
}

// Age distribution report
void PopulationManager::generateAgeDistribution() {
    cout << "\n=== AGE DISTRIBUTION REPORT ===\n";
    
    // Age groups: 0-18, 19-35, 36-50, 51-65, 66+
    int ageGroups[5] = {0};
    
    Sector* s = city;
    while (s != nullptr) {
        Street* st = s->streets;
        while (st != nullptr) {
            Household* h = st->houses;
            while (h != nullptr) {
                for (int i = 0; i < h->memberCount; i++) {
                    int age = h->members[i]->age;
                    if (age <= 18) ageGroups[0]++;
                    else if (age <= 35) ageGroups[1]++;
                    else if (age <= 50) ageGroups[2]++;
                    else if (age <= 65) ageGroups[3]++;
                    else ageGroups[4]++;
                }
                h = h->nextSibling;
            }
            st = st->next;
        }
        s = s->next;
    }
    
    cout << "0-18 years (Children):  " << ageGroups[0] << "\n";
    cout << "19-35 years (Youth):    " << ageGroups[1] << "\n";
    cout << "36-50 years (Adult):    " << ageGroups[2] << "\n";
    cout << "51-65 years (Middle):   " << ageGroups[3] << "\n";
    cout << "66+ years (Senior):     " << ageGroups[4] << "\n";
}

// Occupation summary report
void PopulationManager::generateOccupationSummary() {
    cout << "\n=== OCCUPATION SUMMARY ===\n";
    
    const int MAX_OCCUPATIONS = 20;
    string occupations[MAX_OCCUPATIONS];
    int counts[MAX_OCCUPATIONS];
    int occupationCount = 0;
    
    Sector* s = city;
    while (s != nullptr) {
        Street* st = s->streets;
        while (st != nullptr) {
            Household* h = st->houses;
            while (h != nullptr) {
                for (int i = 0; i < h->memberCount; i++) {
                    string occ = h->members[i]->occupation;
                    
                    // Find or add occupation
                    int index = -1;
                    for (int j = 0; j < occupationCount; j++) {
                        if (occupations[j] == occ) {
                            index = j;
                            break;
                        }
                    }
                    
                    if (index == -1 && occupationCount < MAX_OCCUPATIONS) {
                        occupations[occupationCount] = occ;
                        counts[occupationCount] = 1;
                        occupationCount++;
                    } else if (index != -1) {
                        counts[index]++;
                    }
                }
                h = h->nextSibling;
            }
            st = st->next;
        }
        s = s->next;
    }
    
    // Display results
    for (int i = 0; i < occupationCount; i++) {
        cout << occupations[i] << ": " << counts[i] << "\n";
    }
}

// Population density report
void PopulationManager::generatePopulationDensity() {
    cout << "\n=== POPULATION DENSITY BY SECTOR ===\n";
    
    Sector* s = city;
    while (s != nullptr) {
        int sectorPopulation = 0;
        int houseCount = 0;
        
        Street* st = s->streets;
        while (st != nullptr) {
            Household* h = st->houses;
            while (h != nullptr) {
                sectorPopulation += h->memberCount;
                houseCount++;
                h = h->nextSibling;
            }
            st = st->next;
        }
        
        double avgPerHouse = (houseCount > 0) ? (double)sectorPopulation / houseCount : 0;
        
        cout << "Sector " << s->sectorName << ":\n";
        cout << "  Total Population: " << sectorPopulation << "\n";
        cout << "  Total Houses: " << houseCount << "\n";
        cout << "  Average per House: " << avgPerHouse << "\n\n";
        
        s = s->next;
    }
}

// Gender ratio report
void PopulationManager::generateGenderRatio() {
    cout << "\n=== GENDER RATIO REPORT ===\n";
    
    int maleCount = 0;
    int femaleCount = 0;
    int otherCount = 0;
    
    Sector* s = city;
    while (s != nullptr) {
        Street* st = s->streets;
        while (st != nullptr) {
            Household* h = st->houses;
            while (h != nullptr) {
                for (int i = 0; i < h->memberCount; i++) {
                    string gender = h->members[i]->gender;
                    if (gender == "M" || gender == "m") {
                        maleCount++;
                    } else if (gender == "F" || gender == "f") {
                        femaleCount++;
                    } else {
                        otherCount++;
                    }
                }
                h = h->nextSibling;
            }
            st = st->next;
        }
        s = s->next;
    }
    
    int totalCount = maleCount + femaleCount + otherCount;
    
    cout << "Male:   " << maleCount;
    if (totalCount > 0) {
        cout << " (" << (maleCount * 100.0 / totalCount) << "%)";
    }
    cout << "\n";
    
    cout << "Female: " << femaleCount;
    if (totalCount > 0) {
        cout << " (" << (femaleCount * 100.0 / totalCount) << "%)";
    }
    cout << "\n";
    
    if (otherCount > 0) {
        cout << "Other:  " << otherCount;
        if (totalCount > 0) {
            cout << " (" << (otherCount * 100.0 / totalCount) << "%)";
        }
        cout << "\n";
    }
    
    cout << "\nTotal:  " << totalCount << "\n";
    
    if (maleCount > 0 && femaleCount > 0) {
        double ratio = (double)maleCount / femaleCount;
        cout << "Male to Female Ratio: " << ratio << ":1\n";
    }
}

// Display household information
void PopulationManager::displayHousehold(const string& sectorName, 
                                         const string& streetNo, 
                                         const string& houseNo) {
    Sector* s = city;
    while (s != nullptr) {
        if (s->sectorName == sectorName) {
            Street* st = s->streets;
            while (st != nullptr) {
                if (st->streetNo == streetNo) {
                    Household* h = st->houses;
                    while (h != nullptr) {
                        if (h->houseNo == houseNo) {
                            cout << "\n=== HOUSEHOLD DETAILS ===\n";
                            cout << "Address: House " << houseNo << ", Street " 
                                 << streetNo << ", Sector " << sectorName << "\n";
                            cout << "Members (" << h->memberCount << "):\n";
                            for (int i = 0; i < h->memberCount; i++) {
                                Citizen* c = h->members[i];
                                cout << "  " << (i+1) << ". " << c->name 
                                     << " (Age: " << c->age << ", Gender: " << c->gender
                                     << ", CNIC: " << c->CNIC 
                                     << ", Occupation: " << c->occupation
                                     << ", Relation: " << c->relation;
                                if (!c->parentCNIC.empty()) {
                                    cout << ", Parent: " << c->parentCNIC;
                                }
                                cout << ", Coords: (" << c->latitude << ", " << c->longitude << ")";
                                cout << ")\n";
                            }
                            return;
                        }
                        h = h->nextSibling;
                    }
                }
                st = st->next;
            }
        }
        s = s->next;
    }
    cout << "Household not found!\n";
}
