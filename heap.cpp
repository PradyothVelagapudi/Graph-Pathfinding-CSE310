#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <string>
#include "data_structures.h"
#include "heap.h"

int heapifyCount;
bool countHeapify;
bool justOped=false;

void setHeapifyCount(){
    heapifyCount = 0;
}

void setCountHeapify(bool b){
    countHeapify=b;
}

void heapify(HEAP* heap, int i) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int smallest = i;

    if (left < heap->size && heap->A[left]->key < heap->A[smallest]->key) {
        smallest = left;
    }
    if (right < heap->size && heap->A[right]->key < heap->A[smallest]->key) {
        smallest = right;
    }

    if (smallest != i) {
        ELEMENT* temp = heap->A[i];
        heap->A[i] = heap->A[smallest];
        heap->A[smallest] = temp;
        heap->A[i]->position = i;
        heap->A[smallest]->position = smallest;
        heapify(heap, smallest);
    }

    if(countHeapify){
        heapifyCount++;
    }
    //std::cout<<"\nHeapifying!\n";
}

void buildMinHeap(HEAP* heap) {
    heapifyCount=0;
    for (int i = (heap->size / 2) - 1; i >= 0; i--) {
        heapify(heap, i);
    }

    for(int i = 0; i<heap->size; i++){
        heap->A[i]->position = i;
    }
    justOped=true;
}

HEAP* initCapacity(int capacity){
    HEAP *heap = new HEAP();
    heap->capacity = capacity;
    heap->A = new ELEMENT*[capacity];
    heap->size = 0;
    return heap;
}

void printHeap(HEAP* heap){
    if (heap == NULL || heap->capacity == 0){
        fprintf(stderr, "Error: heap is NULL\n");
        return;
    }
    if(countHeapify && heap->size>0 && justOped){
        fprintf(stdout, "Number of Heapify calls: %d\n", heapifyCount);
        justOped=false;
    }
    //std::cout<<"Heap capacity: "<<heap->capacity;
    //fprintf(stdout, "%d\n", heap->size);
    ELEMENT* e;
    for(int i = 0; i<heap->size; i++){
        e = heap->A[i];
        fprintf(stdout, "%d - %.0e\n",e->index, e->key);
    }
    return;
}

void writeHeap(HEAP* heap, FILE* file){
    if (heap == NULL || heap->capacity == 0){
        fprintf(stderr, "Error: heap is NULL\n");
        return;
    }
    if(!file){
        fprintf(stderr, "Error: cannot open file\n");
        return;
    }
    if(countHeapify && heap->size>0 && justOped){
        fprintf(file, "Number of Heapify calls: %d\n", heapifyCount);
        justOped=false;
    }
    fprintf(file, "%d\n", heap->size);
    ELEMENT* e;
    for(int i = 0; i<heap->size; i++){
        e = heap->A[i];
        fprintf(file, "%f\n",e->key);
    }
 
}

void read(HEAP* heap, std::string& filename){
    if (heap == NULL || heap->capacity == 0){
        fprintf(stderr, "Error: heap is NULL\n");
        return;
    }
    std::ifstream in (filename);
    std::string line;
    bool sizeSet = false;
    int size;

    if(!in.is_open()){
        fprintf(stderr, "Error: cannot open file\n");
        return;
    }
    ELEMENT* e;
    double key;
    int index = 0;
    while (std::getline(in, line)) {
        //std::cout<<"entering main loop\n";
        //std::cout<<"First line: "<<line<<"\n";
        int pos = 0;
        std::string token; //START HERE
        if(line.find(" ",0)!=std::string::npos || line.find("\t",0)!=std::string::npos){
            //std::cout<<"additional delimiter found\n";
            while((pos = line.find_first_of(" \t\n", pos)) != -1){
                //std::cout<<"Entering inner loop\n";
                //std::cout<<pos<<" is location of delimiter"<<line[pos]<<"\n";
                token = line.substr(0, pos);
                //std::cout<<"Token: "<<token<<"\n";
                if (token!="") {
                    //std::cout<<"tokenExists\n";
                    if (!sizeSet) {
                        size = stoi(token);
                        //std::cout<<token<<" size\n";
                        if(size > heap->capacity){
                            fprintf(stderr, "Error: too many elements\n");
                            //std::cout<<heap->capacity;
                            return;
                        }
                        sizeSet = true;
                    }
                    else{
                        key = stod(token);
                        e = new ELEMENT();
                        e->key = key;
                        heap->A[index]=e;
                        index++;
                        //std::cout<<"Index: "<<index<<"\n";
                        //std::cout<<key<<"\n";
                    }
                }
                pos++;
                line = line.substr(pos);
                //std::cout<<"Remaining in line: "<<line<<"\n";
                pos = 0;
            }
            if(!line.empty()){
                key = stod(line);
                e = new ELEMENT();
                e->key = key;
                heap->A[index]=e;
                index++;
                //std::cout<<"Index: "<<index<<"\n";
                //std::cout<<key<<"\n";
            }
        }
        else{
            //std::cout<<"No additional delimiter found\n";
            if(line!=""){
                //std::cout<<"Line exists\n";
                if (!sizeSet) {
                    size = stoi(line);
                    //std::cout<<line<<" size\n";
                    if(size > heap->capacity){
                        fprintf(stderr, "Error: too many elements\n");
                        return;
                    }
                    sizeSet = true;
                }
                else{
                    key = stod(line);
                    e = new ELEMENT();
                    e->key = key;
                    heap->A[index]=e;
                    index++;
                    //std::cout<<"Index: "<<index<<"\n";
                    //std::cout<<key<<"\n";
                }
            }
        }
    }
    heap->size= index;
    buildMinHeap(heap);
    in.close();
}

void insert(HEAP* heap, ELEMENT* e){
    if (heap == NULL || heap->capacity == 0){
        fprintf(stderr, "Error: heap is NULL\n");
        return;
    }
    if (heap->size == heap->capacity){
        fprintf(stderr, "Error: heap is full\n");
        return;
    }
    int currentIndex = heap->size;
    heap->A[currentIndex] = e;
    heap->size++;

    while (currentIndex > 0) {
        int parentIndex = (currentIndex - 1) / 2;

        if (heap->A[currentIndex]->key < heap->A[parentIndex]->key) {
            // Swap the current element with its parent
            std::swap(heap->A[currentIndex], heap->A[parentIndex]);
            currentIndex = parentIndex;
        } else {
            // The min-heap property is satisfied
            break;
        }
    }
}

ELEMENT* extractMin(HEAP* heap){
    if (heap == NULL || heap->capacity == 0){
        fprintf(stderr, "Error: heap is NULL\n");
        return NULL;
    }
    if (heap->size == 0){
        fprintf(stderr, "Error: heap is empty\n");
        return NULL;
    }
    ELEMENT* min = heap->A[0];
    heap->A[0] = heap->A[heap->size -1];
    heap->A[heap->size-1] = NULL;
    heap->size--;
    buildMinHeap(heap);

    return min;
}

void decreaseKey(HEAP* heap, int position, int newKey){
    if (heap == NULL || heap->capacity == 0){
        fprintf(stderr, "Error: heap is NULL\n");
        return;
    }
    if (heap->size == 0){
        fprintf(stderr, "Error: heap is empty\n");
        return;
    }
    if(position-1 > heap->size-1 || position < 0 || newKey >= heap->A[position-1]->key){
        fprintf(stderr, "Error: invalid call to DecreaseKey\n");
        return;
    }
    heap->A[position-1]->key = newKey;
    int currentIndex = position - 1;
    if(countHeapify){
        countHeapify=false;
        while (currentIndex > 0) {
        int parentIndex = (currentIndex - 1) / 2;

        if (heap->A[currentIndex]->key < heap->A[parentIndex]->key) {
            // Swap the current element with its parent
            std::swap(heap->A[currentIndex], heap->A[parentIndex]);
            currentIndex = parentIndex;
        } else {
            // The min-heap property is satisfied
            break;
        }
    }
        countHeapify=true;
    }
    else{
        while (currentIndex > 0) {
        int parentIndex = (currentIndex - 1) / 2;

        if (heap->A[currentIndex]->key < heap->A[parentIndex]->key) {
            // Swap the current element with its parent
            std::swap(heap->A[currentIndex], heap->A[parentIndex]);
            currentIndex = parentIndex;
        } else {
            // The min-heap property is satisfied
            break;
        }
    }
    }
}