#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <string>
#include "data_structures.h"
#include "stack.h"

STACK* initStack(int n){
    STACK *stack = new STACK();
    stack->stack = new VERTEX*[n];
    stack->capacity = n;
    stack->count = 0;
    return stack;
}

void push(STACK* s, VERTEX* n){
    s->stack[s->count] = n;
    s->count ++;
}

VERTEX* pop(STACK* s){
    if(s->count==0){
        return NULL;
    }

    VERTEX* n = s->stack[s->count-1];
    s->stack[s->count-1] = NULL;
    s->count --;
    return n;
}

int getSize(STACK* s){
    if(s->count==0){
        for(int i = 0; i<s->capacity; i++){
            if(s->stack[i] != NULL){
                s->count++;
            }
        }
    }
    return s->count;
}
