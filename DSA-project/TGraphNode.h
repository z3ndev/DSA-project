//Maaz Tahir
#pragma once
#include <string>
using namespace std;


class TGraphNode {
public:
    string id;        
    string name;     
    double latitude;  
    double longitude; 

    TGraphNode(const string& id = "",
        const string& name = "",
        double lat = 0.0,
        double lon = 0.0);

    ~TGraphNode();
    string toString() const;
};
