// Abdullah Noor
#ifndef STUDENTNODE_H
#define STUDENTNODE_H

#include <iostream>
using namespace std;

class StudentNode {
private:
    string name;
    string studentID;
    StudentNode* next;

public:
    StudentNode(string n, string id) :name(n), studentID(id), next(NULL) {}

    string getName() { return name; }
    string getStudentID() { return studentID; }
    StudentNode* getNext() { return next; }

    void setNext(StudentNode* node) { next = node; }

    void display() {
        cout << "      Name: " << name << ", Student ID: " << studentID << endl;
    }
};
#endif