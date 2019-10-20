#include "tree.h"

struct TREE {
    char* label;
    TREE child;   // left most child
    TREE sibling; // right most sibling
};

TREE new_TREE(char* label) {
  TREE tree = (TREE) malloc (sizeof(struct TREE));
  (*tree).label = label;
  (*tree).child  = NULL;
  (*tree).sibling = NULL;
  return tree;
}

// helper function to add child
void add_sibling(TREE tree, TREE sib) {
  TREE temp = tree;
  while ((*temp).sibling != NULL) {
    temp = (*temp).sibling;
  }
  (*temp).sibling = sib;
}

void add_child(TREE root, TREE child) {
  if ((*root).child == NULL) {
    (*root).child = child;
  } else {
    add_sibling((*root).child, child);
  }
}

// helper function to print tree
void printh_TREE(TREE tree, int level) {
  if (tree == NULL) {
    return;
  }
  for (int i = 0; i < level; i = i + 1) {
    printf("  ");
  }
  printf("%s\n", (*tree).label);

  level = level + 1;
  TREE temp = (*tree).child;
  while (temp != NULL) {
    printh_TREE(temp, level);
    temp = (*temp).sibling;
  }
}

void print_TREE(TREE tree) {
  printh_TREE(tree, 0);
}

// helper functions
char* get_label(TREE tree) {
  if (tree == NULL)
    return "∅";
  return (*tree).label;
}

int num_children(TREE tree) {
  int ans = 0;
  TREE temp = (*tree).child;
  while (temp != NULL) {
    ans = ans + 1;
    temp = (*temp).sibling;
  }
  return ans;
}

TREE* get_children(TREE tree) {
  int n = num_children(tree);
  TREE* ans = malloc(n * sizeof(TREE));
  TREE temp = (*tree).child;
  for (int i = 0; i < n; i = i + 1) {
    *(ans + i) = temp;
    temp = (*temp).sibling;
  }
  return ans;
}
