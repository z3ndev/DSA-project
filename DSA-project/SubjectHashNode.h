// Abdullah Noor
#ifndef SUBJECTHASHNODE_H
#define SUBJECTHASHNODE_H

#include <iostream>
using namespace std;

class SubjectHashNode {
private:
    string subject, schoolID;
    SubjectHashNode* next;

public:
    SubjectHashNode(string s, string id) :subject(s), schoolID(id), next(NULL) {}

    string getSubject() { return subject; }
    string getSchoolID() { return schoolID; }
    SubjectHashNode* getNext() { return next; }

    void setNext(SubjectHashNode* node) { next = node; }
};
#endif