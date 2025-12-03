#include "PatientManager.h"
#include <iostream>
using namespace std;

PatientManager::PatientManager() : head(nullptr), patientCount(0) {
}

PatientManager::~PatientManager() {
    Patient* current = head;
    while (current != nullptr) {
        Patient* next = current->next;
        delete current;
        current = next;
    }
}

bool PatientManager::addPatient(const string& id, const string& name, int age, const string& condition, const string& hospitalID) {
    // Check if patient ID already exists
    if (searchPatient(id) != nullptr) {
        cout << "Error: Patient with ID '" << id << "' already exists!\n";
        return false;
    }
    
    // Create new patient
    Patient* newPatient = new Patient(id, name, age, condition, hospitalID);
    
    // Add to front of list
    newPatient->next = head;
    head = newPatient;
    patientCount++;
    
    cout << " Patient admitted successfully!\n";
    return true;
}

bool PatientManager::dischargePatient(const string& patientID) {
    Patient* current = head;
    Patient* previous = nullptr;
    
    while (current != nullptr) {
        if (current->patientID == patientID) {
            // Found the patient to remove
            if (previous == nullptr) {
                // Removing head
                head = current->next;
            } else {
                previous->next = current->next;
            }
            
            cout << " Patient " << current->name << " (ID: " << patientID << ") has been discharged.\n";
            delete current;
            patientCount--;
            return true;
        }
        previous = current;
        current = current->next;
    }
    
    cout << " Patient with ID '" << patientID << "' not found!\n";
    return false;
}

Patient* PatientManager::searchPatient(const string& patientID) {
    Patient* current = head;
    while (current != nullptr) {
        if (current->patientID == patientID) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

void PatientManager::listAllPatients() {
    if (head == nullptr) {
        cout << "No patients in the system.\n";
        return;
    }
    
    cout << "\n===== ALL PATIENTS =====\n";
    Patient* current = head;
    int count = 1;
    
    while (current != nullptr) {
        cout << count << ") ID: " << current->patientID 
             << " | Name: " << current->name 
             << " | Age: " << current->age
             << " | Condition: " << current->condition
             << " | Hospital: " << current->hospitalID << "\n";
        current = current->next;
        count++;
    }
    cout << "Total Patients: " << patientCount << "\n";
    cout << "=========================\n";
}

void PatientManager::listPatientsByHospital(const string& hospitalID) {
    Patient* current = head;
    int count = 0;
    
    cout << "\n===== PATIENTS AT HOSPITAL " << hospitalID << " =====\n";
    
    while (current != nullptr) {
        if (current->hospitalID == hospitalID) {
            cout << ++count << ") ID: " << current->patientID 
                 << " | Name: " << current->name 
                 << " | Age: " << current->age
                 << " | Condition: " << current->condition << "\n";
        }
        current = current->next;
    }
    
    if (count == 0) {
        cout << "No patients found at this hospital.\n";
    } else {
        cout << "Total: " << count << " patient(s)\n";
    }
    cout << "==========================================\n";
}