#ifndef TREE_H
#define TREE_H

typedef struct array array;

typedef struct node_tree_s {
    array* children;
    void* data;
} node_tree;

node_tree* tree_create();
array* tree_get_children(node_tree* parent);
node_tree* tree_append_children(node_tree* parent, node_tree *child);
node_tree* tree_get_child(node_tree* parent, int index);
void tree_free(node_tree *root, void (*f)(void*));

#endif