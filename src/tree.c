#include <stdlib.h>
#include "array.h"
#include "tree.h"
#include "queue.h"

/// @brief Function to free a tree. 
/// @param root A pointer to the root of a tree.
/// @param free_data Function pointer to free the data.
void tree_free(node_tree *root, void (*free_data)(void*)) {
    if(root == NULL) return;
    int len = arr_lenght(root->children);
    for(int i = 0; i < len; i++) {
        node_tree* child = arr_end(root->children);
        if(free_data != NULL)
            free_data(child->data);
        tree_free(child, free_data);
        arr_pop_back(root->children);
    }
}

/// @brief Function to create a generic tree.
/// @return An empty tree. Return NULL in case of error.
node_tree* tree_create() {
    node_tree* temp = NULL;
    temp = malloc(sizeof *temp);
    if(temp == NULL) return NULL; /// Error to be handle in the caller function
    temp->children = arr_init(sizeof(*temp));
    temp->data = NULL;
    return temp;
}

/// @brief Function to create a node of tree.
/// @param data The data contain inside the node.
/// @return a pointer toward the created node.
node_tree* tree_create_node(void *data) {
    node_tree* temp = NULL;
    temp = malloc(sizeof *temp);
    if(temp == NULL) return NULL; /// Error to be handle in the caller function
    temp->children = arr_init(sizeof(*temp));
    temp->data = data;
    return temp;
}

/// @brief Function to create a new node with an array of children.
/// @param data data of the nodes
/// @param arr array of data for the children nodes
/// @param len size of the array of data.
/// @param type_size size of the data.
/// @return The new node or NULL in case of error.
node_tree* tree_create_node_with_children(void* data, void* arr, int len, size_t type_size) {
    node_tree* temp = NULL;
    temp = malloc(sizeof *temp);
    if(temp == NULL) return NULL; /// Error to be handle in the caller function
    temp->children = arr_init(sizeof(*temp));
    for(int i = 0; i<len; type_size == sizeof(char) ? i+=2 : i++) {
        node_tree* node = tree_create_node((((char*)arr) + (i) * type_size));

        if(node == NULL) {
            tree_free(temp, NULL);
            return NULL;
        }
        if(!arr_push_back(temp->children, node)) {
            tree_free(temp, NULL);
            return NULL;
        }
    }
    temp->data = data;
    return temp;
}

/// @brief Function to get the children of a given node
/// @param parent The node to retrieve children from.
/// @return An array structure containing the node of the others children.
array* tree_get_children(node_tree* parent) {
    if(parent == NULL) return NULL;
    return parent->children;
}

/// @brief Function to append a children node to a parent node of a tree.
/// @param parent The parent node.
/// @param child The children node.
/// @return The new parent. The children in case the parent is NULL.
node_tree* tree_append_children(node_tree* parent, node_tree *child) {
    if(parent == NULL) return child;
    arr_push_back(parent->children, child);
    return parent;    
}

/// @brief Function to get the child of a node at given index.
/// @param parent The parent node.
/// @param index The index of the child.
/// @return return a pointer toward the children node. Return NULL in case of error. 
node_tree* tree_get_child(node_tree* parent, int index) {
    if(parent == NULL) return NULL;
    if(arr_lenght(parent->children) == 0) return NULL;
    return arr_get(parent->children, index);
}

void tree_inorder(node_tree *root, void (*f)(void*)) {
    if(root == NULL) return;
    if(f == NULL) return;
    int length = arr_lenght(root->children);
    for(int i=0; i<length -1; i++) {
        tree_inorder(tree_get_child(root, i), f);
    }
    f(root->data);
    tree_inorder(tree_get_child(root, length-1), f);
}

void tree_postorder(node_tree *root, void (*f)(void*)) {
    if(root == NULL) return;
    if(f == NULL) return;
    int length = arr_lenght(root->children);
    for(int i=0; i<length; i++) {
        tree_postorder(tree_get_child(root, i), f);
    }
    f(root->data);
}

void tree_preorder(node_tree *root, void (*f)(void*)) {
    if(root == NULL) return;
    if(f == NULL) return;
    int length = arr_lenght(root->children);
    f(root->data);
    for(int i=0; i<length; i++) {
        tree_preorder(tree_get_child(root, i), f);
    }
}

void tree_levelorder(node_tree *root, void (*f)(void*)) {
    if(root == NULL) return;
    if(f == NULL) return;
    queue* bfs = queue_create();
    queue_push(bfs, root);
    while(!queue_empty(bfs)) {
        node_tree* node = queue_pop(bfs);
        f(node->data);
        int length = arr_lenght(node->children);
        for(int i=0; i<length; i++) {
            queue_push(bfs, tree_get_child(node, i));
        }
    }
    queue_free(bfs);
}

void tree_preorder_next(node_tree *root, void (*f)(void*)) {
    if(root == NULL) return;
    if(f == NULL) return;
    int length = arr_lenght(root->children);
    for(int i=0; i<length; i++) {
        tree_preorder_next(tree_get_child(root, i), f);
    }
    f(root->data);
}