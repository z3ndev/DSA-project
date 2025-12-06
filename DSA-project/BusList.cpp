//Maaz Tahir
#include "BusList.h"

BusList::BusList() {
    head = nullptr;
    tail = nullptr;
    count = 0;
}

BusList::~BusList() {
    clear();
}

void BusList::addBus(TBus* bus) {
    insertAtEnd(bus);
}

void BusList::insertAtBeginning(TBus* bus) {
    BusListNode* newNode = new BusListNode(bus);
    
    if (head == nullptr) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head = newNode;
    }
    count++;
}

void BusList::insertAtEnd(TBus* bus) {
    BusListNode* newNode = new BusListNode(bus);
    
    if (tail == nullptr) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    count++;
}

bool BusList::removeBus(const string& busNo) {
    if (head == nullptr) return false;

    // Special case: removing head
    if (head->bus->getBusNo() == busNo) {
        BusListNode* temp = head;
        head = head->next;
        if (head == nullptr) tail = nullptr;
        delete temp->bus;
        delete temp;
        count--;
        return true;
    }

    // Search for the bus
    BusListNode* current = head;
    while (current->next != nullptr) {
        if (current->next->bus->getBusNo() == busNo) {
            BusListNode* temp = current->next;
            current->next = temp->next;
            
            if (temp == tail) tail = current;
            
            delete temp->bus;
            delete temp;
            count--;
            return true;
        }
        current = current->next;
    }
    return false;
}

TBus* BusList::removeFirst() {
    if (head == nullptr) return nullptr;

    BusListNode* temp = head;
    TBus* bus = temp->bus;
    
    head = head->next;
    if (head == nullptr) tail = nullptr;
    
    delete temp;
    count--;
    return bus;
}

TBus* BusList::removeLast() {
    if (head == nullptr) return nullptr;

    if (head == tail) {
        TBus* bus = head->bus;
        delete head;
        head = tail = nullptr;
        count--;
        return bus;
    }

    BusListNode* current = head;
    while (current->next != tail) {
        current = current->next;
    }

    TBus* bus = tail->bus;
    delete tail;
    tail = current;
    tail->next = nullptr;
    count--;
    return bus;
}

TBus* BusList::searchByBusNo(const string& busNo) {
    BusListNode* current = head;
    while (current != nullptr) {
        if (current->bus->getBusNo() == busNo) {
            return current->bus;
        }
        current = current->next;
    }
    return nullptr;
}

TBus* BusList::findNearestBusByStop(const string& stopID) {
    BusListNode* current = head;
    
    while (current != nullptr) {
        if (current->bus->getCurrentStop() == stopID) {
            return current->bus;
        }
        current = current->next;
    }
    
    return nullptr;
}

TBus* BusList::findNearestBusByCoordinates(double passengerLat, double passengerLon, 
                                           double* outDistance, TGraph* stopsGraph) {
    if (head == nullptr || stopsGraph == nullptr) return nullptr;

    TBus* nearestBus = nullptr;
    double minDistance = 1e18;

    BusListNode* current = head;
    while (current != nullptr) {
        TBus* bus = current->bus;
        string currentStop = bus->getCurrentStop();

        // Get stop coordinates from graph
        double stopLat = 0.0, stopLon = 0.0;
        if (stopsGraph->getNodeCoordinates(currentStop, stopLat, stopLon)) {
            // Calculate Euclidean distance
            double distance = sqrt(pow(passengerLat - stopLat, 2) + 
                                 pow(passengerLon - stopLon, 2));
            
            if (distance < minDistance) {
                minDistance = distance;
                nearestBus = bus;
            }
        }

        current = current->next;
    }

    if (outDistance != nullptr && nearestBus != nullptr) {
        *outDistance = minDistance;
    }

    return nearestBus;
}

bool BusList::isEmpty() const {
    return head == nullptr;
}

int BusList::getCount() const {
    return count;
}

void BusList::clear() {
    while (head != nullptr) {
        BusListNode* temp = head;
        head = head->next;
        delete temp->bus;
        delete temp;
    }
    tail = nullptr;
    count = 0;
}

void BusList::printAll() const {
    if (head == nullptr) {
        cout << "No buses in the system.\n";
        return;
    }

    cout << "\n===== Bus List =====\n";
    BusListNode* current = head;
    int index = 1;
    
    while (current != nullptr) {
        cout << index++ << ") ";
        current->bus->print();
        current = current->next;
    }
    cout << "Total Buses: " << count << "\n";
    cout << "====================\n";
}

void BusList::printBusDetails(const string& busNo) const {
    TBus* bus = const_cast<BusList*>(this)->searchByBusNo(busNo);
    if (bus) {
        bus->print();
    } else {
        cout << "Bus " << busNo << " not found.\n";
    }
}