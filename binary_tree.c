/*
** This program creates a binary tree and inverts it.
** Author: Jake Koroman
** Date:   06/30/2022
*/

#include <stdio.h>
#include <stdlib.h>

#define TREE_SIZE 3

typedef struct Node Node;

struct Node {
    unsigned int value;
    struct Node *left;
    struct Node *right;
};

Node *gen_tree(int level, unsigned int *counter)
{
    if (level == 0) return NULL;

    Node *node = malloc(sizeof(Node));
    node->value = *counter;

    *counter += 1;
    node->left = gen_tree(level - 1, counter);
    node->right = gen_tree(level - 1, counter);
    return node;
}

Node *invert_tree(Node *node)
{
    if (node == NULL) return NULL;

    Node *tmp = node->left;
    node->left = node->right;
    node->right = tmp;

    return node;
}

void print_tree(Node *node, int level)
{
    if (node == NULL) return;

    print_tree(node->left, level + 1);

    for (int i = 0; i < level; ++i) printf("  ");

    printf("%d\n", node->value);
    print_tree(node->right, level + 1);
}

void free_tree(Node *node)
{
    if (node == NULL) return;

    free_tree(node->left);
    free_tree(node->right);
    free(node);
}

int main(void)
{
    unsigned int counter = 1;
    Node *tree = gen_tree(TREE_SIZE, &counter);

    print_tree(tree, 0);
    printf("--------------------\n");
    invert_tree(tree);
    print_tree(tree, 0);
    free_tree(tree);

    return 0;
}
