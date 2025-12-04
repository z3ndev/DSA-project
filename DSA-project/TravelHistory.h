//Maaz Tahir
#pragma once
#include <string>
#include <iostream>
using namespace std;

class TravelHistory {
private:
    string* stack;    // dynamic array for stack
    int capacity;
    int topIndex;

public:
    TravelHistory(int capacity = 100);
    ~TravelHistory();

    void push(const string& stopID); // add stop to history
    bool pop(string& stopID);        // remove last stop
    bool peek(string& stopID) const; // see last stop
    bool isEmpty() const;
    bool isFull() const;
    int size() const;

    void printHistory() const;
};
