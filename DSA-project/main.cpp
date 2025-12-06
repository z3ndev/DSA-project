#include <iostream>
#include <iomanip>
#include "HospitalManager.h"
#include "PharmacyManager.h"
#include "PopulationManager.h"
#include "SchoolTree.h"

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
    cout << "\nSCHOOLS & EDUCATION:\n";
    cout << "  10. List all schools\n";
    cout << "  11. Display full school tree\n";
    cout << "  12. Search school by ID\n";
    cout << "\nPOPULATION & HOUSING:\n";
    cout << "  13. Display all citizens\n";
    cout << "  14. Search citizen by CNIC\n";
    cout << "  15. Display household details\n";
    cout << "  16. Display family tree\n";
    cout << "  17. Age distribution report\n";
    cout << "  18. Occupation summary report\n";
    cout << "  19. Population density report\n";
    cout << "  20. Gender ratio report\n";
    cout << "\nNEAREST LOCATION FINDER (Cross-Type):\n";
    cout << "  21. Find nearest hospital (from School/Citizen/Manual)\n";
    cout << "  22. Find nearest school (from Citizen/Hospital/Manual)\n";
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
    cout << "Coordinates: (" << h->latitude << ", " << h->longitude << ")\n";
    cout << "Specializations: ";
    h->displaySpecializations();
    cout << "\n";
}

void displaySchoolDetails(SchoolNode* s) {
    cout << "\n--- SCHOOL DETAILS ---\n";
    cout << "School ID: " << s->getSchoolID() << "\n";
    cout << "Name: " << s->getName() << "\n";
    cout << "Sector: " << s->getSector() << "\n";
    cout << "Rating: " << s->getRating() << "\n";
    cout << "Coordinates: (" << s->getLatitude() << ", " << s->getLongitude() << ")\n";
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
    cout << "Relation: " << c->relation << "\n";
    if (!c->parentCNIC.empty()) {
        cout << "Parent CNIC: " << c->parentCNIC << "\n";
    }
    cout << "Coordinates: (" << c->latitude << ", " << c->longitude << ")\n";
}

int getIntInput(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(1000, '\n');
            return value;
        } else {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input! Please enter a number.\n";
        }
    }
}

int getPositiveIntInput(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(1000, '\n');
            if (value >= 0) {
                return value;
            } else {
                cout << "Error: Value cannot be negative! Please enter a non-negative number.\n";
            }
        } else {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input! Please enter a number.\n";
        }
    }
}

double getDoubleInput(const string& prompt) {
    double value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(1000, '\n');
            return value;
        } else {
            cin.clear();
            cin.ignore(1000, '\n');
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

// Smart nearest hospital finder
void findNearestHospital(HospitalManager& hospitalMgr, PopulationManager& populationMgr, SchoolTree& schoolTree) {
    printHeader("FIND NEAREST HOSPITAL");
    
    cout << "\nFind nearest hospital from:\n";
    cout << "1. A School (list schools first)\n";
    cout << "2. A Citizen (search by CNIC)\n";
    cout << "3. Manual coordinates\n";
    cout << "Enter choice: ";
    
    int sourceChoice;
    cin >> sourceChoice;
    cin.ignore(1000, '\n');
    
    double lat = 0.0, lon = 0.0;
    bool coordsFound = false;
    
    switch (sourceChoice) {
        case 1: {
            // From School
            cout << "\n--- Available Schools ---\n";
            schoolTree.listSchools();
            
            string schoolID = getStringInput("\nEnter School ID: ");
            SchoolNode* school = schoolTree.searchSchoolByID(schoolID);
            
            if (school) {
                lat = school->getLatitude();
                lon = school->getLongitude();
                coordsFound = true;
                cout << "\nSchool found: " << school->getName() 
                     << " at (" << lat << ", " << lon << ")\n";
            } else {
                cout << "School not found!\n";
            }
            break;
        }
        case 2: {
            // From Citizen
            string cnic = getStringInput("Enter Citizen's CNIC: ");
            Citizen* c = populationMgr.searchByCNIC(cnic);
            
            if (c) {
                lat = c->latitude;
                lon = c->longitude;
                coordsFound = true;
                cout << "\nCitizen found: " << c->name 
                     << " at (" << lat << ", " << lon << ")\n";
            } else {
                cout << "Citizen not found!\n";
            }
            break;
        }
        case 3: {
            // Manual
            lat = getDoubleInput("Enter Latitude: ");
            lon = getDoubleInput("Enter Longitude: ");
            coordsFound = true;
            break;
        }
        default:
            cout << "Invalid choice!\n";
            return;
    }
    
    if (coordsFound) {
        double distance;
        Hospital* nearest = hospitalMgr.findNearestByCoord(lat, lon, &distance);
        
        if (nearest) {
            cout << "\n=== NEAREST HOSPITAL ===\n";
            displayHospitalDetails(nearest);
            cout << "Distance: " << distance << " units\n";
        } else {
            cout << "No hospitals available.\n";
        }
    }
}

// Smart nearest school finder
void findNearestSchool(SchoolTree& schoolTree, PopulationManager& populationMgr, HospitalManager& hospitalMgr) {
    printHeader("FIND NEAREST SCHOOL");
    
    cout << "\nFind nearest school from:\n";
    cout << "1. A Citizen (search by CNIC)\n";
    cout << "2. A Hospital (list hospitals first)\n";
    cout << "3. Manual coordinates\n";
    cout << "Enter choice: ";
    
    int sourceChoice;
    cin >> sourceChoice;
    cin.ignore(1000, '\n');
    
    double lat = 0.0, lon = 0.0;
    bool coordsFound = false;
    
    switch (sourceChoice) {
        case 1: {
            // From Citizen
            string cnic = getStringInput("Enter Citizen's CNIC: ");
            Citizen* c = populationMgr.searchByCNIC(cnic);
            
            if (c) {
                lat = c->latitude;
                lon = c->longitude;
                coordsFound = true;
                cout << "\nCitizen found: " << c->name 
                     << " at (" << lat << ", " << lon << ")\n";
            } else {
                cout << "Citizen not found!\n";
            }
            break;
        }
        case 2: {
            // From Hospital
            cout << "\n--- Available Hospitals ---\n";
            hospitalMgr.listHospitals();
            
            string hospitalID = getStringInput("\nEnter Hospital ID: ");
            Hospital* hospital = hospitalMgr.searchById(hospitalID);
            
            if (hospital) {
                lat = hospital->latitude;
                lon = hospital->longitude;
                coordsFound = true;
                cout << "\nHospital found: " << hospital->name 
                     << " at (" << lat << ", " << lon << ")\n";
            } else {
                cout << "Hospital not found!\n";
            }
            break;
        }
        case 3: {
            // Manual
            lat = getDoubleInput("Enter Latitude: ");
            lon = getDoubleInput("Enter Longitude: ");
            coordsFound = true;
            break;
        }
        default:
            cout << "Invalid choice!\n";
            return;
    }
    
    if (coordsFound) {
        double distance;
        SchoolNode* nearest = schoolTree.findNearestByCoord(lat, lon, &distance);
        
        if (nearest) {
            cout << "\n=== NEAREST SCHOOL ===\n";
            displaySchoolDetails(nearest);
            cout << "Distance: " << distance << " units\n";
        } else {
            cout << "No schools available.\n";
        }
    }
}

int main() {
    HospitalManager hospitalMgr;
    PharmacyManager pharmacyMgr;
    PopulationManager populationMgr;
    SchoolTree schoolTree;

    cout << "\n===================================================\n";
    cout << "        SMART CITY MANAGEMENT SYSTEM\n";
    cout << "   Healthcare, Education, Pharmacy & Population\n";
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

    cout << "Loading schools from CSV...\n";
    schoolTree.loadSchoolsFromCSV("SmartCity_dataset/schools.csv");
    cout << " Schools loaded!\n";

    cout << "Loading departments from CSV...\n";
    schoolTree.loadDepartmentsFromCSV("SmartCity_dataset/department.csv");
    cout << " Departments loaded!\n";

    cout << "Loading classes from CSV...\n";
    schoolTree.loadClassesFromCSV("SmartCity_dataset/classroom.csv");
    cout << " Classes loaded!\n";

    cout << "Loading students from CSV...\n";
    schoolTree.loadStudentsFromCSV("SmartCity_dataset/students.csv");
    cout << " Students loaded!\n";

    cout << "\nPress Enter to continue to main menu...";
    cin.get();

    int choice;
    do {
        displayMenu();
        
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input! Please enter a number.\n";
            continue;
        }
        cin.ignore(1000, '\n');

        switch (choice) {
            // ========== HOSPITAL OPERATIONS =========
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
                        cout << "\n" << (i + 1) << ".";
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
            
            // ========== SCHOOL OPERATIONS =========
            case 10: {
                printHeader("ALL SCHOOLS");
                schoolTree.listSchools();
                break;
            }
            
            case 11: {
                printHeader("FULL SCHOOL TREE");
                schoolTree.displayFullTree();
                break;
            }
            
            case 12: {
                printHeader("SEARCH SCHOOL BY ID");
                string schoolID = getStringInput("Enter School ID: ");
                
                SchoolNode* school = schoolTree.searchSchoolByID(schoolID);
                if (school) {
                    displaySchoolDetails(school);
                } else {
                    cout << "School not found!\n";
                }
                break;
            }
            
            // ========== POPULATION OPERATIONS ==========
            case 13: {
                printHeader("ALL CITIZENS");
                populationMgr.displayAllCitizens();
                break;
            }
            
            case 14: {
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
            
            case 15: {
                printHeader("HOUSEHOLD DETAILS");
                string sector = getStringInput("Enter Sector (e.g., G-10): ");
                string street = getStringInput("Enter Street No (e.g., 22): ");
                string house = getStringInput("Enter House No (e.g., 180): ");
                
                populationMgr.displayHousehold(sector, street, house);
                break;
            }
            
            case 16: {
                printHeader("FAMILY TREE");
                string headCNIC = getStringInput("Enter CNIC of household head: ");
                populationMgr.displayFamilyTree(headCNIC);
                break;
            }
            
            case 17: {
                printHeader("AGE DISTRIBUTION REPORT");
                populationMgr.generateAgeDistribution();
                break;
            }
            
            case 18: {
                printHeader("OCCUPATION SUMMARY REPORT");
                populationMgr.generateOccupationSummary();
                break;
            }
            
            case 19: {
                printHeader("POPULATION DENSITY REPORT");
                populationMgr.generatePopulationDensity();
                break;
            }
            
            case 20: {
                printHeader("GENDER RATIO REPORT");
                populationMgr.generateGenderRatio();
                break;
            }
            
            // ========== NEAREST LOCATION FINDER =========
            case 21: {
                findNearestHospital(hospitalMgr, populationMgr, schoolTree);
                break;
            }
            
            case 22: {
                findNearestSchool(schoolTree, populationMgr, hospitalMgr);
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
                cout << "Invalid choice! Please select a valid option (0-22).\n";
                break;
            }
        }

    } while (choice != 0);

    return 0;
}