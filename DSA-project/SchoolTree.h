// Abdullah Noor
#ifndef SCHOOLTREE_H
#define SCHOOLTREE_H

#include <iostream>
using namespace std;
#include <fstream>
#include <sstream>
#include <cmath>
#include <climits>
#include "SchoolNode.h"
#include "SchoolGraph.h"  // ADD THIS

class SchoolTree {
private:
    SchoolNode* head;
    SchoolGraph* schoolGraph;  // ADD THIS - Graph for Dijkstra routing
    int schoolCount;  // ADD THIS - Track number of schools
    
    // Helper function to convert string to lowercase
    string toLowercase(const string& str) const {
        string result = str;
        for (size_t i = 0; i < result.length(); i++) {
            if (result[i] >= 'A' && result[i] <= 'Z') {
                result[i] = result[i] + ('a' - 'A');
            }
        }
        return result;
    }

public:
    SchoolTree() : head(NULL), schoolCount(0) {
        schoolGraph = new SchoolGraph(100);  // Initialize graph
    }

    ~SchoolTree() {
        SchoolNode* curr = head;
        while (curr) {
            SchoolNode* nextNode = curr->getNext();
            delete curr;
            curr = nextNode;
        }
        delete schoolGraph;  // Clean up graph
    }

    void addSchool(SchoolNode* school) {
        if (!head) head = school;
        else {
            SchoolNode* curr = head;
            while (curr->getNext()) curr = curr->getNext();
            curr->setNext(school);
        }
        
        // Add to graph for Dijkstra
        schoolGraph->addNode(school->getSchoolID(), 
                            (float)school->getLatitude(), 
                            (float)school->getLongitude());
        schoolCount++;
    }
    
    // NEW: Get school index by ID for graph operations
    int getSchoolIndexByID(const string& schoolID) {
        string lowerSearchID = toLowercase(schoolID);
        int index = 0;
        SchoolNode* curr = head;
        while (curr) {
            if (toLowercase(curr->getSchoolID()) == lowerSearchID) {
                return index;
            }
            curr = curr->getNext();
            index++;
        }
        return -1;
    }
    
    // NEW: Get school by index
    SchoolNode* getSchoolAt(int index) {
        int currentIndex = 0;
        SchoolNode* curr = head;
        while (curr) {
            if (currentIndex == index) {
                return curr;
            }
            curr = curr->getNext();
            currentIndex++;
        }
        return NULL;
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
        // Case-insensitive search
        string lowerSearchID = toLowercase(schoolID);
        
        SchoolNode* curr = head;
        while (curr) {
            if (toLowercase(curr->getSchoolID()) == lowerSearchID) return curr;
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

    void listSchools() {
        cout << "\n===== School List =====\n";
        SchoolNode* curr = head;
        int count = 1;
        while (curr) {
            cout << count++ << ") ID: " << curr->getSchoolID()
                 << " | Name: " << curr->getName()
                 << " | Sector: " << curr->getSector()
                 << " | Rating: " << curr->getRating()
                 << " | Coordinates: (" << curr->getLatitude() << ", " << curr->getLongitude() << ")\n";
            curr = curr->getNext();
        }
        cout << "========================\n";
    }

    void loadSchoolsFromCSV(string filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error opening file: " << filename << endl;
            return;
        }

        string line;
        getline(file, line); // Skip header

        while (getline(file, line)) {
            stringstream ss(line);
            string id, name, sector, ratingStr, subjectsStr, coordStr;

            getline(ss, id, ',');
            getline(ss, name, ',');
            getline(ss, sector, ',');
            getline(ss, ratingStr, ',');

            // Parse subjects (quoted, comma-separated)
            getline(ss, subjectsStr, ',');
            if (!subjectsStr.empty() && subjectsStr.front() == '"') {
                if (subjectsStr.back() != '"') {
                    string rest;
                    while (getline(ss, rest, ',')) {
                        subjectsStr += "," + rest;
                        if (!rest.empty() && rest.back() == '"') break;
                    }
                }
                if (subjectsStr.front() == '"' && subjectsStr.back() == '"') {
                    subjectsStr = subjectsStr.substr(1, subjectsStr.length() - 2);
                }
            }

            // Parse coordinates
            getline(ss, coordStr);
            if (!coordStr.empty() && coordStr.front() == '"' && coordStr.back() == '"') {
                coordStr = coordStr.substr(1, coordStr.length() - 2);
            }

            double latitude = 0.0, longitude = 0.0;
            stringstream coordStream(coordStr);
            string latStr, lonStr;
            if (getline(coordStream, latStr, ',') && getline(coordStream, lonStr)) {
                size_t start = latStr.find_first_not_of(" \t\r\n");
                size_t end = latStr.find_last_not_of(" \t\r\n");
                if (start != string::npos && end != string::npos) {
                    latStr = latStr.substr(start, end - start + 1);
                }
                start = lonStr.find_first_not_of(" \t\r\n");
                end = lonStr.find_last_not_of(" \t\r\n");
                if (start != string::npos && end != string::npos) {
                    lonStr = lonStr.substr(start, end - start + 1);
                }
                try { latitude = stod(latStr); } catch (...) { latitude = 0.0; }
                try { longitude = stod(lonStr); } catch (...) { longitude = 0.0; }
            }

            float rating = stof(ratingStr);
            SchoolNode* school = new SchoolNode(id, name, sector, rating, latitude, longitude);

            // Parse subjects
            stringstream s2(subjectsStr);
            string sub;
            while (getline(s2, sub, ',')) {
                size_t start = sub.find_first_not_of(" \t\r\n");
                if (start != string::npos) {
                    sub = sub.substr(start);
                }
                if (!sub.empty()) {
                    school->addSubject(sub);
                }
            }

            addSchool(school);
        }
        file.close();
    }
    
    // NEW: Load school edges for graph-based routing
    bool loadSchoolEdgesFromCSV(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error opening file: " << filename << endl;
            return false;
        }

        string line;
        getline(file, line); // Skip header

        while (getline(file, line)) {
            if (line.empty()) continue;
            
            stringstream ss(line);
            string fromSchoolID, toSchoolID, distanceStr;

            getline(ss, fromSchoolID, ',');
            getline(ss, toSchoolID, ',');
            getline(ss, distanceStr);

            int distance = 0;
            try { distance = stoi(distanceStr); } catch (...) { distance = 0; }

            int fromIndex = getSchoolIndexByID(fromSchoolID);
            int toIndex = getSchoolIndexByID(toSchoolID);

            if (fromIndex != -1 && toIndex != -1) {
                schoolGraph->addEdge(fromIndex, toIndex, distance);
            } else {
                cout << "Warning: Edge between " << fromSchoolID << " and " << toSchoolID 
                     << " skipped (school not found)\n";
            }
        }
        file.close();
        return true;
    }
    
    // NEW: Find shortest path between schools using Dijkstra
    bool findShortestPath(const string& startSchoolID, const string& endSchoolID, 
                          string* path, int& pathLength, int& totalDistance) {
        int startIndex = getSchoolIndexByID(startSchoolID);
        int endIndex = getSchoolIndexByID(endSchoolID);

        if (startIndex == -1 || endIndex == -1) {
            cout << "One or both schools not found!\n";
            return false;
        }

        schoolGraph->dijkstra(startIndex, endIndex, path, pathLength, totalDistance);
        
        if (pathLength == 0 || totalDistance == INT_MAX) {
            cout << "No path found between schools.\n";
            return false;
        }
        
        return true;
    }

    void loadDepartmentsFromCSV(string filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error opening file: " << filename << endl;
            return;
        }

        string line;
        getline(file, line); // Skip header

        while (getline(file, line)) {
            stringstream ss(line);
            string schoolID, deptName, deptID;

            getline(ss, schoolID, ',');
            getline(ss, deptName, ',');
            getline(ss, deptID);

            DepartmentNode* dept = new DepartmentNode(deptName, deptID);
            if (!addDepartmentToSchool(schoolID, dept)) {
                cout << "Warning: Could not add department " << deptName 
                     << " to school " << schoolID << endl;
                delete dept;
            }
        }
        file.close();
    }

    void loadClassesFromCSV(string filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error opening file: " << filename << endl;
            return;
        }

        string line;
        getline(file, line); // Skip header

        while (getline(file, line)) {
            stringstream ss(line);
            string schoolID, deptName, className, classID;

            getline(ss, schoolID, ',');
            getline(ss, deptName, ',');
            getline(ss, className, ',');
            getline(ss, classID);

            ClassNode* cls = new ClassNode(className, classID);
            if (!addClassToDepartment(schoolID, deptName, cls)) {
                cout << "Warning: Could not add class " << className 
                     << " to department " << deptName << " in school " << schoolID << endl;
                delete cls;
            }
        }
        file.close();
    }

    void loadStudentsFromCSV(string filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error opening file: " << filename << endl;
            return;
        }

        string line;
        getline(file, line); // Skip header

        while (getline(file, line)) {
            stringstream ss(line);
            string schoolID, deptName, className, studentName, studentID;

            getline(ss, schoolID, ',');
            getline(ss, deptName, ',');
            getline(ss, className, ',');
            getline(ss, studentName, ',');
            getline(ss, studentID);

            StudentNode* student = new StudentNode(studentName, studentID);
            if (!addStudentToClass(schoolID, deptName, className, student)) {
                cout << "Warning: Could not add student " << studentName 
                     << " to class " << className << endl;
                delete student;
            }
        }
        file.close();
    }

    SchoolNode* findNearestByCoord(double lat, double lon, double* outDistance = nullptr) {
        if (!head) return nullptr;

        SchoolNode* nearest = head;
        double minDistance = sqrt((lat - head->getLatitude()) * (lat - head->getLatitude()) +
                                  (lon - head->getLongitude()) * (lon - head->getLongitude()));

        SchoolNode* curr = head->getNext();
        while (curr) {
            double distance = sqrt((lat - curr->getLatitude()) * (lat - curr->getLatitude()) +
                                   (lon - curr->getLongitude()) * (lon - curr->getLongitude()));
            if (distance < minDistance) {
                minDistance = distance;
                nearest = curr;
            }
            curr = curr->getNext();
        }

        if (outDistance != nullptr) {
            *outDistance = minDistance;
        }

        return nearest;
    }
    
    // Getters
    int getSchoolCount() const { return schoolCount; }
    SchoolGraph* getGraph() { return schoolGraph; }
};
#endif