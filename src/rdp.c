// recursive decent parser
#include "../rdp.h"

// declare all the functions,
// so they can be called recursively,
// independent from their order of initialisation
TREE E(); TREE ET();
TREE C(); TREE CT();
TREE S(); TREE ST();
TREE A();

TREE recursive() {
  return E();
}

TREE E() {
  // <E> -> <C><ET>
  TREE E_tree = new_TREE("<E>");

  TREE C_tree = C();
  if (C_tree == NULL) {
    return NULL;
  }
  add_child(E_tree, C_tree);

  TREE ET_tree = ET();
  if (ET_tree == NULL) {
    return NULL;
  }
  add_child(E_tree, ET_tree);

  return E_tree;
}

TREE C() {
  // <C> -> <S><CT>
  TREE C_tree = new_TREE("<C>");

  TREE S_tree = S();
  if (S_tree == NULL) {
    return NULL;
  }
  add_child(C_tree, S_tree);

  TREE CT_tree = CT();
  if (CT_tree == NULL) {
    return NULL;
  }
  add_child(C_tree, CT_tree);

  return C_tree;

}

TREE S() {
  // <S> -> <A><ST>
  TREE S_tree = new_TREE("<S>");

  TREE A_tree = A();
  if (A_tree == NULL) {
    return NULL;
  }
  add_child(S_tree, A_tree);

  TREE ST_tree = ST();
  if (ST_tree == NULL) {
    return NULL;
  }
  add_child(S_tree, ST_tree);

  return S_tree;
}

TREE A() {
  char* str = malloc(2 * sizeof(char));
  *(str + 0) = *input;
  *(str + 1) = '\0';

  // <A> -> (<E>) | a | b ... | z
  TREE A_tree = new_TREE("<A>");
  TREE E_tree = NULL;
  switch (*input) {
    case '(': // <A> -> (<E>)
      input++;
      add_child(A_tree, new_TREE("("));
      E_tree = E();
      if (E_tree == NULL) {
        return NULL;
      }
      add_child(A_tree, E_tree);
      if (*input != ')') {
        return NULL;
      }
      input++;
      add_child(A_tree, new_TREE(")"));
      return A_tree;
    case 'a': // <A> -> a
    case 'b': // <A> -> b
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
    case 'z': // <A> -> z
      add_child(A_tree, new_TREE(str));
      input++;
      return A_tree;
    default:
      return NULL;
  }
}

// tails
TREE ET() {
  // <ET> -> |<E> | ε
  TREE ET_tree = new_TREE("<ET>");
  TREE E_tree = NULL;
  switch (*input) {
    case '|': // <ET> -> |<E>
      input++;
      add_child(ET_tree, new_TREE("|"));
      E_tree = E();
      if (E_tree == NULL) {
        return NULL;
      }
      add_child(ET_tree, E_tree);
      break;
    default: // <ET> -> ε
      add_child(ET_tree, new_TREE("ε"));
  }
  return ET_tree;
}

TREE CT() {
  // <CT> -> .<C> | ε
  TREE CT_tree = new_TREE("<CT>");
  TREE C_tree = NULL;
  switch (*input) {
    case '.': // <CT> -> .<C>
      input++;
      add_child(CT_tree, new_TREE("."));
      C_tree = C();
      if (C_tree == NULL) {
        return NULL;
      }
      add_child(CT_tree, C_tree);
      break;
    default: // <CT> -> ε
      add_child(CT_tree, new_TREE("ε"));
  }
  return CT_tree;
}

TREE ST() {
  // <ST> -> *<ST> | ε
  TREE ST_tree = new_TREE("<ST>");
  TREE ST_tree2 = NULL;
  switch (*input) {
    case '*': // <ST> -> *<ST>
      input++;
      add_child(ST_tree, new_TREE("*"));
      ST_tree2 = ST();
      if (ST_tree2 == NULL) {
        return NULL;
      }
      add_child(ST_tree, ST_tree2);
      break;
    default: // <ST> -> ε
      add_child(ST_tree, new_TREE("ε"));
  }
  return ST_tree;
}
