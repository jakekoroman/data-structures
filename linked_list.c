/*
** This program implements a linked list and allows the user to create nodes, insert nodes at the start and end of the list.
** As well as a specific index of the list.
** Author: Jake Koroman
** Date:   06/30/2022
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;

struct Node {
    unsigned int value;
    Node *next;
};

void add_node_to_end(Node *head, Node *node)
{
    Node *tmp = head;
    while (tmp->next != NULL) {
        tmp = tmp->next;
    }
    tmp->next = node;
}

void add_node_to_start(Node *head, Node *node)
{
    node->next = head;
}

// If the index given is to high it will insert at the end of the list
// this could cause undefined behaviour if you intend to keep track of
// that index.
void add_node_at_index(Node *head, Node *node, int index)
{
    Node *tmp = head;
    int i = 0;

    while (tmp->next != NULL && i < index - 1) {
        tmp = tmp->next;
        i++;
    }

    Node *old_ptr = tmp->next;
    tmp->next = node;
    node->next = old_ptr;
}

Node *create_node(int *value)
{
    Node *node = malloc(sizeof(Node));
    node->value = *value;
    node->next = NULL;
    *value += 1;
    return node;
}

void print_list(Node *head)
{
    Node* tmp = head;

    while (tmp != NULL) {
        printf("%d -> ", tmp->value);
        tmp = tmp->next;
    }
    printf("end\n");
}

void free_list(Node *head)
{
    Node *tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

int main(void)
{
    int counter = 1;

    Node *head = create_node(&counter);
    Node *next = create_node(&counter);

    add_node_to_end(head, next);

    Node *new_head = create_node(&counter);

    add_node_to_start(head, new_head);

    Node *last_one = create_node(&counter);
    add_node_at_index(new_head, last_one, 1);

    print_list(new_head);
    free_list(new_head);
    return 0;
}
