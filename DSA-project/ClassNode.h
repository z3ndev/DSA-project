// Abdullah Noor
#ifndef CLASSNODE_H
#define CLASSNODE_H

#include <iostream>
using namespace std;
#include "StudentNode.h"
#include "FacultyNode.h"

class ClassNode {
private:
    string className;
    string classID;
    StudentNode* studentHead;
    FacultyNode* facultyHead;
    ClassNode* next;

public:
    ClassNode(string name, string id = "") 
        :className(name), classID(id), studentHead(NULL), facultyHead(NULL), next(NULL) {}

    ~ClassNode() {
        StudentNode* currStudent = studentHead;
        while (currStudent) {
            StudentNode* nextStudent = currStudent->getNext();
            delete currStudent;
            currStudent = nextStudent;
        }
        FacultyNode* currFaculty = facultyHead;
        while (currFaculty) {
            FacultyNode* nextFaculty = currFaculty->getNext();
            delete currFaculty;
            currFaculty = nextFaculty;
        }
    }

    string getClassName() { return className; }
    string getClassID() { return classID; }
    StudentNode* getStudentHead() { return studentHead; }
    FacultyNode* getFacultyHead() { return facultyHead; }
    ClassNode* getNext() { return next; }

    void setNext(ClassNode* node) { next = node; }

    void addStudent(StudentNode* s) {
        if (!studentHead) studentHead = s;
        else {
            StudentNode* curr = studentHead;
            while (curr->getNext()) curr = curr->getNext();
            curr->setNext(s);
        }
    }

    void addFaculty(FacultyNode* f) {
        if (!facultyHead) facultyHead = f;
        else {
            FacultyNode* curr = facultyHead;
            while (curr->getNext()) curr = curr->getNext();
            curr->setNext(f);
        }
    }

    void display() {
        cout << "    Class: " << className << " (ID: " << classID << ")" << endl;
        cout << "    Students:" << endl;
        StudentNode* currStudent = studentHead;
        while (currStudent) {
            currStudent->display();
            currStudent = currStudent->getNext();
        }
        cout << "    Faculty:" << endl;
        FacultyNode* currFaculty = facultyHead;
        while (currFaculty) {
            currFaculty->display();
            currFaculty = currFaculty->getNext();
        }
    }
};
#endif