#ifndef DOCTOR_H
#define DOCTOR_H

#include <string>
using namespace std;

class Doctor {
public:
    string doctorID;
    string name;
    string specialization;
    string hospitalID;  // Which hospital they work at
    
    Doctor* next;  // For linked list
    
    Doctor();
    Doctor(const string& id, const string& n, const string& spec, const string& hospID);
};

#endif