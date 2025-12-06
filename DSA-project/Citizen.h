#ifndef CITIZEN_H
#define CITIZEN_H

#include <string>
using namespace std;

class Citizen {
public:
    string CNIC;
    string name;
    int age;
    string occupation;
    string gender;      // 'M' or 'F'
    string relation;    // Relationship: Head, Son, Daughter, etc.
    string parentCNIC;  // CNIC of parent/head if applicable
    double latitude;
    double longitude;

    Citizen();
    Citizen(const string& c, const string& n, int a, const string& o, const string& g);
    Citizen(const string& c, const string& n, int a, const string& o, const string& g, 
            const string& rel, const string& pCNIC);
    Citizen(const string& c, const string& n, int a, const string& o, const string& g, 
            const string& rel, const string& pCNIC, double lat, double lon);
};

#endif
