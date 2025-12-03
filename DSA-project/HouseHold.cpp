#include "Household.h"
#include <iostream>

Household::Household(const string& hn) {
    houseNo = hn;
    memberCount = 0;
    maxMembers = 10; // can resize if needed
    members = new Citizen * [maxMembers];
    firstChild = nullptr;
    nextSibling = nullptr;
}

Household::~Household() {
    for (int i = 0; i < memberCount; i++)
        delete members[i];
    delete[] members;
}

void Household::addMember(Citizen* c) {
    if (memberCount < maxMembers)
        members[memberCount++] = c;
    else
        cerr << "Max members reached for house " << houseNo << endl;
}
