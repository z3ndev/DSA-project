//Abdullah Noor
#ifndef GRAPHEDGE_H
#define GRAPHEDGE_H
class GraphEdge {
private:
    int to, weight;
    GraphEdge* next;
public:
    GraphEdge(int t, int w);
    ~GraphEdge();
    int getTo();
    int getWeight();
    GraphEdge* getNext();
    void setNext(GraphEdge* edge);
};
#endif