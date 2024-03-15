#ifndef _stack_h
#define _stack_h 1

#include "data_structures.h"
#include <string.h>

STACK* initStack(int);
void push(STACK*, VERTEX*);
VERTEX* pop(STACK*);
int getSize(STACK*);

#endif