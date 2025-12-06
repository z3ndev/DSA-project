// Abdullah Noor
#ifndef SCHOOLNODE_H
#define SCHOOLNODE_H

#include <iostream>
using namespace std;
#include "DepartmentNode.h"

class SchoolNode {
private:
    string schoolID, name, sector;
    float rating;
    double latitude, longitude;
    string* subjects;
    int subjectCount;
    DepartmentNode** departments;
    int deptCount, deptCapacity;
    SchoolNode* next;

public:
    SchoolNode(string id, string n, string s, float r, double lat = 0.0, double lon = 0.0) 
        :schoolID(id), name(n), sector(s), rating(r), latitude(lat), longitude(lon), 
         subjectCount(0), deptCount(0), deptCapacity(5), next(NULL) {
        subjects = new string[10];
        departments = new DepartmentNode * [deptCapacity];
    }

    ~SchoolNode() {
        delete[] subjects;
        for (int i = 0; i < deptCount; i++) delete departments[i];
        delete[] departments;
    }

    string getSchoolID() { return schoolID; }
    string getName() { return name; }
    string getSector() { return sector; }
    float getRating() { return rating; }
    double getLatitude() { return latitude; }
    double getLongitude() { return longitude; }
    DepartmentNode** getDepartments() { return departments; }
    int getDeptCount() { return deptCount; }
    SchoolNode* getNext() { return next; }

    void setNext(SchoolNode* node) { next = node; }

    void addSubject(string subject) {
        if (subjectCount >= 10) {
            string* newSubjects = new string[subjectCount + 10];
            for (int i = 0; i < subjectCount; i++) newSubjects[i] = subjects[i];
            delete[] subjects;
            subjects = newSubjects;
        }
        subjects[subjectCount++] = subject;
    }

    void addDepartment(DepartmentNode* dept) {
        if (deptCount >= deptCapacity)
        {
            deptCapacity *= 2;
            DepartmentNode** newDepts = new DepartmentNode * [deptCapacity];
            for (int i = 0; i < deptCount; i++) newDepts[i] = departments[i];
            delete[] departments;
            departments = newDepts;
        }
        departments[deptCount++] = dept;
    }

    void display() {
        cout << "School ID: " << schoolID << endl;
        cout << "Name: " << name << endl;
        cout << "Sector: " << sector << endl;
        cout << "Rating: " << rating << endl;
        cout << "Coordinates: (" << latitude << ", " << longitude << ")" << endl;
        cout << "Subjects: ";
        for (int i = 0; i < subjectCount; i++) {
            cout << subjects[i];
            if (i < subjectCount - 1) cout << ", ";
        }
        cout << endl << "Departments (" << deptCount << "):" << endl;
        for (int i = 0; i < deptCount; i++) departments[i]->display();
    }
};
#endif