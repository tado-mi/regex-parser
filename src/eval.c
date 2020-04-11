// recursive descent parser
#include "../rdp.h"

// evaluator
#include "../eval.h"

void preorder(TREE tree) {
  if (tree == NULL)
    return;

  char* focus = get_label(tree);

  if (strcmp(focus, "|") == 0) {
    printf("(union ");
  }

  else if (strcmp(focus, ".") == 0) {
    printf("(concat ");
  }

  else if (strcmp(focus, "*") == 0) {
    printf("(closure ");
  }

  else {
    printf("(atomic %s", focus);
  }

  TREE* children = get_children(tree);
  for (int i = 0; children[i] != NULL; i++) {
    preorder(children[i]);
  }

  printf(") ");

}

TREE expression(TREE full) {

  TREE root = NULL;

  char* focus = get_label(full);
  TREE* temp_children = get_children(full);
  TREE first = temp_children[0];

  if (strcmp(focus, "<E>") == 0) {
    TREE  ET_tree = temp_children[1];

    TREE* ET_children = get_children(ET_tree);
    if (strcmp(get_label(ET_children[0]), "|") == 0) {
      root = new_TREE("|");
      add_child(root, expression(first));
      add_child(root, expression(ET_children[1]));
    } else {
      root = expression(first);
    }
  }

  if (strcmp(focus, "<C>") == 0) {
    // first child: <S>
    TREE  CT_tree = temp_children[1];
    TREE* CT_children = get_children(CT_tree);
    if (strcmp(get_label(CT_children[0]), ".") == 0) {
      root = new_TREE(".");
      add_child(root, expression(first));
      add_child(root, expression(CT_children[1]));
    } else {
      root = expression(first);
    }

  }

  if (strcmp(focus, "<S>") == 0) {
    // first child: <A>
    TREE  ST_tree = temp_children[1];
    TREE* ST_children = get_children(ST_tree);
    if (strcmp(get_label(ST_children[0]), "*") == 0) {
      root = new_TREE("*");
      add_child(root, expression(first));
    } else {
      root = expression(first);
    }

  }

  if (strcmp(focus, "<A>") == 0) {
    if (strcmp(get_label(first), "(") == 0) {
      root = expression(temp_children[1]);
    } else {
      root = temp_children[0];
    }
  }

  return root;
}

void evaluate(TREE full) {

  TREE expr = expression(full);
  printf("expression tree:\n");

  print_TREE(expr);

  printf("preorder evaluation:\n");
  preorder(expr);
  printf("\n");

}

TREE get_tree(char* regex) {

  TREE tree = recursive();
  tree = expression(tree);
  return tree;

}
