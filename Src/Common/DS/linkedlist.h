#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#include <stdlib.h>

#include "Common/Algorithm/QSort.h"

typedef struct _Node {
    void *data;
    struct _Node *next;
} Node;

#define ll_get_node(node, type) ((type *)node->data)

typedef struct {
    Node *head;
    Node *tail;
    int size;
} linkedlist;


linkedlist linkedlist_create()
{
    return (linkedlist) {
        .head = NULL,
        .tail = NULL,
        .size = 0
    };
}


linkedlist *linkedlist_insert_after(linkedlist *list, Node *node, void *data)
{
    Node *new_node = (Node *) malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = node->next;
    node->next = new_node;
    list->size++;
    return list;
}


linkedlist *linkedlist_append(linkedlist *list, void *data)
{
    Node *new_node = (Node *) malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    if (list->head == NULL) {
        list->head = new_node;
        list->tail = new_node;
    } else {
        list->tail->next = new_node;
        list->tail = new_node;
    }
    list->size++;
    return list;
}

void *linkedlist_pop_value(linkedlist *list)
{
    if (list->head == NULL) {
        return NULL;
    }
    Node *node = list->head;
    list->head = node->next;
    list->size--;
    void *data = node->data;
    free(node);
    return data;
}

#define linkedlist_append_value(list, type, value) { \
    type *new_value = (type *) malloc(sizeof(type)); \
    *new_value = value; \
    linkedlist_append(list, new_value); \
}


void linkedlist_clear(linkedlist *list)
{
    Node *node = list->head;
    while (node != NULL) {
        Node *next = node->next;
        free(node->data);
        free(node);
        node = next;
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}


linkedlist linkedlist_sort(linkedlist list, int (*compare)(const void *, const void *, void *), void *data)
{
    linkedlist sorted = linkedlist_create();

    void **values = (void **) malloc(sizeof(void *) * list.size);
    int i = 0;
    for(Node *node = list.head; node != NULL; node = node->next, i ++) {
        values[i] = node->data;
    }

    QSort(values, 0, list.size - 1, compare, data);


    for(int i = 0; i < list.size; i ++) {
        linkedlist_append(&sorted, values[i]);
    }
    return sorted;
}


void linkedlist_reverse(linkedlist *list)
{
    Node *node = list->head;
    Node *prev = NULL;
    while (node != NULL) {
        Node *next = node->next;
        node->next = prev;
        prev = node;
        node = next;
    }
    list->tail = list->head;
    list->head = prev;
}
#endif