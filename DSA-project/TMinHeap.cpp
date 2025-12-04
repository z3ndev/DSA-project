//Maaz Tahir
#include "TMinHeap.h"

TMinHeap::TMinHeap(int capacity)
{
    this->capacity = capacity;
    size = 0;
    ids = new string[capacity];
    dist = new double[capacity];
}

TMinHeap::~TMinHeap()
{
    delete[] ids;
    delete[] dist;
}

void TMinHeap::swap(int i, int j)
{
    string tempID = ids[i];
    ids[i] = ids[j];
    ids[j] = tempID;

    double tempD = dist[i];
    dist[i] = dist[j];
    dist[j] = tempD;
}

void TMinHeap::heapifyUp(int i)
{
    while (i != 0 && dist[parent(i)] > dist[i]) {
        swap(i, parent(i));
        i = parent(i);
    }
}

void TMinHeap::heapifyDown(int i)
{
    int smallest = i;
    int l = left(i);
    int r = right(i);

    if (l < size && dist[l] < dist[smallest])
        smallest = l;

    if (r < size && dist[r] < dist[smallest])
        smallest = r;

    if (smallest != i) {
        swap(i, smallest);
        heapifyDown(smallest);
    }
}

void TMinHeap::insert(const string& id, double d)
{
    if (size == capacity)
        return; // Ignore if full

    ids[size] = id;
    dist[size] = d;
    heapifyUp(size);
    size++;
}

bool TMinHeap::isEmpty() const
{
    return size == 0;
}

void TMinHeap::extractMin(string& id, double& d)
{
    if (size == 0) {
        id = "";
        d = -1;
        return;
    }

    id = ids[0];
    d = dist[0];

    ids[0] = ids[size - 1];
    dist[0] = dist[size - 1];
    size--;

    heapifyDown(0);
}
