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
    string gender;  // 'M' or 'F'

    Citizen();
    Citizen(const string& c, const string& n, int a, const string& o, const string& g);
};

#endif
