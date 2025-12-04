//Maaz Tahir
#include "PassengerQueue.h"

PassengerQueue::PassengerQueue(int capacity)
{
    this->capacity = capacity;
    queue = new TPassenger[capacity];
    front = 0;
    rear = -1;
    count = 0;
}

PassengerQueue::~PassengerQueue()
{
    delete[] queue;
}

bool PassengerQueue::enqueue(const TPassenger& passenger) 
{
    if (isFull())
        return false;

    rear = (rear + 1) % capacity;
    queue[rear] = passenger; // copy passenger by value
    count++;
    return true;
}

bool PassengerQueue::dequeue(TPassenger& passenger) 
{
    if (isEmpty())
        return false;

    passenger = queue[front]; // copy out
    front = (front + 1) % capacity;
    count--;
    return true;
}

bool PassengerQueue::isEmpty() const 
{
    return count == 0;
}

bool PassengerQueue::isFull() const 
{
    return count == capacity;
}

int PassengerQueue::size() const 
{
    return count;
}

void PassengerQueue::printQueue() const
{
    cout << "Passenger Queue (size=" << count << "):\n";
    for (int i = 0; i < count; i++) {
        int idx = (front + i) % capacity;
        queue[idx].print();
    }
}
