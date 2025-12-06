// Abdullah Noor
#include "MallManager.h"

MallManager::MallManager() : mallCount(0) {
    mallGraph = new MallGraph(MAX_MALLS);
}

MallManager::~MallManager() {
    delete mallGraph;
}

bool MallManager::addMall(const MallNode& mall) {
    if (mallCount >= MAX_MALLS) {
        cout << "Mall storage full.\n";
        return false;
    }
    
    // Add to mall data array
    malls[mallCount] = mall;
    
    // Add to graph for Dijkstra (coordinates as float)
    mallGraph->addNode(mall.getMallID(), (float)mall.getLatitude(), (float)mall.getLongitude());
    
    mallCount++;
    return true;
}

MallNode* MallManager::searchMallByID(const string& mallID) {
    for (int i = 0; i < mallCount; i++) {
        if (malls[i].getMallID() == mallID) {
            return &malls[i];
        }
    }
    return nullptr;
}

int MallManager::getMallIndexByID(const string& mallID) {
    for (int i = 0; i < mallCount; i++) {
        if (malls[i].getMallID() == mallID) {
            return i;
        }
    }
    return -1;
}

void MallManager::listMalls() {
    cout << "\n===== Mall List =====\n";
    for (int i = 0; i < mallCount; i++) {
        cout << (i + 1) << ") ID: " << malls[i].getMallID()
             << " | Name: " << malls[i].getName()
             << " | Sector: " << malls[i].getSector()
             << " | Coordinates: (" << malls[i].getLatitude() << ", " << malls[i].getLongitude() << ")\n";
    }
    cout << "======================\n";
}

void MallManager::displayMallDetails(const string& mallID) {
    MallNode* mall = searchMallByID(mallID);
    if (mall) {
        mall->display();
    } else {
        cout << "Mall not found!\n";
    }
}

bool MallManager::addProductToMall(const string& mallID, const string& productName, const string& category, int price) {
    MallNode* mall = searchMallByID(mallID);
    if (mall) {
        mall->getProductTable()->insert(productName, category, price);
        return true;
    }
    return false;
}

void MallManager::searchProductByName(const string& productName) {
    cout << "\n=== Searching for Product: " << productName << " ===\n";
    bool found = false;
    
    for (int i = 0; i < mallCount; i++) {
        ProductNode* product = malls[i].getProductTable()->searchByName(productName);
        if (product) {
            cout << "Found in Mall: " << malls[i].getName() << " (" << malls[i].getMallID() << ")\n";
            product->display();
            found = true;
        }
    }
    
    if (!found) {
        cout << "Product not found in any mall.\n";
    }
}

void MallManager::searchProductsByCategory(const string& category) {
    cout << "\n=== Products in Category: " << category << " ===\n";
    
    for (int i = 0; i < mallCount; i++) {
        cout << "\n--- Mall: " << malls[i].getName() << " ---\n";
        malls[i].getProductTable()->searchByCategory(category);
    }
}

bool MallManager::loadMallsFromCSV(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file: " << filename << endl;
        return false;
    }

    string line;
    getline(file, line); // Skip header

    while (getline(file, line)) {
        if (line.empty()) continue;
        
        stringstream ss(line);
        string id, name, sector, coordStr;

        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, sector, ',');

        // Parse coordinates (quoted "lat, lon")
        getline(ss, coordStr);
        if (!coordStr.empty() && coordStr.front() == '"' && coordStr.back() == '"') {
            coordStr = coordStr.substr(1, coordStr.length() - 2);
        }

        double latitude = 0.0, longitude = 0.0;
        stringstream coordStream(coordStr);
        string latStr, lonStr;
        if (getline(coordStream, latStr, ',') && getline(coordStream, lonStr)) {
            size_t start = latStr.find_first_not_of(" \t\r\n");
            size_t end = latStr.find_last_not_of(" \t\r\n");
            if (start != string::npos && end != string::npos) {
                latStr = latStr.substr(start, end - start + 1);
            }
            start = lonStr.find_first_not_of(" \t\r\n");
            end = lonStr.find_last_not_of(" \t\r\n");
            if (start != string::npos && end != string::npos) {
                lonStr = lonStr.substr(start, end - start + 1);
            }
            try { latitude = stod(latStr); } catch (...) { latitude = 0.0; }
            try { longitude = stod(lonStr); } catch (...) { longitude = 0.0; }
        }

        MallNode mall(id, name, sector, latitude, longitude);
        addMall(mall);
    }
    file.close();
    return true;
}

bool MallManager::loadProductsFromCSV(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file: " << filename << endl;
        return false;
    }

    string line;
    getline(file, line); // Skip header

    while (getline(file, line)) {
        if (line.empty()) continue;
        
        stringstream ss(line);
        string mallID, productName, category, priceStr;

        getline(ss, mallID, ',');
        getline(ss, productName, ',');
        getline(ss, category, ',');
        getline(ss, priceStr);

        int price = 0;
        try { price = stoi(priceStr); } catch (...) { price = 0; }

        if (!addProductToMall(mallID, productName, category, price)) {
            cout << "Warning: Mall " << mallID << " not found for product " << productName << endl;
        }
    }
    file.close();
    return true;
}

bool MallManager::loadMallEdgesFromCSV(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file: " << filename << endl;
        return false;
    }

    string line;
    getline(file, line); // Skip header

    while (getline(file, line)) {
        if (line.empty()) continue;
        
        stringstream ss(line);
        string fromMallID, toMallID, distanceStr;

        getline(ss, fromMallID, ',');
        getline(ss, toMallID, ',');
        getline(ss, distanceStr);

        int distance = 0;
        try { distance = stoi(distanceStr); } catch (...) { distance = 0; }

        int fromIndex = getMallIndexByID(fromMallID);
        int toIndex = getMallIndexByID(toMallID);

        if (fromIndex != -1 && toIndex != -1) {
            mallGraph->addEdge(fromIndex, toIndex, distance);
        } else {
            cout << "Warning: Edge between " << fromMallID << " and " << toMallID << " skipped (mall not found)\n";
        }
    }
    file.close();
    return true;
}

MallNode* MallManager::findNearestByCoord(double lat, double lon, double* outDistance) {
    if (mallCount == 0) return nullptr;

    MallNode* nearest = &malls[0];
    double minDistance = sqrt((lat - malls[0].getLatitude()) * (lat - malls[0].getLatitude()) +
                              (lon - malls[0].getLongitude()) * (lon - malls[0].getLongitude()));

    for (int i = 1; i < mallCount; i++) {
        double distance = sqrt((lat - malls[i].getLatitude()) * (lat - malls[i].getLatitude()) +
                               (lon - malls[i].getLongitude()) * (lon - malls[i].getLongitude()));
        if (distance < minDistance) {
            minDistance = distance;
            nearest = &malls[i];
        }
    }

    if (outDistance != nullptr) {
        *outDistance = minDistance;
    }

    return nearest;
}

bool MallManager::findShortestPath(const string& startMallID, const string& endMallID, 
                                   string* path, int& pathLength, int& totalDistance) {
    int startIndex = getMallIndexByID(startMallID);
    int endIndex = getMallIndexByID(endMallID);

    if (startIndex == -1 || endIndex == -1) {
        cout << "One or both malls not found!\n";
        return false;
    }

    mallGraph->dijkstra(startIndex, endIndex, path, pathLength, totalDistance);
    
    if (pathLength == 0 || totalDistance == INT_MAX) {
        cout << "No path found between malls.\n";
        return false;
    }
    
    return true;
}

MallNode* MallManager::getMallAt(int index) {
    if (index >= 0 && index < mallCount) {
        return &malls[index];
    }
    return nullptr;
}