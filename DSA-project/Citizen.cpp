#include "Citizen.h"

Citizen::Citizen() : CNIC(""), name(""), age(0), occupation(""), gender(""), relation(""), parentCNIC(""), latitude(0.0), longitude(0.0) {}

Citizen::Citizen(const string& c, const string& n, int a, const string& o, const string& g)
    : CNIC(c), name(n), age(a), occupation(o), gender(g), relation(""), parentCNIC(""), latitude(0.0), longitude(0.0) {
}

Citizen::Citizen(const string& c, const string& n, int a, const string& o, const string& g, 
                 const string& rel, const string& pCNIC)
    : CNIC(c), name(n), age(a), occupation(o), gender(g), relation(rel), parentCNIC(pCNIC), latitude(0.0), longitude(0.0) {
}

Citizen::Citizen(const string& c, const string& n, int a, const string& o, const string& g, 
                 const string& rel, const string& pCNIC, double lat, double lon)
    : CNIC(c), name(n), age(a), occupation(o), gender(g), relation(rel), parentCNIC(pCNIC), latitude(lat), longitude(lon) {
}
