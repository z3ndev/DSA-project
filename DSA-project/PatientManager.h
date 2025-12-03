#ifndef PATIENT_MANAGER_H
#define PATIENT_MANAGER_H

#include "Patient.h"
#include <string>
using namespace std;

class PatientManager {
private:
    Patient* head;  // Head of linked list
    int patientCount;

public:
    PatientManager();
    ~PatientManager();
    
    // Add a new patient (admit)
    bool addPatient(const string& id, const string& name, int age, const string& condition, const string& hospitalID);
    
    // Discharge (remove) a patient by ID
    bool dischargePatient(const string& patientID);
    
    // Search patient by ID
    Patient* searchPatient(const string& patientID);
    
    // List all patients
    void listAllPatients();
    
    // List patients by hospital
    void listPatientsByHospital(const string& hospitalID);
    
    // Get count
    int getCount() const { return patientCount; }
};

#endif