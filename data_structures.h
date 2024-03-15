#ifndef _data_structures_h
#define _data_structures_h 1

#include <string> 
using namespace std;

typedef struct TAG_VERTEX{
    int index;
    string color;
    double key;
    TAG_VERTEX* predecessor;
    int position;
    bool onSinglePairPath;
    bool isDestination;
}VERTEX;
typedef VERTEX ELEMENT;

typedef struct TAG_NODE{

    int index;
    VERTEX* u;
    VERTEX* v;
    double weight;
}NODE;

typedef struct TAG_HEAP {
    int capacity;
    int size;
    ELEMENT** A;
}HEAP;

typedef struct TAG_STACK{
    int count;
    VERTEX** stack;
    int capacity;
}STACK;

typedef struct TAG_GRAPH{
    int numOfVertices;
    int numOfEdges;
    STACK* stack;
    NODE*** ADJ;
    VERTEX** V;
}GRAPH;

#endif