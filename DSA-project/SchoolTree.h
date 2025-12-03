// Abdullah Noor
#ifndef SCHOOLTREE_H
#define SCHOOLTREE_H

#include <iostream>
using namespace std;
#include <fstream>
#include <sstream>
#include "SchoolNode.h"

class SchoolTree {
private:
    SchoolNode* head;

public:
    SchoolTree() :head(NULL) {}

    ~SchoolTree() {
        SchoolNode* curr = head;
        while (curr) {
            SchoolNode* nextNode = curr->getNext();
            delete curr;
            curr = nextNode;
        }
    }

    void addSchool(SchoolNode* school) {
        if (!head) head = school;
        else {
            SchoolNode* curr = head;
            while (curr->getNext()) curr = curr->getNext();
            curr->setNext(school);
        }
    }

    bool addDepartmentToSchool(string schoolID, DepartmentNode* dept) {
        SchoolNode* school = searchSchoolByID(schoolID);
        if (school) {
            school->addDepartment(dept);
            return true;
        }
        return false;
    }

    bool addClassToDepartment(string schoolID, string deptName, ClassNode* cls) {
        SchoolNode* school = searchSchoolByID(schoolID);
        if (school) {
            DepartmentNode** depts = school->getDepartments();
            int count = school->getDeptCount();
            for (int i = 0; i < count; i++) {
                if (depts[i]->getDepartmentName() == deptName) {
                    depts[i]->addClass(cls);
                    return true;
                }
            }
        }
        return false;
    }

    bool addStudentToClass(string schoolID, string deptName, string className, StudentNode* student) {
        SchoolNode* school = searchSchoolByID(schoolID);
        if (school) {
            DepartmentNode** depts = school->getDepartments();
            int deptCount = school->getDeptCount();
            for (int i = 0; i < deptCount; i++) {
                if (depts[i]->getDepartmentName() == deptName) {
                    ClassNode** classes = depts[i]->getClasses();
                    int classCount = depts[i]->getClassCount();
                    for (int j = 0; j < classCount; j++) {
                        if (classes[j]->getClassName() == className) {
                            classes[j]->addStudent(student);
                            return true;
                        }
                    }
                }
            }
        }
        return false;
    }

    bool addFacultyToClass(string schoolID, string deptName, string className, FacultyNode* faculty) {
        SchoolNode* school = searchSchoolByID(schoolID);
        if (school) {
            DepartmentNode** depts = school->getDepartments();
            int deptCount = school->getDeptCount();
            for (int i = 0; i < deptCount; i++) {
                if (depts[i]->getDepartmentName() == deptName) {
                    ClassNode** classes = depts[i]->getClasses();
                    int classCount = depts[i]->getClassCount();
                    for (int j = 0; j < classCount; j++) {
                        if (classes[j]->getClassName() == className) {
                            classes[j]->addFaculty(faculty);
                            return true;
                        }
                    }
                }
            }
        }
        return false;
    }

    SchoolNode* searchSchoolByID(string schoolID) {
        SchoolNode* curr = head;
        while (curr) {
            if (curr->getSchoolID() == schoolID) return curr;
            curr = curr->getNext();
        }
        return NULL;
    }

    void displayFullTree() {
        SchoolNode* curr = head;
        while (curr) {
            curr->display();
            cout << "------------------------" << endl;
            curr = curr->getNext();
        }
    }

    void loadSchoolsFromCSV(string filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error opening file: " << filename << endl;
            return;
        }

        string line;
        getline(file, line);

        while (getline(file, line)) {
            stringstream ss(line);
            string id, name, sector, ratingStr, subjectsStr;

            getline(ss, id, ',');
            getline(ss, name, ',');
            getline(ss, sector, ',');
            getline(ss, ratingStr, ',');
            getline(ss, subjectsStr);

            if (subjectsStr.size() >= 2 && subjectsStr.front() == '"' && subjectsStr.back() == '"')
                subjectsStr = subjectsStr.substr(1, subjectsStr.size() - 2);

            float rating = stof(ratingStr);
            SchoolNode* school = new SchoolNode(id, name, sector, rating);

            stringstream s2(subjectsStr);
            string sub;
            while (getline(s2, sub, ',')) {
                if (sub.size() && sub.front() == ' ') sub = sub.substr(1);
                school->addSubject(sub);
            }

            addSchool(school);
        }
        file.close();
    }
};
#endif