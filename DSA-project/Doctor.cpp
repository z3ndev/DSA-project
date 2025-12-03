#include "Doctor.h"

Doctor::Doctor() : doctorID(""), name(""), specialization(""), hospitalID(""), next(nullptr) {
}

Doctor::Doctor(const string& id, const string& n, const string& spec, const string& hospID)
    : doctorID(id), name(n), specialization(spec), hospitalID(hospID), next(nullptr) {
}