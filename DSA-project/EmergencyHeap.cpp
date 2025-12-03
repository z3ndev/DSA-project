#include "EmergencyHeap.h"

// Constructor
EmergencyHeap::EmergencyHeap() {
    size = 0;
}

// Restore upward heap property
void EmergencyHeap::heapifyUp(int index) {
    if (index == 0) return;

    int parent = (index - 1) / 2;

    // Compare emergency beds
    if (heap[index]->emergencyBeds > heap[parent]->emergencyBeds) {
        Hospital* temp = heap[index];
        heap[index] = heap[parent];
        heap[parent] = temp;

        heapifyUp(parent);
    }
}

// Restore downward heap property
void EmergencyHeap::heapifyDown(int index) {
    int left = index * 2 + 1;
    int right = index * 2 + 2;
    int largest = index;

    if (left < size && heap[left]->emergencyBeds > heap[largest]->emergencyBeds)
        largest = left;

    if (right < size && heap[right]->emergencyBeds > heap[largest]->emergencyBeds)
        largest = right;

    if (largest != index) {
        Hospital* temp = heap[index];
        heap[index] = heap[largest];
        heap[largest] = temp;

        heapifyDown(largest);
    }
}

// Insert hospital pointer into heap
void EmergencyHeap::insert(Hospital* h) {
    if (size >= MAX_HEAP_SIZE) return;

    heap[size] = h;
    heapifyUp(size);
    size++;
}

// Return the max (most emergency beds)
Hospital* EmergencyHeap::getMax() {
    if (size == 0) return nullptr;
    return heap[0];
}

// Remove the max and re-heapify
Hospital* EmergencyHeap::extractMax() {
    if (size == 0) return nullptr;

    Hospital* top = heap[0];

    heap[0] = heap[size - 1];
    size--;

    heapifyDown(0);

    return top;
}

int EmergencyHeap::getSize() const {
    return size;
}
