//Maaz Tahir
#include "TGraphNode.h"

TGraphNode::TGraphNode(const string& id,const string& name,double lat,double lon): id(id), name(name), latitude(lat), longitude(lon){}

TGraphNode::~TGraphNode() {}

string TGraphNode::toString() const
{
    // Simple debug string
    return id + " | " + name + " | (" +
        to_string(latitude) + ", " +
        to_string(longitude) + ")";
}
