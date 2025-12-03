#include "PharmacyManager.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

PharmacyManager::PharmacyManager() : pharmacyCount(0) {
}

bool PharmacyManager::loadFromCSV(const char* filename) {
    ifstream fin(filename);
    if (!fin.is_open()) {
        cerr << "Failed to open " << filename << endl;
        return false;
    }

    string line;
    // Read header line
    if (!getline(fin, line)) {
        fin.close();
        return false;
    }

    bool headerConsumed = (line.find("PharmacyID") != string::npos);

    if (!headerConsumed) {
        // Process first line as data
        stringstream ss(line);
        string token;

        Pharmacy p;
        Medicine m;

        if (getline(ss, token, ',')) p.id = token;
        if (getline(ss, token, ',')) p.name = token;
        if (getline(ss, token, ',')) p.sector = token;
        if (getline(ss, token, ',')) m.name = token;
        if (getline(ss, token, ',')) m.formula = token;
        if (getline(ss, token, ',')) {
            try {
                m.price = stoi(token);
            } catch (...) { m.price = 0; }
        }

        p.med = m;
        addPharmacy(p);
    }

    // Process remaining lines
    while (getline(fin, line)) {
        if (line.length() == 0) continue;
        stringstream ss(line);
        string token;

        Pharmacy p;
        Medicine m;

        if (getline(ss, token, ',')) p.id = token;
        if (getline(ss, token, ',')) p.name = token;
        if (getline(ss, token, ',')) p.sector = token;
        if (getline(ss, token, ',')) m.name = token;
        if (getline(ss, token, ',')) m.formula = token;
        if (getline(ss, token, ',')) {
            try {
                m.price = stoi(token);
            } catch (...) { m.price = 0; }
        }

        p.med = m;
        addPharmacy(p);
    }

    fin.close();
    return true;
}

bool PharmacyManager::addPharmacy(const Pharmacy& p) {
    if (pharmacyCount >= MAX_PHARMACIES) {
        cerr << "Pharmacy storage full, cannot add more." << endl;
        return false;
    }

    pharmacies[pharmacyCount] = p;
    pharmacyCount++;

    // Index medicine in both hash tables
    medicineTable.insert(p.med);
    formulaTable.insert(p.med);

    return true;
}

Medicine* PharmacyManager::searchMedicineByName(const string& name) {
    return medicineTable.searchByName(name);
}

Medicine* PharmacyManager::searchMedicineByFormula(const string& formula) {
    return formulaTable.searchByFormula(formula);
}

void PharmacyManager::listPharmacies() {
    cout << "\n===== Pharmacy List =====\n";
    for (int i = 0; i < pharmacyCount; i++) {
        cout << i + 1 << ") " << pharmacies[i].id << " | " << pharmacies[i].name 
             << " | Sector: " << pharmacies[i].sector
             << " | Medicine: " << pharmacies[i].med.name 
             << " (" << pharmacies[i].med.formula << ") - Price: " 
             << pharmacies[i].med.price << "\n";
    }
    cout << "=========================\n";
}

void PharmacyManager::displayAllMedicines() {
    cout << "\n===== Medicines List =====\n";
    for (int i = 0; i < pharmacyCount; i++) {
        cout << i + 1 << ") " << pharmacies[i].med.name 
             << " | Formula: " << pharmacies[i].med.formula
             << " | Price: " << pharmacies[i].med.price << "\n";
    }
    cout << "==========================\n";
}

