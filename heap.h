#ifndef _heap_h
#define _heap_h 1

#include "data_structures.h"
#include <stdio.h>
#include <fstream>
#include <string>
void setCountHeapify(bool);
void setHeapifyCount();
void buildMinHeap(HEAP*);
void heapify(HEAP*, int);

HEAP* initCapacity(int);
void printHeap(HEAP*);
void writeHeap(HEAP*, FILE*);
void read(HEAP*, std::string&);
void insert(HEAP*, ELEMENT*);
ELEMENT* extractMin(HEAP*);
void decreaseKey(HEAP*, int, int);

#endif
