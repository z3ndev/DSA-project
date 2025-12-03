#include "DoctorManager.h"
#include <iostream>
using namespace std;

DoctorManager::DoctorManager() : head(nullptr), doctorCount(0) {
}

DoctorManager::~DoctorManager() {
    Doctor* current = head;
    while (current != nullptr) {
        Doctor* next = current->next;
        delete current;
        current = next;
    }
}

bool DoctorManager::addDoctor(const string& id, const string& name, const string& specialization, const string& hospitalID) {
    // Check if doctor ID already exists
    if (searchDoctor(id) != nullptr) {
        cout << "Error: Doctor with ID '" << id << "' already exists!\n";
        return false;
    }
    
    // Create new doctor
    Doctor* newDoctor = new Doctor(id, name, specialization, hospitalID);
    
    // Add to front of list
    newDoctor->next = head;
    head = newDoctor;
    doctorCount++;
    
    cout << " Doctor added successfully!\n";
    return true;
}

bool DoctorManager::fireDoctor(const string& doctorID) {
    Doctor* current = head;
    Doctor* previous = nullptr;
    
    while (current != nullptr) {
        if (current->doctorID == doctorID) {
            // Found the doctor to remove
            if (previous == nullptr) {
                // Removing head
                head = current->next;
            } else {
                previous->next = current->next;
            }
            
            cout << " Doctor " << current->name << " (ID: " << doctorID << ") has been removed.\n";
            delete current;
            doctorCount--;
            return true;
        }
        previous = current;
        current = current->next;
    }
    
    cout << " Doctor with ID '" << doctorID << "' not found!\n";
    return false;
}

Doctor* DoctorManager::searchDoctor(const string& doctorID) {
    Doctor* current = head;
    while (current != nullptr) {
        if (current->doctorID == doctorID) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

void DoctorManager::listAllDoctors() {
    if (head == nullptr) {
        cout << "No doctors in the system.\n";
        return;
    }
    
    cout << "\n===== ALL DOCTORS =====\n";
    Doctor* current = head;
    int count = 1;
    
    while (current != nullptr) {
        cout << count << ") ID: " << current->doctorID 
             << " | Name: " << current->name 
             << " | Specialization: " << current->specialization
             << " | Hospital: " << current->hospitalID << "\n";
        current = current->next;
        count++;
    }
    cout << "Total Doctors: " << doctorCount << "\n";
    cout << "=======================\n";
}

void DoctorManager::listDoctorsByHospital(const string& hospitalID) {
    Doctor* current = head;
    int count = 0;
    
    cout << "\n===== DOCTORS AT HOSPITAL " << hospitalID << " =====\n";
    
    while (current != nullptr) {
        if (current->hospitalID == hospitalID) {
            cout << ++count << ") ID: " << current->doctorID 
                 << " | Name: " << current->name 
                 << " | Specialization: " << current->specialization << "\n";
        }
        current = current->next;
    }
    
    if (count == 0) {
        cout << "No doctors found at this hospital.\n";
    } else {
        cout << "Total: " << count << " doctor(s)\n";
    }
    cout << "==========================================\n";
}