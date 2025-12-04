//Maaz Tahir
#include "TPassenger.h"
#include <iostream>
using namespace std;

// Default Constructor
TPassenger::TPassenger() 
{
    name = "";
    cnic = "";
    destinationStop = "";
    ticketNo = 0;
}

// Parameterized Constructor
TPassenger::TPassenger(const string& name,const string& cnic,const string& dest,int ticketNo)
{
    this->name = name;
    this->cnic = cnic;
    this->destinationStop = dest;
    this->ticketNo = ticketNo;
}

// Setters
void TPassenger::setName(const string& n)
{
    name = n; 
}
void TPassenger::setCNIC(const string& c) 
{
    cnic = c; 
}
void TPassenger::setDestination(const string& d)
{
    destinationStop = d;
}
void TPassenger::setTicketNo(int t) 
{
    ticketNo = t;
}

// Getters
string TPassenger::getName() const
{
    return name; 
}
string TPassenger::getCNIC() const 
{
    return cnic;
}
string TPassenger::getDestination() const
{
    return destinationStop;
}
int TPassenger::getTicketNo() const 
{
    return ticketNo;
}

// Print
void TPassenger::print() const 
{
    cout << "Passenger: " << name << " | CNIC: " << cnic
        << " | Destination: " << destinationStop
        << " | Ticket#: " << ticketNo << endl;
}
