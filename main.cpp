#include "data_structures.h"
#include "heap.h"
#include "util.h"
#include "stack.h"
#include "graph.h"
#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char **argv){
    //cout<<"STARTING PROGRAM";
    string sflag = argv[3];
    //cout<<sflag<<"\n";
    int flag = stoi(sflag);

    if(argc != 4 || (flag!=1 && flag!=2) || (strcmp(argv[2], "DirectedGraph") != 0 && strcmp(argv[2], "UndirectedGraph") != 0)){
        fprintf(stderr,"Usage: ./PJ3 <InputFile> <GraphType> <Flag>");
        fprintf(stderr, "%d",argc);
        return 1;
    }

    string inputFileName = argv[1];
    string graphType = argv[2];

    bool directed;
    if(graphType.compare("DirectedGraph")==0){
        directed=true;
    }
    else if(graphType.compare("UndirectedGraph")==0){
        directed=false;
    }

    bool placeFront;
    if(flag==1){
        placeFront=true;
    }
    else if(flag==2){
        placeFront=false;
    }

    ifstream in (inputFileName);
    string line;
    if(!in.is_open()){
        fprintf(stderr, "Error: cannot open file\n");
        return 1;
    }

    string firstLine="";
    int i;
    int numOfVertices;
    int numOfEdges;
    getline(in, firstLine);
    
    //cout<<firstLine<<"\n";
    i = firstLine.find(" ",1);
    //cout<<"substr: "<<firstLine.substr(0,i)<<"\n";
    numOfVertices = stoi(firstLine.substr(0,i));
    //cout<<"numOfVertices = "<<numOfVertices<<" ";
    int t = i+1;
    i = firstLine.find("\n",t);
    numOfEdges = stoi(firstLine.substr(t,i));
    //cout<<"numOfEdges = "<<numOfEdges<<"\n";

    GRAPH* graph = initializeGraph(in, numOfVertices, numOfEdges, directed, placeFront);
    //cout<<"graph initialized.\n";

    HEAP* heap = initCapacity(numOfVertices);
    setCountHeapify(false);

    STACK* stack = initStack(numOfVertices);
    //cout<<"heap & stack initialized.\n";

    //cout<<"\n\n\n";
    //printADJ(graph);
    int returnV;
    while(1){
        returnV = nextInstruction(graph, heap, stack);

        switch(returnV){
            case 0:
                fprintf(stderr, "Invalid instruction.\n");
                break;
            case 1:
                return 1;
                break;
            case 2:
                break;
        }
    }
    return 1;
}