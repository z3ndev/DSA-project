#include "Patient.h"

Patient::Patient() : patientID(""), name(""), age(0), condition(""), hospitalID(""), next(nullptr) {
}

Patient::Patient(const string& id, const string& n, int a, const string& cond, const string& hospID)
    : patientID(id), name(n), age(a), condition(cond), hospitalID(hospID), next(nullptr) {
}