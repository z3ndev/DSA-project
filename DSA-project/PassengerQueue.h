//Maaz Tahir
#pragma once
#include "TPassenger.h"
#include <iostream>
using namespace std;

class PassengerQueue {
private:
    TPassenger* queue;   // array of passengers
    int capacity;        // max size
    int front;           // index of first element
    int rear;            // index of last element
    int count;           // current number of elements

public:
    PassengerQueue(int capacity = 100);
    ~PassengerQueue();

    // Queue operations
    bool enqueue(const TPassenger& passenger); // add passenger
    bool dequeue(TPassenger& passenger);       // remove passenger
    bool isEmpty() const;
    bool isFull() const;
    int size() const;

    // Display queue contents
    void printQueue() const;
};
