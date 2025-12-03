// Abdullah Noor
#ifndef FACULTYNODE_H
#define FACULTYNODE_H

#include <iostream>
using namespace std;

class FacultyNode {
private:
    string name, subject;
    FacultyNode* next;

public:
    FacultyNode(string n, string s) :name(n), subject(s), next(NULL) {}

    string getName() { return name; }
    string getSubject() { return subject; }
    FacultyNode* getNext() { return next; }

    void setNext(FacultyNode* node) { next = node; }

    void display() {
        cout << "      Name: " << name << ", Subject: " << subject << endl;
    }
};
#endif