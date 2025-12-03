#include "CNICHashTable.h"

CNICNode::CNICNode(Citizen* c) {
    data = c;
    next = nullptr;
}

CNICHashTable::CNICHashTable() {
    for (int i = 0; i < TABLE_SIZE; i++)
        table[i] = nullptr;
}

int CNICHashTable::hashFunction(const string& cnic) {
    int hash = 0;
    for (int i = 0; i < cnic.length(); i++)
        hash = (hash * 31 + cnic[i]) % TABLE_SIZE;
    return hash;
}

void CNICHashTable::insert(Citizen* c) {
    int idx = hashFunction(c->CNIC);
    CNICNode* newNode = new CNICNode(c);
    newNode->next = table[idx];
    table[idx] = newNode;
}

Citizen* CNICHashTable::search(const string& cnic) {
    int idx = hashFunction(cnic);
    CNICNode* cur = table[idx];
    while (cur != nullptr) {
        if (cur->data->CNIC == cnic)
            return cur->data;
        cur = cur->next;
    }
    return nullptr;
}
