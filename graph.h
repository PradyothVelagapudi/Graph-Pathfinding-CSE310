#ifndef _graph_h
#define _graph_h 1

#include "data_structures.h"
#include <string.h>

GRAPH* initializeGraph(ifstream&, int, int, bool, bool);
void printADJ(GRAPH*);
NODE* getEdge(GRAPH*, VERTEX*, VERTEX*);
void initializeSingleSource(GRAPH*, VERTEX*);
bool relax(NODE*, VERTEX*, VERTEX*);
void singleSource(GRAPH*, VERTEX*);
void singlePair(GRAPH*, VERTEX*, VERTEX*);
void printLength(GRAPH*, VERTEX*, VERTEX*);
void printPath(GRAPH*, VERTEX*, VERTEX*);

#endif