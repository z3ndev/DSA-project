// Abdullah Noor
#ifndef SCHOOLMINHEAP_H
#define SCHOOLMINHEAP_H

#include <iostream>
using namespace std;
#include "SchoolNode.h"

class SchoolMinHeap {
private:
    SchoolNode** heap;
    int size, capacity;

    void swap(int i, int j) {
        SchoolNode* temp = heap[i];
        heap[i] = heap[j];
        heap[j] = temp;
    }

    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap[index]->getRating() < heap[parent]->getRating()) {
                swap(index, parent);
                index = parent;
            }
            else break;
        }
    }

    void heapifyDown(int index) {
        while (true) {
            int leftChild = 2 * index + 1, rightChild = 2 * index + 2;
            int smallest = index;
            if (leftChild < size && heap[leftChild]->getRating() < heap[smallest]->getRating())
                smallest = leftChild;
            if (rightChild < size && heap[rightChild]->getRating() < heap[smallest]->getRating())
                smallest = rightChild;
            if (smallest != index) {
                swap(index, smallest);
                index = smallest;
            }
            else break;
        }
    }

public:
    SchoolMinHeap(int cap = 100) :size(0), capacity(cap) {
        heap = new SchoolNode * [capacity];
    }

    ~SchoolMinHeap() {
        delete[] heap;
    }

    void insert(SchoolNode* school) {
        if (size >= capacity) {
            capacity *= 2;
            SchoolNode** newHeap = new SchoolNode * [capacity];
            for (int i = 0; i < size; i++)
                newHeap[i] = heap[i];
            delete[] heap;
            heap = newHeap; 
        }

        heap[size] = school;
        heapifyUp(size);
        size++;
    }

    SchoolNode* extractMin() {
        if (size == 0) return NULL;

        SchoolNode* min = heap[0];
        heap[0] = heap[size - 1];
        size--;
        heapifyDown(0);

        return min;
    }

    bool isEmpty() { return size == 0; }
    int getSize() { return size; }

    void display() {
        cout << "School Min-Heap (by rating):\n";
        for (int i = 0; i < size; i++) {
            cout << "  " << heap[i]->getSchoolID() << " - "
                << heap[i]->getName() << " - Rating: "
                << heap[i]->getRating() << endl;
        }
    }
};

#endif