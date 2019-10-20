#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// data structures
#include "tree.h"
#include "stack.h"

// recursive descent parser
#include "rdp.h"
// table driven parser
#include "tdp.h"
// evaluator
#include "eval.h"

char* input;
#include "input.h"

void parse(char* method) {
  char* str = input;
  printf("processing input: [%s] on  a ", input);

  TREE tree = NULL;

  if (strcmp(method, "RDP") == 0) {
    printf("Recursive Descent parser.\n");
    tree = recursive();
  }
  if (strcmp(method, "TDP") == 0) {
    printf("Table Driven parser.\n");
    tree = drive();
  }

  if (tree == NULL) {
    printf("tree was not constructed\n");
    return;
  } else if (*input != '\0') {
    printf("input contained a valid substring; remaining chars: [%s]\n", input);
    return;
  }

  printf("tree construction succeeded:\n");
  print_TREE(tree);

  evaluate(tree);

  // recover the input
  input = str;
}


int main() {

  input = "a|(c.d)*";
  char* method = "RDP";

  parse(method);

}
