// Abdullah Noor

#ifndef SUBJECTHASHTABLE_H
#define SUBJECTHASHTABLE_H

#include <iostream>
using namespace std;
#include "SubjectHashNode.h"

class SubjectHashTable {
private:
    SubjectHashNode** table;
    int size;

    int hashFunction(string key) {
        int p = 31;
        int m = size;
        int hashVal = 0;
        int pPow = 1;
        for (char c : key) {
            hashVal = (hashVal + (c - 'a' + 1) * pPow) % m;
            pPow = (pPow * p) % m;
        }
        return hashVal;
    }

public:
    SubjectHashTable(int s = 100) :size(s) {
        table = new SubjectHashNode * [size];
        for (int i = 0; i < size; i++) table[i] = NULL;
    }

    ~SubjectHashTable() {
        for (int i = 0; i < size; i++) {
            SubjectHashNode* curr = table[i];
            while (curr) {
                SubjectHashNode* nextNode = curr->getNext();
                delete curr;
                curr = nextNode;
            }
        }
        delete[] table;
    }

    void insert(string subject, string schoolID) {
        int index = hashFunction(subject);
        SubjectHashNode* node = new SubjectHashNode(subject, schoolID);
        node->setNext(table[index]);
        table[index] = node;
    }

    void searchSchoolsBySubject(string subject) {
        int index = hashFunction(subject);
        SubjectHashNode* curr = table[index];
        cout << "Schools offering " << subject << ":" << endl;
        bool found = false;
        while (curr) {
            if (curr->getSubject() == subject) {
                cout << "  " << curr->getSchoolID() << endl;
                found = true;
            }
            curr = curr->getNext();
        }
        if (!found) cout << "  No schools found offering this subject." << endl;
    }

    void displayAll() {
        cout << "Subject Hash Table Contents:" << endl;
        for (int i = 0; i < size; i++) {
            cout << "Bucket " << i << ": ";
            SubjectHashNode* curr = table[i];
            while (curr) {
                cout << "(" << curr->getSubject() << ", " << curr->getSchoolID() << ") -> ";
                curr = curr->getNext();
            }
            cout << "NULL" << endl;
        }
    }
};
#endif