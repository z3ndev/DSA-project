#ifndef PHARMACYMANAGER_H
#define PHARMACYMANAGER_H

#include <string>
#include "Medicine.h"
#include "Pharmacy.h"
#include "MedicineHashTable.h"
#include "MedicineFormulaHashTable.h"

using namespace std;

class PharmacyManager {
private:
    static const int MAX_PHARMACIES = 200;

    Pharmacy pharmacies[MAX_PHARMACIES];
    int pharmacyCount;

    MedicineHashTable medicineTable;           // hash by medicine.name
    MedicineFormulaHashTable formulaTable;     // hash by medicine.formula

public:
    PharmacyManager();

    // Load pharmacies from CSV file
    bool loadFromCSV(const char* filename);

    // Add a pharmacy entry (and index its medicine)
    bool addPharmacy(const Pharmacy& p);

    // Search medicine by name (fast hash lookup)
    Medicine* searchMedicineByName(const string& name);

    // Search medicine by formula (fast hash lookup)
    Medicine* searchMedicineByFormula(const string& formula);

    // Display all pharmacies (basic)
    void listPharmacies();

    // Display all medicines (built from pharmacy entries)
    void displayAllMedicines();
};

#endif

