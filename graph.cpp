#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;
#include <fstream>
#include "data_structures.h"
#include "graph.h"
#include "heap.h"
#include "stack.h"
#include <array>

bool justSinglePaired = false;
bool justSingleSourced = false;

GRAPH* initializeGraph(ifstream& in, int numOfVertices, int numOfEdges, bool directed, bool placefront){
    //cout<<"STARTING INITIALIZE GRAPH!!!\n";
    int edgeIndex;
    int u;
    int v;
    double weight;
    VERTEX* vertexU;
    VERTEX* vertexV;
    NODE* nodeUV;
    GRAPH* graph = new GRAPH();
    graph->ADJ = new NODE**[numOfVertices+1];
    for(int j = 1; j<=numOfVertices; j++){
        graph->ADJ[j] = new NODE*[numOfEdges+1];
        /*for(int k = 0; k<=numOfEdges; k++){
            graph->ADJ[j][k] = NULL;
        }*/
    }
    //cout<<"declared adjacency list \n";
    graph-> V = new VERTEX*[numOfVertices+1];
    //cout<<"declared vertex list \n";
    graph->numOfEdges=numOfEdges;
    graph->numOfVertices=numOfVertices;

    string line;
    int start;
    int end;
    while (std::getline(in, line)) {
        //cout<<"Line read: "<<line<<"\n";
        start=0;
        end = 0;

        start = line.find_first_of("123456789", 0);
        end = line.find(" ", start);
        //cout<<"Edgeindex: "<<line.substr(start, end-start)<<"\n";
        edgeIndex = stoi(line.substr(start, end-start));

        start= line.find_first_of("123456789", end);
        end = line.find(" ", start);
        //cout<<"U: "<<line.substr(start, end-start)<<"\n";
        u = stoi(line.substr(start,end-start));
        
        start= line.find_first_of("123456789", end);
        end = line.find(" ", start);
        //cout<<"V: "<<line.substr(start, end-start)<<"\n";
        v=stoi(line.substr(start, end-start));
        
        start= line.find_first_of("123456789", end);
        end = line.find("\n", start);
        //cout<<line.substr(start,end-start)<<"\n";
        weight=stod(line.substr(start,end-start));
        
        //cout<<"creating vertex "<<u<<".\n";
        vertexU = new VERTEX;
        vertexU -> index = u;

        //cout<<"creating vertex "<<v<<".\n";
        vertexV = new VERTEX;
        vertexV->index = v;

        //cout<<"creating edge "<<u<<" - "<<v<<": "<<weight<<"\n";
        nodeUV = new NODE;
        nodeUV->index = edgeIndex;
        nodeUV->u = vertexU;
        nodeUV->v = vertexV;
        nodeUV->weight = weight;

        if(graph->V[u]==NULL){
            graph->V[u] = vertexU;
            //cout<<"added to array: vertex "<<u<<".\n";
        }
        if(graph->V[v]==NULL){
            graph->V[v] = vertexV;
            //cout<<"added to array: vertex "<<v<<".\n";
        }

        //cout<<"EDGE "<<nodeUV->index<<"-- vertex u: "<<nodeUV->u->index<<" node v: "<<nodeUV->v->index<<" weight: "<<nodeUV->weight<<"\n";
        //cout<<"updating adjacency list\n";
        if(placefront){
            //cout<<"placefront true\n";
            //cout<<"Vertex "<<u<<"\n";
            int index=1; 
            while(graph->ADJ[u][index]!=NULL){
                //cout<<"("<<u<<","<<index<<") is populated. moving on.\n";
                index ++;
            }
            if(graph->ADJ[u][index-1]!=NULL){
                while(index>1){
                    graph->ADJ[u][index] = graph->ADJ[u][index-1];
                    //cout<<"moved edge "<<graph->ADJ[u][index]->index<<" back to ("<<u<<","<<index<<")\n";
                    index--;
                }
            }
            //cout<<"("<<u<<",1) is free.\n";
            graph->ADJ[u][1] = nodeUV;
            if(!directed){
                //cout<<"undirected. Adding corresponding edge. ";
                NODE* nodeVU = new NODE();
                nodeVU->weight = weight;
                nodeVU->u = vertexV;
                nodeVU->v = vertexU;
                //cout<<v<<" - "<<u<<": "<<weight<<"\n";
                index=1; 
                while(graph->ADJ[v][index]!=NULL){
                    //cout<<"("<<v<<","<<index<<") is populated. moving on.\n";
                    index ++;
                }
                while(index>0){
                    graph->ADJ[v][index] = graph->ADJ[v][index-1];
                    index--;
                }
                graph->ADJ[v][1] = nodeVU;
            }
        }
        else{
            //cout<<"placefront false\n";
            int index=1; 
            //cout<<"Vertex "<<u<<"\n";
            while(graph->ADJ[u][index]!=NULL){
                //cout<<"("<<u<<","<<index<<") is populated. moving on.\n";
                index ++;
            }
            graph->ADJ[u][index] = nodeUV;
            //cout<<"Inserted edge "<<graph->ADJ[u][index]->u->key<<"-"<<graph->ADJ[u][index]->v->key<<" at index ("<<u<<","<<index<<")\n";

            if(!directed){
                //cout<<"undirected. Adding corresponding edge. ";
                NODE* nodeVU = new NODE();
                nodeVU->weight = weight;
                nodeVU->u = vertexV;
                nodeVU->v = vertexU;
                //cout<<v<<" - "<<u<<": "<<weight<<"\n";
                index=1;
                while(graph->ADJ[v][index]!=NULL){
                    //cout<<"("<<v<<","<<index<<") is populated. moving on.\n";
                    index++;
                }
                graph->ADJ[v][index] = nodeVU;
            }
                
        }
        //cout<<"finished with edge "<<edgeIndex<<"\n\n\n";
    }
    in.close();
    return graph;
}

void printADJ(GRAPH* graph){
    for(int i = 1; i<=(graph->numOfVertices); i++){
        fprintf(stdout, "ADJ[%d]:",i);
        for(int j=1;j<=(graph->numOfEdges); j++){
            if(graph->ADJ[i][j]!=NULL){
                fprintf(stdout, "-->[%.0d %.0d: %4.2lf]", (graph->ADJ[i][j]->u->index), (graph->ADJ[i][j]->v->index), (graph->ADJ[i][j]->weight));
            }
        }
        fprintf(stdout, "\n");
    }
}

void initializeSingleSource(GRAPH* graph, VERTEX* source){
    for(int i = 1; i <= graph->numOfVertices; i++){
        if(graph->V[i]!=NULL){
            graph->V[i]->key = __DBL_MAX__;
            graph->V[i]->predecessor = NULL;
            graph->V[i]->color = "white";
            graph->V[i]->onSinglePairPath = false;
            graph->V[i]->isDestination = false;
        }
    }
    if(graph->V[source->index]!=NULL){
        graph->V[source->index]->key = 0;
    }
}

bool relax(NODE* edgeUV, VERTEX* u, VERTEX* v){
    if(v->key > (u->key +edgeUV->weight)){
        v->key = (u->key +edgeUV->weight);
        v->predecessor = u;
        return true;
    }
    return false;
}

NODE* getEdge(GRAPH* graph, VERTEX* u, VERTEX* v){
    for(int i=1; i<=graph->numOfEdges; i++){
        if(graph->ADJ[u->index][i]->v->index == v->index){
            return graph-> ADJ[u->index][i];
        }
    }
    return NULL;
}

void singleSource(GRAPH* graph, VERTEX* source){
    initializeSingleSource(graph, source);
    //cout<<"successfully initialized singlesource.\n";
    graph->stack = initStack(graph->numOfVertices);
    //cout<<"successfully initialized stack.\n";
    HEAP* heap = initCapacity(graph->numOfVertices);
    //cout<<"successfully initialized heap.\n";

    for(int i = 1; i<=graph->numOfVertices; i++){
        if(graph->V[i]!=NULL){
            insert(heap, graph->V[i]);
            graph->V[i]->position = i-1;
            //cout<<"successfully inserted vertex"<<graph->V[i]->index<<"onto heap.\n";
        }
    }
    VERTEX* minVertex;
    VERTEX* adjacentVertex;
    while(heap->size>0){
        minVertex = extractMin(heap);
        //cout<<"printing heap...\n";
        //printHeap(heap);
        //cout<<"MIN VERTEX EXTRACTED: "<<minVertex->index<<" - "<<minVertex->key<<"\n";
        for(int i=1; i<=graph->numOfEdges;i++){ 
            if(graph->ADJ[minVertex->index][i] != NULL){
                adjacentVertex = graph->ADJ[minVertex->index][i]->v;
                if(adjacentVertex->color.compare("black")!=0){
                    relax(graph->ADJ[minVertex->index][i], graph->V[minVertex->index], graph->V[adjacentVertex->index]);
                    //cout<<"relaxed "<<graph->V[adjacentVertex->index]->index<<" to "<<graph->V[adjacentVertex->index]->key<<"\n";
                    buildMinHeap(heap);
                }
            }
        }
        minVertex->color = "black";
        push(graph->stack, minVertex);
    }
    justSinglePaired = false;
    justSingleSourced = true;
    //cout<<"done with singlesource\n";
}

void singlePair(GRAPH* graph, VERTEX* source, VERTEX* destination){
    singleSource(graph, source);
    if(destination->color.compare("black")==0 && destination->predecessor!=NULL && destination->key!=__DBL_MAX__){
        VERTEX* v = destination;
        while(v!=NULL){
            v->onSinglePairPath = true;
            v = v->predecessor;
        }

        for(int i = 1; i<=graph->numOfVertices;i++){
            if(!graph->V[i]->onSinglePairPath){
                graph->V[i]->color = "white";
                graph->V[i]->predecessor = NULL;
                graph->V[i]->key = __DBL_MAX__;
                if(graph->V[i]->index != destination->index){
                    graph->V[i]->isDestination = false;
                }
            }
        }
        destination->color = "black";
    }
    justSinglePaired=true;
    justSingleSourced = false;
    destination->isDestination = true;
}

void printLength(GRAPH* graph, VERTEX* source, VERTEX* destination){
    if(graph->V[source->index]->key != 0 || graph->stack->count == 0){
        fprintf(stderr, "Invalid instruction.\n");
        return;
    }
    if(destination->key == __DBL_MAX__ || destination->predecessor == NULL){
        fprintf(stdout, "There is no path from %d to %d.\n", source->index, destination->index);
        return;
    }
    fprintf(stdout, "The length of the shortest path from %d to %d is:     %.2f\n",source->index, destination->index, destination->key);
}

void printPath(GRAPH* graph, VERTEX* source, VERTEX* destination){
    //cout<<"Just singlepaired: "<<justSinglePaired<<"\n";
    //cout<<"Just singlesourced: "<<justSingleSourced<<"\n";
    if(!justSinglePaired && !justSingleSourced){
        fprintf(stderr, "Invalid instruction.\n");
        return;
    }
    if(graph->V[source->index]->color.compare("")==0 || graph->V[source->index]->key != 0 || graph->stack->count == 0){
        fprintf(stderr, "Invalid instruction.\n");
        return;
    }
    if(justSinglePaired && !justSingleSourced){
        if(graph->V[destination->index]->isDestination==false){
            fprintf(stderr, "Invalid instruction.\n");
            return;
        }
    }
    
    if(destination->key == __DBL_MAX__ || destination->predecessor == NULL){
        fprintf(stdout, "There is no path from %d to %d.\n", source->index, destination->index);
        return;
    }
    STACK* s = initStack(graph->numOfVertices);
    VERTEX* v = destination;
    while(v != NULL){
        push(s, v);
        v = v->predecessor;
    }
    fprintf(stdout,"The shortest path from %d to %d is:\n", source->index, destination->index);
    v = pop(s);
    if(v->index == source->index){
        fprintf(stdout, "[%d:%8.2lf]", v->index, v->key);
        while(s->count>0){
            v = pop(s);
            fprintf(stdout, "-->[%d:%8.2lf]", v->index, v->key);
        }
        fprintf(stdout, ".\n");
    }
    else{
        fprintf(stdout, "There is no path from %d to %d.", source->index, destination->index);
        return;
    }
}