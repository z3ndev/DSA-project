#ifndef PATIENT_H
#define PATIENT_H

#include <string>
using namespace std;

class Patient {
public:
    string patientID;
    string name;
    int age;
    string condition;
    string hospitalID;  // Which hospital they're admitted to
    
    Patient* next;  // For linked list
    
    Patient();
    Patient(const string& id, const string& n, int a, const string& cond, const string& hospID);
};

#endif