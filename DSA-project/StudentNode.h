// Abdullah Noor
#ifndef STUDENTNODE_H
#define STUDENTNODE_H

#include <iostream>
using namespace std;

class StudentNode {
private:
    string name, roll;
    int age;
    StudentNode* next;

public:
    StudentNode(string n, int a, string r) :name(n), age(a), roll(r), next(NULL) {}

    string getName() { return name; }
    int getAge() { return age; }
    string getRoll() { return roll; }
    StudentNode* getNext() { return next; }

    void setNext(StudentNode* node) { next = node; }

    void display() {
        cout << "      Name: " << name << ", Age: " << age << ", Roll: " << roll << endl;
    }
};
#endif