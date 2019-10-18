#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

#define MAX 200

typedef struct STACK *STACK;
extern STACK new_STACK();
extern void print_STACK(STACK stack);
extern void* pop(STACK stack);
extern void push(STACK stack, void* data);
extern int is_empty(STACK stack);
