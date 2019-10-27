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

STACK reverse(STACK stack) {
  STACK ans = new_STACK();
  while (!is_empty(stack)) {
    NODE temp = pop(stack);
    push(ans, temp);
  }
  return ans;
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

void* peek(STACK stack) {
  if (is_empty(stack)) {
    return NULL;
  }
  NODE top = (*stack).top;
  return (*top).data;

}

int is_empty(STACK stack) {
  NODE top = (*stack).top;
  return top == NULL;
}

// usage: print_stack(stack, &print_function_name)
void print_STACK(STACK stack, void (*f)()) { // receive address of f : a print function

  NODE top = (*stack).top;
  while (top != NULL) {
    if (f == NULL) {
      printf("%s\n", (char*)(*top).data);
    } else {
      f((*top).data);
    }
    top = (*top).next;
  }
  printf("________________\n");
}
