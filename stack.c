#include "stack.h"

typedef struct NODE *NODE;
struct NODE {
  void* data;
  NODE next;
};

struct STACK {
  NODE top;
};

STACK new_STACK() {
  STACK stack = malloc(sizeof(struct STACK));
  (*stack).top = NULL;
  return stack;
}

void push(STACK stack, void* data) {
  NODE new = malloc(sizeof(struct NODE));
  (*new).data = data;
  (*new).next = (*stack).top;

  (*stack).top = new;
}

void* pop(STACK stack) {
  if (is_empty(stack)) {
    return NULL;
  }
  NODE top = (*stack).top;
  (*stack).top = (*top).next;
  return (*top).data;

}

int is_empty(STACK stack) {
  NODE top = (*stack).top;
  return top == NULL;
}

void print_STACK(STACK stack) {
  printf("\n");
  NODE top = (*stack).top;
  while (top != NULL) {
    printf("%s\n", (char*)(*top).data);
    top = (*top).next;
  }
  printf("________________\n");
}
