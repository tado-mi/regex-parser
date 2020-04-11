// table driven parser
#include "../tdp.h"

// syntactic categories
int num_synt = 7;
#define E 0
#define C 1
#define S 2
#define A 3
#define ET 4
#define CT 5
#define ST 6

int num_term = 6;
int get_index_tm(char* str) {

  if (strcmp(str, "α") == 0) {
    return 0;
  }

  // first character of the input
  char c = *str;

  switch (c) {
    case 'a':
    case 'b':
    case 'c':
    case 'd':
    case 'e':
    case 'f':
    case 'g':
    case 'h':
    case 'i':
    case 'j':
    case 'k':
    case 'l':
    case 'm':
    case 'n':
    case 'o':
    case 'p':
    case 'q':
    case 'r':
    case 's':
    case 't':
    case 'u':
    case 'v':
    case 'w':
    case 'x':
    case 'y':
    case 'z':
      return 0;
    case '(':
      return 1;
    case '*':
      return 2;
    case '.':
      return 3;
    case '|':
      return 4;
    case ')':
    case '\0':
      return 5;
    default:
      return -1;
  }

}

int get_index_sc(char* str) {
  if (strcmp(str, "<E>") == 0)
    return E;
  if (strcmp(str, "<C>") == 0)
    return C;
  if (strcmp(str, "<S>") == 0)
    return S;
  if (strcmp(str, "<A>") == 0)
    return A;
  if (strcmp(str, "<ET>") == 0)
    return ET;
  if (strcmp(str, "<CT>") == 0)
    return CT;
  if (strcmp(str, "<ST>") == 0)
    return ST;
  return -1;
}

char*** prod;
int num_prod = 9;
void hardcode_productions() {

  prod = malloc(num_prod * sizeof(char**));
  for (int i = 0; i < num_prod; i = i + 1) {
    prod[i] = malloc(3 * sizeof(char*));
    for (int j = 0; j < 3; j = j + 1) {
      prod[i][j] = NULL;
    }
  }

  // <E> on α, (
  prod[0][0] = "<C>";
  prod[0][1] = "<ET>";

  // <ET> on '|'
  prod[1][0] = "|";
  prod[1][1] = "<E>";

  // <C> on α, (
  prod[2][0] = "<S>";
  prod[2][1] = "<CT>";

  // <CT> on .
  prod[3][0] = ".";
  prod[3][1] = "<C>";

  // <S> on α, (
  prod[4][0] = "<A>";
  prod[4][1] = "<ST>";

  // <ST> on *
  prod[5][0] = "*";
  prod[5][1] = "<ST>";

  // <A> on (
  prod[6][0] = "(";
  prod[6][1] = "<E>";
  prod[6][2] = ")";

  // ε production
  prod[7][0] = "ε";

  // <A> on α
  prod[8][0] = "α";

}

int** table;
void hardcode_table() {

  hardcode_productions();

  // initialise the table
  table = malloc(num_synt * sizeof(int*));
  for (int i = 0; i < num_synt; i = i + 1) {
    table[i] = malloc(num_term * sizeof(int));
    for (int j = 0; j < num_term; j = j + 1) {
      table[i][j] = -1;
      if (i == ET || i == CT || i == ST) {
        table[i][j] = 7; // ε production
      }
    }
  }

  // hardcode the table

  // row for <E>
  table[E][0] = 0;
  table[E][1] = 0;

  // row for <C>
  table[C][0] = 2;
  table[C][1] = 2;

  // row for <S>
  table[S][0] = 4;
  table[S][1] = 4;

  // row for <A>
  table[A][0] = 8;
  table[A][1] = 6;

  // row for <ET>
  table[ET][4] = 1;

  // row for <CT>
  table[CT][3] = 3;

  // row for <ST>
  table[ST][2] = 5;


}

TREE drive() {

  hardcode_table();

  STACK stack = new_STACK();
  push(stack, "<E>");

  TREE root = new_TREE("<E>");
  STACK tree_stack = new_STACK();
  push(tree_stack, root);

  while (!is_empty(stack)) {

    char* focus = pop(stack);
    TREE node = pop(tree_stack);

    if (strcmp(focus, "ε") == 0) {
      continue;
    }

    int TM = get_index_tm(focus);
    int SC = get_index_sc(focus);

    int input_index = get_index_tm(input);

    if (SC >= 0) { // syntactic category

      int prod_index = table[SC][input_index];
      if (prod_index < 0) {
        printf("missing production for %s on input %c\n", focus, *input);
        return NULL;
      }

      char** current_production = prod[prod_index];
      // record the pointers to the nodes so we can add the nodes in correct order
      TREE *children = malloc(3 * sizeof(TREE));

      // push productions and nodes onto the stacks in the opposite order
      for (int i = 2; i >= 0; i = i - 1) {
        if (current_production[i] == NULL) continue;
        char* temp = current_production[i];
        if (strcmp(temp, "α") == 0) {
          temp = malloc(sizeof(char));
          *temp = *input;
        }
        push(stack, temp);
        TREE new_node = new_TREE(temp);
        push(tree_stack, new_node);
        *(children + i) = new_node;
      }

      for (int i = 0; i <= 2; i = i + 1) {
        add_child(node, *(children + i));
      }

    }

    else if (TM >= 0) { // terminal

      // match the terminal
      if (*input != *focus) {
        printf("input mismatch on focus: [%s] and input: [%s]\n", focus, input);
        return NULL;
      }
      input++;

    }

    else {

      printf("\tERROR: illegal input on the stack: [%s]\n", focus);
      return NULL;

    }

  }

  return root;
}
