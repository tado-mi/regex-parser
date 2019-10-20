#include <stdio.h>
#include <stdlib.h>

typedef struct TREE *TREE;

extern TREE new_TREE(char* label);
extern void add_child(TREE root, TREE child);
extern void print_TREE(TREE tree);

extern char* get_label(TREE tree);
extern TREE* get_children(TREE tree);
