#include <stdlib.h>
#include "array.h"
#include "tree.h"

/// @brief Function to create a generic tree.
/// @return An empty tree. Return NULL in case of error.
node_tree* tree_create() {
    node_tree* temp = NULL;
    temp = malloc(sizeof *temp);
    if(temp == NULL) return NULL; /// Error to be handle in the caller function
    temp->children = arr_init(sizeof *(temp->children));
    if(temp->children == NULL) { ///Handle failed of malloc in arr_init
        free(temp);
        return NULL;
    }
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
    return arr_get(parent->children, index);
}

/// @brief Function to free a tree. 
/// @param root A pointer to the root of a tree.
/// @param free_data Function pointer to free the data.
void tree_free(node_tree *root, void (*free_data)(void*)) {
    if(root == NULL) return;
    for(int i = 0; i < arr_lenght(root->children); i++) {
        node_tree* node = arr_get(root->children, i);
        free_data(node->data);
        tree_free(node, free_data);
        free(node);
    }
}
