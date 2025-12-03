#ifndef EMERGENCYHEAP_H
#define EMERGENCYHEAP_H

#include "Hospital.h"

class EmergencyHeap {
private:
    static const int MAX_HEAP_SIZE = 200;   // Adjust as needed

    Hospital* heap[MAX_HEAP_SIZE];
    int size;

    void heapifyUp(int index);
    void heapifyDown(int index);

public:
    EmergencyHeap();
    void insert(Hospital* h);
    Hospital* getMax();      // See the hospital with most emergency beds
    Hospital* extractMax();  // Remove the top hospital
    int getSize() const;
};

#endif
