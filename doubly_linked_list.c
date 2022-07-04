#include <stdio.h>
#include <stdlib.h>

#define PANIC(x) printf("[%s:%d] panicking - %s\n", __FILE__, __LINE__, x); exit(1)

typedef struct Node Node;

struct Node {
    unsigned int value;
    Node *prev;
    Node *next;
};

Node *create_node(int *value)
{
    Node *node = malloc(sizeof(Node));
    if (node == NULL) {
        PANIC("Can't alloc new node");
    }

    node->value = *value;
    node->prev = NULL;
    node->next = NULL;

    *value += 1;
    return node;
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

void print_list(Node *head)
{
    Node* tmp = head;

    while (tmp != NULL) {
        printf("%d -> ", tmp->value);
        tmp = tmp->next;
    }
    printf("end\n");
}

void add_node_to_end(Node *head, Node *node)
{
    if (head == NULL || node == NULL) { PANIC("Invalid Pointers"); }

    Node *tmp = head;
    while (tmp->next != NULL) tmp = tmp->next;

    tmp->next = node;
    node->prev = tmp;
}

void add_node_to_start(Node *head, Node *node)
{
    if (head == NULL || node == NULL) { PANIC("Invalid Pointers"); }

    node->next = head;
    node->prev = NULL;
    head->prev = node;
}

void add_node_at_index(Node *head, Node *node, int index)
{
    if (head == NULL || node == NULL) { PANIC("Invalid Pointers"); }

    if (index < 0) { PANIC("Invalid index"); }

    if (index == 0) { PANIC("Trying to overwrite head pointer in add_node_at_index(). \nNote: should be using add_node_to_start()"); }

    Node *tmp = head;
    int i = 0;
    while (tmp->next != NULL && i < index - 1) {
        tmp = tmp->next;
        i++;
    }

    if (tmp->next != NULL) {
        node->next = tmp->next;
        tmp->next->prev = node;
    }

    tmp->next = node;
    node->prev = tmp;
}

int main(void)
{
    int value = 1;
    Node *head = create_node(&value);
    Node *second = create_node(&value);
    Node *new_head = create_node(&value);
    Node *fourth = create_node(&value);

    add_node_to_end(head, second);
    add_node_to_start(head, new_head);
    add_node_at_index(new_head, fourth, 1);

    print_list(new_head);

    free_list(new_head);
    return 0;
}
