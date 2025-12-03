// Abdullah Noor
#ifndef DEPARTMENTNODE_H
#define DEPARTMENTNODE_H

#include <iostream>
using namespace std;
#include "ClassNode.h"

class DepartmentNode {
private:
    string departmentName;
    ClassNode** classes;
    int classCount, classCapacity;
    DepartmentNode* next;

public:
    DepartmentNode(string name) :departmentName(name), classCount(0), classCapacity(5), next(NULL) {
        classes = new ClassNode * [classCapacity];
    }

    ~DepartmentNode() {
        for (int i = 0; i < classCount; i++) delete classes[i];
        delete[] classes;
    }

    string getDepartmentName() { return departmentName; }
    ClassNode** getClasses() { return classes; }
    int getClassCount() { return classCount; }
    DepartmentNode* getNext() { return next; }

    void setNext(DepartmentNode* node) { next = node; }

    void addClass(ClassNode* cls) {
        if (classCount >= classCapacity) {
            classCapacity *= 2;
            ClassNode** newClasses = new ClassNode * [classCapacity];
            for (int i = 0; i < classCount; i++) newClasses[i] = classes[i];
            delete[] classes;
            classes = newClasses;
        }
        classes[classCount++] = cls;
    }

    void display() {
        cout << "  Department: " << departmentName << endl;
        cout << "  Classes (" << classCount << "):" << endl;
        for (int i = 0; i < classCount; i++) classes[i]->display();
    }
};
#endif