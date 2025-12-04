//Maaz Tahir
#include "TravelHistory.h"

TravelHistory::TravelHistory(int capacity) 
{
    this->capacity = capacity;
    stack = new string[capacity];
    topIndex = -1;
}

TravelHistory::~TravelHistory() 
{
    delete[] stack;
}

void TravelHistory::push(const string& stopID) {
    if (!isFull()) {
        if (topIndex >= 0 && stack[topIndex] == stopID)
        {
            return;
        }
        stack[++topIndex] = stopID;
    }
    else {
        cout << "Travel history full, cannot push " << stopID << endl;
    }
}

bool TravelHistory::pop(string& stopID)
{
    if (isEmpty()) 
        return false;
    stopID = stack[topIndex--];
    return true;
}

bool TravelHistory::peek(string& stopID) const 
{
    if (isEmpty()) 
        return false;
    stopID = stack[topIndex];
    return true;
}

bool TravelHistory::isEmpty() const
{
    return topIndex == -1;
}

bool TravelHistory::isFull() const 
{
    return topIndex + 1 == capacity;
}

int TravelHistory::size() const
{
    return topIndex + 1;
}

void TravelHistory::printHistory() const {
    cout << "Travel History (most recent on top):\n";
    for (int i = topIndex; i >= 0; i--) {
        cout << stack[i] << (i == 0 ? "" : " -> ");
    }
    cout << "\n";
}
