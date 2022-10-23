#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "array.h"

void print_node(void* value) {
    printf("%s ", (char*)value);
}

/// This is the tree created for this project
///     ------A------
///     |    / \    |
///     B   b   C   D
///    / \  |  /||
///   E   F f G H I

int main(int argc, char const *argv[])
{
    node_tree* root = tree_create();
    root = tree_create_node_with_children("A\0", "B\0b\0C\0D\0", 8, sizeof(char));
    tree_append_children(tree_get_child(root, 0), tree_create_node("E\0"));
    tree_append_children(tree_get_child(root, 0), tree_create_node("F\0"));
    tree_append_children(tree_get_child(root, 1), tree_create_node("f\0"));
    tree_append_children(tree_get_child(root, 2), tree_create_node("G\0"));
    tree_append_children(tree_get_child(root, 2), tree_create_node("H\0"));
    tree_append_children(tree_get_child(root, 2), tree_create_node("I\0"));
    printf("The created tree is as follow : \n");
    printf(" ------A------\n");
    printf(" |    / \\    |\n");
    printf(" B   b   C   D\n");
    printf("/ \\  |  /|\\ \n");
    printf("E  F f G H I\n");
    printf("Inorder Traversal : ");
    tree_inorder(root, print_node);
    printf("\nPreorder Traversal : ");
    tree_preorder(root, print_node);
    printf("\nLevelorder Traversal : ");
    tree_levelorder(root, print_node);
    printf("\nPostorder Traversal : ");
    tree_preorder(root, print_node);
    printf("\nPostorderNext Traversal : ");
    tree_preorder_next(root, print_node);
    tree_free(root, NULL);
    return 0;
}
