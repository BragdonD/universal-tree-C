#ifndef TREE_H
#define TREE_H

typedef struct array array;

typedef struct node_tree_s {
    array* children;
    void* data;
} node_tree;

node_tree* tree_create();
node_tree* tree_create_node(void *data);
node_tree* tree_create_node_with_children(void* data, void* arr, int len, size_t type_size);
array* tree_get_children(node_tree* parent);
node_tree* tree_append_children(node_tree* parent, node_tree *child);
node_tree* tree_get_child(node_tree* parent, int index);
void tree_free(node_tree *root, void (*f)(void*));
void tree_inorder(node_tree *root, void (*f)(void*));
void tree_postorder(node_tree *root, void (*f)(void*));
void tree_preorder(node_tree *root, void (*f)(void*));
void tree_levelorder(node_tree *root, void (*f)(void*));
void tree_preorder_next(node_tree *root, void (*f)(void*));

#endif