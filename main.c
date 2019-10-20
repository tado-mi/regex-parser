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

// define some constants
#define TDP  "TDP"
#define RDP  "RDP"
#define EVAL "EVAL"

char* input;
#include "input.h"

void parse(char* method) {
  // char* str = input;
  printf("processing input \"%s\" on the ", input);

  TREE tree = NULL;

  if (strcmp(method, RDP) == 0) {
    printf("Recursive Descent parser.\n");
    tree = recursive();
  }
  if (strcmp(method, TDP) == 0) {
    printf("Table Driven parser.\n");
    tree = drive();
  }
  if (strcmp(method, EVAL) == 0) {
    printf("Evalutor.\n");
    tree = recursive();
    if (tree == NULL || *input != '\0') {
      printf("Invalid input.\n");
      return;
    }
    evaluate(tree);
    return;
  }

  if (tree == NULL) {
    printf("tree was not constructed\n");
    return;
  } else if (*input != '\0') {
    printf("tree was constructed, but the input contained a valid substring; remaining chars: \"%s\"\n", input);
    return;
  }

  printf("tree construction succeeded:\n");
  print_TREE(tree);

  // recover the input
  // input = str;
}

void interact() {
    char* quit = "quit";
    char* method = RDP;
    char* next_method = "start the table driven parser";
    char* temp;
    int max_len = 100;
    printf("Starting the Recursive Descent parser.\n");
  while (1) {
    printf("enter the expression [up to %d characters / \"%s\" to %s]: ", max_len, quit, next_method);
    temp = malloc(max_len * sizeof(char));
    fgets(temp, max_len, stdin);
    input = malloc(strlen(temp) - 1 * sizeof(char));
    memcpy(input, temp, strlen(temp) - 1);
    if (strcmp(input, quit) == 0) {
      if (strcmp(method, EVAL) == 0) {
        return;
      }
      if (strcmp(method, TDP) == 0) {
        method = EVAL;
        next_method = "quit";
        printf("Switch to the Evaluating.\n");
        continue;
      }
      method = TDP;
      next_method = "start evaluating";
      printf("Switch to the Table Driven parser.\n");
      continue;
    }
    parse(method);
  }
}

int main() {

  interact();
  printf("\nterminated\n");

  return 1;

}
