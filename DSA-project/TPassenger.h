//Maaz Tahir
#pragma once
#include <string>
using namespace std;

class TPassenger {
private:
    string name;
    string cnic;
    string destinationStop;
    int ticketNo;

public:
    // Constructors
    TPassenger();
    TPassenger(const string& name, const string& cnic,const string& dest, int ticketNo);

    // Setters
    void setName(const string& n);
    void setCNIC(const string& c);
    void setDestination(const string& d);
    void setTicketNo(int t);

    // Getters
    string getName() const;
    string getCNIC() const;
    string getDestination() const;
    int getTicketNo() const;

    // Display
    void print() const;
};
