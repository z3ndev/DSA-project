#ifndef DOCTOR_MANAGER_H
#define DOCTOR_MANAGER_H

#include "Doctor.h"
#include <string>
using namespace std;

class DoctorManager {
private:
    Doctor* head;  // Head of linked list
    int doctorCount;

public:
    DoctorManager();
    ~DoctorManager();
    
    // Add a new doctor
    bool addDoctor(const string& id, const string& name, const string& specialization, const string& hospitalID);
    
    // Fire (remove) a doctor by ID
    bool fireDoctor(const string& doctorID);
    
    // Search doctor by ID
    Doctor* searchDoctor(const string& doctorID);
    
    // List all doctors
    void listAllDoctors();
    
    // List doctors by hospital
    void listDoctorsByHospital(const string& hospitalID);
    
    // Get count
    int getCount() const { return doctorCount; }
};

#endif