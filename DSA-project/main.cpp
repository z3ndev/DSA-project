#include <iostream>
#include <iomanip>
#include "HospitalManager.h"
#include "PharmacyManager.h"
#include "PopulationManager.h"

using namespace std;

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pause() {
    cout << "\nPress Enter to continue...";
    cin.get();
}

void printHeader(const string& title) {
    cout << "\n=== " << title << " ===\n";
}

void displayMenu() {
    cout << "\n==================== MAIN MENU ====================\n";
    cout << "\nHOSPITALS:\n";
    cout << "  1. List all hospitals\n";
    cout << "  2. Get hospital(s) with most emergency beds\n";
    cout << "  3. Search hospital by ID\n";
    cout << "  4. Update emergency beds\n";
    cout << "  5. Add new hospital\n";
    cout << "\nPHARMACIES & MEDICINES:\n";
    cout << "  6. List all pharmacies\n";
    cout << "  7. Display all medicines\n";
    cout << "  8. Search medicine by name\n";
    cout << "  9. Search medicine by formula\n";
    cout << "\nPOPULATION & HOUSING:\n";
    cout << "  10. Display all citizens\n";
    cout << "  11. Search citizen by CNIC\n";
    cout << "  12. Display household details\n";
    cout << "  13. Age distribution report\n";
    cout << "  14. Occupation summary report\n";
    cout << "  15. Population density report\n";
    cout << "  16. Gender ratio report\n";
    cout << "\n  0. Exit\n";
    cout << "\n===================================================\n";
    cout << "Enter your choice: ";
}

void displayHospitalDetails(Hospital* h) {
    cout << "\n--- HOSPITAL DETAILS ---\n";
    cout << "Hospital ID: " << h->id << "\n";
    cout << "Name: " << h->name << "\n";
    cout << "Sector: " << h->sector << "\n";
    cout << "Emergency Beds: " << h->emergencyBeds << "\n";
    cout << "Specializations: ";
    h->displaySpecializations();
    cout << "\n";
}

void displayMedicineDetails(Medicine* med) {
    cout << "\n--- MEDICINE DETAILS ---\n";
    cout << "Name: " << med->name << "\n";
    cout << "Formula: " << med->formula << "\n";
    cout << "Price: Rs. " << med->price << "\n";
}

void displayCitizenDetails(Citizen* c) {
    cout << "\n--- CITIZEN DETAILS ---\n";
    cout << "CNIC: " << c->CNIC << "\n";
    cout << "Name: " << c->name << "\n";
    cout << "Age: " << c->age << "\n";
    cout << "Occupation: " << c->occupation << "\n";
    cout << "Gender: " << c->gender << "\n";
}

int getIntInput(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(1000, '\n');  // Clear input buffer
            return value;
        } else {
            cin.clear();
            cin.ignore(1000, '\n');  // Clear input buffer
            cout << "Invalid input! Please enter a number.\n";
        }
    }
}

int getPositiveIntInput(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(1000, '\n');  // Clear input buffer
            if (value >= 0) {
                return value;
            } else {
                cout << "Error: Value cannot be negative! Please enter a non-negative number.\n";
            }
        } else {
            cin.clear();
            cin.ignore(1000, '\n');  // Clear input buffer
            cout << "Invalid input! Please enter a number.\n";
        }
    }
}

string getStringInput(const string& prompt) {
    string value;
    cout << prompt;
    getline(cin, value);
    return value;
}

int main() {
    HospitalManager hospitalMgr;
    PharmacyManager pharmacyMgr;
    PopulationManager populationMgr;

    cout << "\n===================================================\n";
    cout << "        SMART CITY MANAGEMENT SYSTEM\n";
    cout << "   Healthcare, Pharmacy & Population Management\n";
    cout << "===================================================\n";
    
    // Load data from CSV files
    cout << "\n--- LOADING DATA ---\n";
    
    cout << "Loading hospitals from CSV...\n";
    if (hospitalMgr.loadFromCSV("SmartCity_dataset/hospitals.csv")) {
        cout << " Hospitals loaded successfully!\n";
    } else {
        cout << " Failed to load hospitals.\n";
    }

    cout << "Loading pharmacies from CSV...\n";
    if (pharmacyMgr.loadFromCSV("SmartCity_dataset/pharmacies.csv")) {
        cout << " Pharmacies loaded successfully!\n";
    } else {
        cout << " Failed to load pharmacies.\n";
    }

    cout << "Loading population data from CSV...\n";
    if (populationMgr.loadFromCSV("SmartCity_dataset/population.csv")) {
        cout << " Population data loaded successfully!\n";
    } else {
        cout << " Failed to load population data.\n";
    }

    cout << "\nPress Enter to continue to main menu...";
    cin.get();

    int choice;
    do {
        displayMenu();
        
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');  // Clear input buffer
            cout << "Invalid input! Please enter a number.\n";
            continue;
        }
        cin.ignore(1000, '\n');  // Clear input buffer after reading choice

        switch (choice) {
            // ========== HOSPITAL OPERATIONS ==========
            case 1: {
                printHeader("ALL HOSPITALS");
                hospitalMgr.listHospitals();
                break;
            }
            
            case 2: {
                printHeader("HOSPITAL(S) WITH MOST EMERGENCY BEDS");
                
                const int MAX_RESULTS = 50;
                Hospital* results[MAX_RESULTS];
                int count = 0;
                
                hospitalMgr.getHospitalsWithMostBeds(results, count);
                
                if (count > 0) {
                    if (count == 1) {
                        cout << "\nFound 1 hospital with maximum emergency beds:\n";
                    } else {
                        cout << "\nFound " << count << " hospitals with maximum emergency beds:\n";
                    }
                    
                    for (int i = 0; i < count; i++) {
                        cout << "\n" << (i+1) << ".";
                        displayHospitalDetails(results[i]);
                    }
                } else {
                    cout << "No hospitals available.\n";
                }
                break;
            }
            
            case 3: {
                printHeader("SEARCH HOSPITAL BY ID");
                string searchId = getStringInput("Enter Hospital ID: ");
                
                Hospital* h = hospitalMgr.searchById(searchId);
                if (h) {
                    displayHospitalDetails(h);
                } else {
                    cout << "Hospital not found!\n";
                }
                break;
            }
            
            case 4: {
                printHeader("UPDATE EMERGENCY BEDS");
                string hospitalId = getStringInput("Enter Hospital ID: ");
                int newBeds = getPositiveIntInput("Enter new emergency bed count (must be >= 0): ");
                
                if (hospitalMgr.updateEmergencyBeds(hospitalId, newBeds)) {
                    cout << " Emergency beds updated successfully!\n";
                } else {
                    cout << " Hospital not found or update failed.\n";
                }
                break;
            }
            
            case 5: {
                printHeader("ADD NEW HOSPITAL");
                hospitalMgr.addHospitalInteractive();
                break;
            }
            
            // ========== PHARMACY OPERATIONS ==========
            case 6: {
                printHeader("ALL PHARMACIES");
                pharmacyMgr.listPharmacies();
                break;
            }
            
            case 7: {
                printHeader("ALL MEDICINES");
                pharmacyMgr.displayAllMedicines();
                break;
            }
            
            case 8: {
                printHeader("SEARCH MEDICINE BY NAME");
                string searchName = getStringInput("Enter medicine name: ");
                
                Medicine* med = pharmacyMgr.searchMedicineByName(searchName);
                if (med) {
                    displayMedicineDetails(med);
                } else {
                    cout << "Medicine not found!\n";
                }
                break;
            }
            
            case 9: {
                printHeader("SEARCH MEDICINE BY FORMULA");
                string searchFormula = getStringInput("Enter medicine formula: ");
                
                Medicine* med = pharmacyMgr.searchMedicineByFormula(searchFormula);
                if (med) {
                    displayMedicineDetails(med);
                } else {
                    cout << "Medicine with formula '" + searchFormula + "' not found!\n";
                }
                break;
            }
            
            // ========== POPULATION OPERATIONS ==========
            case 10: {
                printHeader("ALL CITIZENS");
                populationMgr.displayAllCitizens();
                break;
            }
            
            case 11: {
                printHeader("SEARCH CITIZEN BY CNIC");
                string searchCNIC = getStringInput("Enter CNIC (e.g., 61101-1111111-1): ");
                
                Citizen* c = populationMgr.searchByCNIC(searchCNIC);
                if (c) {
                    displayCitizenDetails(c);
                } else {
                    cout << "Citizen not found!\n";
                }
                break;
            }
            
            case 12: {
                printHeader("HOUSEHOLD DETAILS");
                string sector = getStringInput("Enter Sector (e.g., G-10): ");
                string street = getStringInput("Enter Street No (e.g., 22): ");
                string house = getStringInput("Enter House No (e.g., 180): ");
                
                populationMgr.displayHousehold(sector, street, house);
                break;
            }
            
            case 13: {
                printHeader("AGE DISTRIBUTION REPORT");
                populationMgr.generateAgeDistribution();
                break;
            }
            
            case 14: {
                printHeader("OCCUPATION SUMMARY REPORT");
                populationMgr.generateOccupationSummary();
                break;
            }
            
            case 15: {
                printHeader("POPULATION DENSITY REPORT");
                populationMgr.generatePopulationDensity();
                break;
            }
            
            case 16: {
                printHeader("GENDER RATIO REPORT");
                populationMgr.generateGenderRatio();
                break;
            }
            
            // ========== EXIT ==========
            case 0: {
                cout << "\n===================================================\n";
                cout << "        Thank you for using\n";
                cout << "        Smart City Management System!\n";
                cout << "        Goodbye!\n";
                cout << "===================================================\n\n";
                break;
            }
            
            default: {
                cout << "Invalid choice! Please select a valid option (0-16).\n";
                break;
            }
        }

    } while (choice != 0);

    return 0;
}