//Maaz Tahir
#pragma once
#include <string>
using namespace std;


class TGraphEdge {
public:
    string to;      
    double weight;  

    TGraphEdge(const string& to = "", double weight = 0.0);
    ~TGraphEdge();
};
