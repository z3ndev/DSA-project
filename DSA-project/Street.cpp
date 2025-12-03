#include "Street.h"

Street::Street(const string& sn) {
    streetNo = sn;
    houses = nullptr;
    next = nullptr;
}
