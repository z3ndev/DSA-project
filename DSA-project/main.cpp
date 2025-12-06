#include <iostream>
#include <iomanip>
#include <climits>
#include "HospitalManager.h"
#include "PharmacyManager.h"
#include "PopulationManager.h"
#include "SchoolTree.h"
#include "MallManager.h"
#include "FacilityManager.h"
#include "TransportManager.h"
#include "AirportRailManager.h"  // ADD THIS

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

string getStringInput(const string& prompt) {
    string value;
    cout << prompt;
    getline(cin, value);
    return value;
}

int getIntInput(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(1000, '\n');
            return value;
        }
        else {
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
            }
            else {
                cout << "Error: Value cannot be negative! Please enter a non-negative number.\n";
            }
        }
        else {
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
        }
        else {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input! Please enter a number.\n";
        }
    }
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

// ==================== UNIVERSAL INTERACTIVE NEAREST SEARCH ====================
void universalNearestSearch(HospitalManager& hospitalMgr, MallManager& mallMgr,
    FacilityManager& facilityMgr, SchoolTree& schoolTree,
    PopulationManager& populationMgr) {

    printHeader("UNIVERSAL NEAREST SEARCH");

    cout << "\nAvailable types: Hospital, Mall, School, Facility (Park, Mosque, Police, Fire)\n";

    // Step 1: Ask WHAT they want to find (TARGET/DESTINATION)
    cout << "\nWhat do you want to find? (e.g., Hospital, Mall, School, Park, Mosque, Police, Fire)\n";
    cout << "Enter type: ";
    string targetType;
    getline(cin, targetType);

    if (targetType.empty()) {
        cout << "Invalid input. Search cancelled.\n";
        return;
    }

    // Step 2: Ask FROM WHAT they want to find it (SOURCE)
    cout << "\nYou want to find nearest " << targetType << " from what?\n";
    cout << "Enter source type: ";
    string sourceType;
    getline(cin, sourceType);

    if (sourceType.empty()) {
        cout << "Invalid input. Search cancelled.\n";
        return;
    }

    // Step 3: Determine if SAME TYPE or CROSS TYPE
    bool sameType = (targetType == sourceType);

    if (sameType) {
        // ==================== SAME TYPE: Use Dijkstra ====================
        cout << "\n--- Same-type search detected: Using Dijkstra's algorithm ---\n";

        // List available entities of this type
        if (targetType == "Hospital") {
            hospitalMgr.listHospitals();
        }
        else if (targetType == "Mall") {
            mallMgr.listMalls();
        }
        else if (targetType == "School") {
            schoolTree.listSchools();
        }
        else {
            facilityMgr.listFacilities(targetType);
        }

        cout << "\nEnter the ID of starting " << sourceType << ": ";
        string startID;
        getline(cin, startID);

        // Validate source exists
        bool sourceValid = false;
        if (sourceType == "Hospital") {
            sourceValid = (hospitalMgr.searchById(startID) != nullptr);
        }
        else if (sourceType == "Mall") {
            sourceValid = (mallMgr.searchMallByID(startID) != nullptr);
        }
        else if (sourceType == "School") {
            sourceValid = (schoolTree.searchSchoolByID(startID) != nullptr);
        }
        else {
            sourceValid = (facilityMgr.searchFacilityByID(startID) != nullptr);
        }

        if (!sourceValid) {
            cout << "Invalid " << sourceType << " ID!\n";
            return;
        }

        // Find nearest using Dijkstra
        cout << "\nSearching for nearest " << targetType << " from " << startID << "...\n";

        string path[100];
        int pathLength = 0;
        int minDistance = INT_MAX;
        string nearestID = "";

        if (targetType == "Hospital") {
            // Hospital to Hospital
            for (int i = 0; i < hospitalMgr.getCount(); i++) {
                Hospital* h = hospitalMgr.getHospitalAt(i);
                if (h && h->id != startID) {
                    int distance = 0;
                    int tempPathLen = 0;

                    if (hospitalMgr.findShortestPath(startID, h->id, path, tempPathLen, distance)) {
                        if (distance < minDistance) {
                            minDistance = distance;
                            nearestID = h->id;
                            pathLength = tempPathLen;
                        }
                    }
                }
            }
        }
        else if (targetType == "Mall") {
            // Mall to Mall
            for (int i = 0; i < mallMgr.getMallCount(); i++) {
                MallNode* m = mallMgr.getMallAt(i);
                if (m && m->getMallID() != startID) {
                    int distance = 0;
                    int tempPathLen = 0;

                    if (mallMgr.findShortestPath(startID, m->getMallID(), path, tempPathLen, distance)) {
                        if (distance < minDistance) {
                            minDistance = distance;
                            nearestID = m->getMallID();
                            pathLength = tempPathLen;
                        }
                    }
                }
            }
        }
        else if (targetType == "School") {
            // School to School
            for (int i = 0; i < schoolTree.getSchoolCount(); i++) {
                SchoolNode* s = schoolTree.getSchoolAt(i);
                if (s && s->getSchoolID() != startID) {
                    int distance = 0;
                    int tempPathLen = 0;

                    if (schoolTree.findShortestPath(startID, s->getSchoolID(), path, tempPathLen, distance)) {
                        if (distance < minDistance) {
                            minDistance = distance;
                            nearestID = s->getSchoolID();
                            pathLength = tempPathLen;
                        }
                    }
                }
            }
        }
        else {
            // Facility to Facility (same type)
            for (int i = 0; i < facilityMgr.getFacilityCount(); i++) {
                FacilityNode* f = facilityMgr.getFacilityAt(i);
                if (f && f->getType() == targetType && f->getID() != startID) {
                    int distance = 0;
                    int tempPathLen = 0;

                    if (facilityMgr.findShortestPath(startID, f->getID(), path, tempPathLen, distance)) {
                        if (distance < minDistance) {
                            minDistance = distance;
                            nearestID = f->getID();
                            pathLength = tempPathLen;
                        }
                    }
                }
            }
        }

        if (nearestID.empty() || minDistance == INT_MAX) {
            cout << "\nNo reachable " << targetType << " found from " << startID << ".\n";
            return;
        }

        // Display result with path
        cout << "\n========== RESULT ==========\n";
        cout << "Nearest " << targetType << ": " << nearestID << endl;
        cout << "Total Distance: " << minDistance << " units\n";

        // Reconstruct and show detailed path
        if (targetType == "Hospital") {
            hospitalMgr.findShortestPath(startID, nearestID, path, pathLength, minDistance);
        }
        else if (targetType == "Mall") {
            mallMgr.findShortestPath(startID, nearestID, path, pathLength, minDistance);
        }
        else if (targetType == "School") {
            schoolTree.findShortestPath(startID, nearestID, path, pathLength, minDistance);
        }
        else {
            facilityMgr.findShortestPath(startID, nearestID, path, pathLength, minDistance);
        }

        cout << "\nPath:\n";
        for (int i = 0; i < pathLength; i++) {
            cout << (i + 1) << ". " << path[i];
            if (i < pathLength - 1) cout << " -->";
            cout << endl;
        }
        cout << "============================\n";

    }
    else {
        // ==================== CROSS TYPE: Use Euclidean Distance ====================
        // ... (rest of cross-type search remains the same)
    }
}

void displayMenu() {
    cout << "\n==================== SMART CITY MANAGEMENT SYSTEM ====================\n";
    cout << "\n[1] HOSPITALS:\n";
    cout << "  1. List all hospitals\n";
    cout << "  2. Get hospital(s) with most emergency beds\n";
    cout << "  3. Search hospital by ID\n";
    cout << "  4. Update emergency beds\n";
    cout << "  5. Add new hospital\n";

    cout << "\n[2] PHARMACIES & MEDICINES:\n";
    cout << "  6. List all pharmacies\n";
    cout << "  7. Display all medicines\n";
    cout << "  8. Search medicine by name\n";
    cout << "  9. Search medicine by formula\n";

    cout << "\n[3] SCHOOLS & EDUCATION:\n";
    cout << "  10. List all schools\n";
    cout << "  11. Display full school tree\n";
    cout << "  12. Search school by ID\n";

    cout << "\n[4] COMMERCIAL SECTOR (MALLS):\n";
    cout << "  13. List all malls\n";
    cout << "  14. Search mall by ID\n";
    cout << "  15. Add product to mall\n";
    cout << "  16. Search product by name (across all malls)\n";
    cout << "  17. Search products by category\n";

    cout << "\n[5] PUBLIC FACILITIES (Parks, Mosques, etc):\n";
    cout << "  18. List all facilities\n";
    cout << "  19. List facilities by type\n";
    cout << "  20. Search facility by ID\n";

    cout << "\n[6] POPULATION & HOUSING:\n";
    cout << "  21. Display all citizens\n";
    cout << "  22. Search citizen by CNIC\n";
    cout << "  23. Display household details\n";
    cout << "  24. Display family tree\n";
    cout << "  25. Age distribution report\n";
    cout << "  26. Occupation summary report\n";
    cout << "  27. Population density report\n";
    cout << "  28. Gender ratio report\n";

    cout << "\n[7] TRANSPORT SYSTEM:\n";
    cout << "  30. List all buses\n";
    cout << "  31. Search bus by number\n";
    cout << "  32. List all bus stops\n";
    cout << "  33. Find shortest path between stops (Dijkstra)\n";
    cout << "  34. View bus travel history\n";
    cout << "  35. Move bus to next stop\n";
    cout << "  36. Find nearest bus to passenger location\n";

    cout << "\n[8] UNIVERSAL NEAREST SEARCH:\n";
    cout << "  29. Find Nearest (Any Type - Smart: Same=Dijkstra, Cross=Euclidean)\n";

    cout << "\n[9] AIRPORT & RAILWAY SYSTEM:\n";
    cout << "  37. Display airport/rail network\n";
    cout << "  38. Find shortest route (Airport/Rail)\n";

    cout << "\n  0. Exit\n";
    cout << "\n======================================================================\n";
    cout << "Enter your choice: ";
}

int main() {
    HospitalManager hospitalMgr;
    PharmacyManager pharmacyMgr;
    PopulationManager populationMgr;
    SchoolTree schoolTree;
    MallManager mallMgr;
    FacilityManager facilityMgr;
    TransportManager transportMgr;
    AirportRailManager airportRailMgr;  // ADD THIS

    cout << "\n======================================================================\n";
    cout << "                 SMART CITY MANAGEMENT SYSTEM\n";
    cout << "  Healthcare | Education | Pharmacy | Malls | Facilities | Population | Transport | Airport/Rail\n";
    cout << "======================================================================\n";

    // Load data from CSV files
    cout << "\n--- LOADING DATA ---\n";

    cout << "Loading hospitals from CSV...\n";
    if (hospitalMgr.loadFromCSV("SmartCity_dataset/hospitals.csv")) {
        cout << "   Hospitals loaded successfully!\n";
    }
    else {
        cout << "   Failed to load hospitals.\n";
    }

    cout << "Loading hospital edges from CSV...\n";
    if (hospitalMgr.loadHospitalEdgesFromCSV("SmartCity_dataset/hospital_edges.csv")) {
        cout << "   Hospital edges loaded successfully!\n";
    }
    else {
        cout << "   Failed to load hospital edges.\n";
    }

    cout << "Loading pharmacies from CSV...\n";
    if (pharmacyMgr.loadFromCSV("SmartCity_dataset/pharmacies.csv")) {
        cout << "   Pharmacies loaded successfully!\n";
    }
    else {
        cout << "   Failed to load pharmacies.\n";
    }

    cout << "Loading population data from CSV...\n";
    if (populationMgr.loadFromCSV("SmartCity_dataset/population.csv")) {
        cout << "   Population data loaded successfully!\n";
    }
    else {
        cout << "   Failed to load population data.\n";
    }

    cout << "Loading schools from CSV...\n";
    schoolTree.loadSchoolsFromCSV("SmartCity_dataset/schools.csv");
    cout << "   Schools loaded!\n";

    cout << "Loading school edges from CSV...\n";
    if (schoolTree.loadSchoolEdgesFromCSV("SmartCity_dataset/school_edges.csv")) {
        cout << "   School edges loaded successfully!\n";
    }
    else {
        cout << "   Failed to load school edges.\n";
    }

    cout << "Loading departments from CSV...\n";
    schoolTree.loadDepartmentsFromCSV("SmartCity_dataset/department.csv");
    cout << "   Departments loaded!\n";

    cout << "Loading classes from CSV...\n";
    schoolTree.loadClassesFromCSV("SmartCity_dataset/classroom.csv");
    cout << "   Classes loaded!\n";

    cout << "Loading students from CSV...\n";
    schoolTree.loadStudentsFromCSV("SmartCity_dataset/students.csv");
    cout << "   Students loaded!\n";

    cout << "Loading malls from CSV...\n";
    if (mallMgr.loadMallsFromCSV("SmartCity_dataset/malls.csv")) {
        cout << "   Malls loaded successfully!\n";
    }
    else {
        cout << "   Failed to load malls.\n";
    }

    cout << "Loading products from CSV...\n";
    if (mallMgr.loadProductsFromCSV("SmartCity_dataset/products.csv")) {
        cout << "   Products loaded successfully!\n";
    }
    else {
        cout << "   Failed to load products.\n";
    }

    cout << "Loading mall edges from CSV...\n";
    if (mallMgr.loadMallEdgesFromCSV("SmartCity_dataset/mall_edges.csv")) {
        cout << "   Mall edges loaded successfully!\n";
    }
    else {
        cout << "   Failed to load mall edges.\n";
    }

    cout << "Loading facilities from CSV...\n";
    if (facilityMgr.loadFacilitiesFromCSV("SmartCity_dataset/facilities.csv")) {
        cout << "   Facilities loaded successfully!\n";
    }
    else {
        cout << "   Failed to load facilities.\n";
    }

    cout << "Loading facility edges from CSV...\n";
    if (facilityMgr.loadFacilityEdgesFromCSV("SmartCity_dataset/facility_edges.csv")) {
        cout << "   Facility edges loaded successfully!\n";
    }
    else {
        cout << "   Failed to load facility edges.\n";
    }

    // TRANSPORT LOADING
    cout << "Loading bus stops from CSV...\n";
    if (transportMgr.loadStopsFromCSV("SmartCity_dataset/stops.csv")) {
        cout << "   Bus stops loaded successfully!\n";
    }
    else {
        cout << "   Failed to load bus stops.\n";
    }

    cout << "Loading stop edges from CSV...\n";
    if (transportMgr.loadStopEdgesFromCSV("SmartCity_dataset/stop_edges.csv")) {
        cout << "   Stop edges loaded successfully!\n";
    }
    else {
        cout << "   Failed to load stop edges.\n";
    }

    cout << "Loading buses from CSV...\n";
    if (transportMgr.loadBusesFromCSV("SmartCity_dataset/buses.csv")) {
        cout << "   Buses loaded successfully!\n";
    }
    else {
        cout << "   Failed to load buses.\n";
    }

    // AIRPORT/RAIL LOADING
    cout << "Loading airport/rail nodes from CSV...\n";
    if (airportRailMgr.loadNodesFromCSV("SmartCity_dataset/airport_rail_nodes.csv")) {
        cout << "   Airport/Rail nodes loaded successfully!\n";
    }
    else {
        cout << "   Failed to load airport/rail nodes.\n";
    }

    cout << "Loading airport/rail edges from CSV...\n";
    if (airportRailMgr.loadEdgesFromCSV("SmartCity_dataset/airport_rail_edges.csv")) {
        cout << "   Airport/Rail edges loaded successfully!\n";
    }
    else {
        cout << "   Failed to load airport/rail edges.\n";
    }

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
                cout << "\nFound " << count << " hospital(s) with maximum emergency beds:\n";
                for (int i = 0; i < count; i++) {
                    cout << "\n" << (i + 1) << ".";
                    displayHospitalDetails(results[i]);
                }
            }
            else {
                cout << "No hospitals available.\n";
            }
            break;
        }

        case 3: {
            printHeader("SEARCH HOSPITAL BY ID");
            hospitalMgr.listHospitals();
            string searchId = getStringInput("\nEnter Hospital ID: ");
            Hospital* h = hospitalMgr.searchById(searchId);
            if (h) {
                displayHospitalDetails(h);
            }
            else {
                cout << "Hospital not found!\n";
            }
            break;
        }

        case 4: {
            printHeader("UPDATE EMERGENCY BEDS");
            hospitalMgr.listHospitals();
            string hospitalId = getStringInput("\nEnter Hospital ID: ");
            int newBeds = getPositiveIntInput("Enter new emergency bed count (must be >= 0): ");
            if (hospitalMgr.updateEmergencyBeds(hospitalId, newBeds)) {
                cout << "  Emergency beds updated successfully!\n";
            }
            else {
                cout << "  Hospital not found or update failed.\n";
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
            pharmacyMgr.displayAllMedicines();
            string searchName = getStringInput("\nEnter medicine name: ");
            Medicine* med = pharmacyMgr.searchMedicineByName(searchName);
            if (med) {
                displayMedicineDetails(med);
            }
            else {
                cout << "Medicine not found!\n";
            }
            break;
        }

        case 9: {
            printHeader("SEARCH MEDICINE BY FORMULA");
            pharmacyMgr.displayAllMedicines();
            string searchFormula = getStringInput("\nEnter medicine formula: ");
            Medicine* med = pharmacyMgr.searchMedicineByFormula(searchFormula);
            if (med) {
                displayMedicineDetails(med);
            }
            else {
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
            schoolTree.listSchools();
            string schoolID = getStringInput("\nEnter School ID: ");
            SchoolNode* school = schoolTree.searchSchoolByID(schoolID);
            if (school) {
                displaySchoolDetails(school);
            }
            else {
                cout << "School not found!\n";
            }
            break;
        }

               // ========== MALL OPERATIONS =========
        case 13: {
            printHeader("ALL MALLS");
            mallMgr.listMalls();
            break;
        }

        case 14: {
            printHeader("SEARCH MALL BY ID");
            mallMgr.listMalls();
            string mallID = getStringInput("\nEnter Mall ID: ");
            mallMgr.displayMallDetails(mallID);
            break;
        }

        case 15: {
            printHeader("ADD PRODUCT TO MALL");
            mallMgr.listMalls();
            string mallID = getStringInput("\nEnter Mall ID: ");
            string productName = getStringInput("Enter Product Name: ");
            string category = getStringInput("Enter Category: ");
            int price = getPositiveIntInput("Enter Price: ");
            if (mallMgr.addProductToMall(mallID, productName, category, price)) {
                cout << "  Product added successfully!\n";
            }
            else {
                cout << "  Mall not found!\n";
            }
            break;
        }

        case 16: {
            printHeader("SEARCH PRODUCT BY NAME");
            cout << "\n=== All Available Products ===\n";
            for (int i = 0; i < mallMgr.getMallCount(); i++) {
                MallNode* mall = mallMgr.getMallAt(i);
                if (mall) {
                    cout << "\n--- " << mall->getName() << " ---\n";
                    mall->getProductTable()->displayAll();
                }
            }
            string productName = getStringInput("\nEnter Product Name: ");
            mallMgr.searchProductByName(productName);
            break;
        }

        case 17: {
            printHeader("SEARCH PRODUCTS BY CATEGORY");
            cout << "\n=== All Available Products ===\n";
            for (int i = 0; i < mallMgr.getMallCount(); i++) {
                MallNode* mall = mallMgr.getMallAt(i);
                if (mall) {
                    cout << "\n--- " << mall->getName() << " ---\n";
                    mall->getProductTable()->displayAll();
                }
            }
            string category = getStringInput("\nEnter Category: ");
            mallMgr.searchProductsByCategory(category);
            break;
        }

               // ========== FACILITY OPERATIONS =========
        case 18: {
            printHeader("ALL FACILITIES");
            facilityMgr.listFacilities();
            break;
        }

        case 19: {
            printHeader("FACILITIES BY TYPE");
            facilityMgr.listFacilities();
            string type = getStringInput("\nEnter Facility Type (Park, Mosque, Police, Fire): ");
            facilityMgr.listFacilities(type);
            break;
        }

        case 20: {
            printHeader("SEARCH FACILITY BY ID");
            facilityMgr.listFacilities();
            string facilityID = getStringInput("\nEnter Facility ID: ");
            facilityMgr.displayFacilityDetails(facilityID);
            break;
        }

               // ========== POPULATION OPERATIONS ==========
        case 21: {
            printHeader("ALL CITIZENS");
            populationMgr.displayAllCitizens();
            break;
        }

        case 22: {
            printHeader("SEARCH CITIZEN BY CNIC");
            cout << "\n=== Sample Citizens (showing first 20) ===\n";
            populationMgr.displayAllCitizens();
            string searchCNIC = getStringInput("\nEnter CNIC (e.g., 61101-1111111-1): ");
            Citizen* c = populationMgr.searchByCNIC(searchCNIC);
            if (c) {
                displayCitizenDetails(c);
            }
            else {
                cout << "Citizen not found!\n";
            }
            break;
        }

        case 23: {
            printHeader("HOUSEHOLD DETAILS");
            cout << "\n=== Available Sectors ===\n";
            cout << "Sample sectors: G-10, F-8, F-10, G-9, etc.\n";
            string sector = getStringInput("\nEnter Sector (e.g., G-10): ");
            string street = getStringInput("Enter Street No (e.g., 22): ");
            string house = getStringInput("Enter House No (e.g., 180): ");
            populationMgr.displayHousehold(sector, street, house);
            break;
        }

        case 24: {
            printHeader("FAMILY TREE");
            cout << "\n=== Sample Citizens (showing first 10) ===\n";
            populationMgr.displayAllCitizens();
            string headCNIC = getStringInput("\nEnter CNIC of household head: ");
            populationMgr.displayFamilyTree(headCNIC);
            break;
        }

        case 25: {
            printHeader("AGE DISTRIBUTION REPORT");
            populationMgr.generateAgeDistribution();
            break;
        }

        case 26: {
            printHeader("OCCUPATION SUMMARY REPORT");
            populationMgr.generateOccupationSummary();
            break;
        }

        case 27: {
            printHeader("POPULATION DENSITY REPORT");
            populationMgr.generatePopulationDensity();
            break;
        }

        case 28: {
            printHeader("GENDER RATIO REPORT");
            populationMgr.generateGenderRatio();
            break;
        }

               // ========== UNIVERSAL NEAREST SEARCH =========
        case 29: {
            universalNearestSearch(hospitalMgr, mallMgr, facilityMgr, schoolTree, populationMgr);
            break;
        }

               // ========== TRANSPORT OPERATIONS =========
        case 30: {
            printHeader("ALL BUSES");
            transportMgr.printAllBuses();
            break;
        }

        case 31: {
            printHeader("SEARCH BUS BY NUMBER");
            transportMgr.printAllBuses();
            string busNo = getStringInput("\nEnter Bus Number: ");
            TBus* bus = transportMgr.getBus(busNo);
            if (bus) {
                cout << "\n=== BUS FOUND ===\n";
                bus->print();
                cout << "=================\n";
            }
            else {
                cout << "Bus not found!\n";
            }
            break;
        }

        case 32: {
            printHeader("ALL BUS STOPS");
            transportMgr.printAllStops();
            break;
        }

        case 33: {
            printHeader("SHORTEST PATH BETWEEN STOPS");
            transportMgr.printAllStops();
            string fromStop = getStringInput("\nEnter starting stop ID: ");
            string toStop = getStringInput("Enter destination stop ID: ");
            double distance = transportMgr.getShortestDistance(fromStop, toStop);
            if (distance >= 0) {
                cout << "\n  Shortest distance from " << fromStop << " to " << toStop
                    << ": " << distance << " km\n";
            }
            else {
                cout << "  No path found or invalid stops!\n";
            }
            break;
        }

        case 34: {
            printHeader("BUS TRAVEL HISTORY");
            transportMgr.printAllBuses();
            string busNo = getStringInput("\nEnter Bus Number: ");
            transportMgr.printBusHistory(busNo);
            break;
        }

        case 35: {
            printHeader("MOVE BUS TO NEXT STOP");
            transportMgr.printAllBuses();
            string busNo = getStringInput("\nEnter Bus Number: ");
            cout << "\n";
            transportMgr.printAllStops();
            string stopID = getStringInput("\nEnter Stop ID to move to: ");
            transportMgr.moveBus(busNo, stopID);
            break;
        }

        case 36: {
            printHeader("FIND NEAREST BUS TO PASSENGER");
            transportMgr.printAllBuses();
            cout << "\n";
            transportMgr.printAllStops();
            cout << "\nEnter passenger coordinates:\n";
            double lat = getDoubleInput("Latitude: ");
            double lon = getDoubleInput("Longitude: ");
            double distance;
            TBus* nearestBus = transportMgr.findNearestBus(lat, lon, &distance);
            if (nearestBus) {
                cout << "\n=== NEAREST BUS ===\n";
                nearestBus->print();
                cout << "Distance: " << distance << " units\n";
                cout << "===================\n";
            }
            else {
                cout << "No buses available.\n";
            }
            break;
        }

               // ========== AIRPORT & RAILWAY OPERATIONS =========
        case 37: {
            printHeader("AIRPORT & RAILWAY NETWORK");
            airportRailMgr.displayGraph();
            break;
        }

        case 38: {
            printHeader("SHORTEST ROUTE (AIRPORT/RAIL)");

            airportRailMgr.displayGraph();

            string fromLocation = getStringInput("\nEnter starting location: ");
            string toLocation = getStringInput("Enter destination: ");

            string path[100];
            int pathLength = 0;
            int totalDistance = 0;

            if (airportRailMgr.findShortestRoute(fromLocation, toLocation, path, pathLength, totalDistance)) {
                cout << "\n========== ROUTE FOUND ==========\n";
                cout << "Total Distance: " << totalDistance << " km\n";
                cout << "\nRoute:\n";
                for (int i = 0; i < pathLength; i++) {
                    cout << (i + 1) << ". " << path[i];
                    if (i < pathLength - 1) cout << " -->";
                    cout << endl;
                }
                cout << "=================================\n";
            }
            break;
        }

               // ========== EXIT ==========
        case 0: {
            cout << "\n======================================================================\n";
            cout << "                  Thank you for using\n";
            cout << "              Smart City Management System!\n";
            cout << "                       Goodbye!\n";
            cout << "======================================================================\n\n";
            break;
        }

        default: {
            cout << "Invalid choice! Please select a valid option (0-38).\n";
            break;
        }
        }

    } while (choice != 0);

    return 0;
}