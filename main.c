#include <stdio.h>
#include <stdlib.h>

#include "tree.h"
// recursive descent parser
#include "rdp.h"

void process() {
  printf("processing input: [%s]\n", input);
  TREE E_tree = E();
  if (E_tree == NULL) {
    printf("tree was not constructed\n");
  } else if (*input != '\0') {
    printf("input contained a valid substring\n");
    printf("remaining chars: [%s]", input);
    return;
  }
  printf("tree construction succeeded:\n");
  print_TREE(E_tree);
}

int main() {
  input = "a|(c.d)*";
  process();
}
