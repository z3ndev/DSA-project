#include "Citizen.h"

Citizen::Citizen() : CNIC(""), name(""), age(0), occupation(""), gender("") {}

Citizen::Citizen(const string& c, const string& n, int a, const string& o, const string& g)
    : CNIC(c), name(n), age(a), occupation(o), gender(g) {
}
