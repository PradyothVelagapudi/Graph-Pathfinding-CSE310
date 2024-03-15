#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include "data_structures.h"
#include "graph.h"
#include "util.h"

int nextInstruction(GRAPH* graph, HEAP* heap, STACK* stack)
{
    char cmd[100];

    fscanf(stdin, "%s", cmd);

    string command = cmd;

    char sour[100];
    char dest[100];

    if (command.compare("Stop")==0) return 1;
    else if (command.compare("PrintADJ")==0) {
        printADJ(graph);
        return 2;
    }
    else if (command.compare("SinglePair")==0){
        fscanf(stdin, "%s", sour);
        fscanf(stdin, "%s", dest);
        int sourceIndex = stoi(sour);
        int destinationIndex = stoi(dest);

        VERTEX* source = graph->V[sourceIndex];
        VERTEX* destination = graph->V[destinationIndex];

        singlePair(graph, source, destination);
        return 3;
    }
    else if (command.compare("SingleSource")==0){
        fscanf(stdin, "%s", sour);
        int sourceIndex = stoi(sour);
        VERTEX* source = graph->V[sourceIndex];
        singleSource(graph, source);
        return 4;
    }
    else if (command.compare("PrintLength")==0){
        fscanf(stdin, "%s", sour);
        fscanf(stdin, "%s", dest);
        int sourceIndex = stoi(sour);
        int destinationIndex = stoi(dest);
        VERTEX* source = graph->V[sourceIndex];
        VERTEX* destination = graph->V[destinationIndex];
        printLength(graph, source, destination);
        return 5;
    }
    else if (command.compare("PrintPath")==0){
        fscanf(stdin, "%s", sour);
        fscanf(stdin, "%s", dest);
        int sourceIndex = stoi(sour);
        int destinationIndex = stoi(dest);
        VERTEX* source = graph->V[sourceIndex];
        VERTEX* destination = graph->V[destinationIndex];
        printPath(graph, source, destination);
        return 6;
    }
    else return 0;
}