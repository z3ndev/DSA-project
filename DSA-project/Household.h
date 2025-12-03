#ifndef HOUSEHOLD_H
#define HOUSEHOLD_H

#include "Citizen.h"

class Household {
public:
    string houseNo;
    Citizen** members;    // Array of citizens
    int memberCount;
    int maxMembers;

    Household* firstChild;   // For tree: first child household (if needed, optional)
    Household* nextSibling;  // For tree: next house in street

    Household(const string& hn);
    ~Household();
    void addMember(Citizen* c);
};

#endif
