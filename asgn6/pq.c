#include "pq.h"

#include "node.h"

#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct ListElement ListElement;

struct ListElement {
    Node *tree;
    ListElement *next;
};

struct PriorityQueue {
    ListElement *list;
};

PriorityQueue *pq_create(void) {
    //allocating a pq object
    PriorityQueue *pq = calloc(1, sizeof(PriorityQueue));
    //returning pointer
    return pq;
}

void pq_free(PriorityQueue **q) {
    free(*q);
    *q = NULL;
}
bool pq_is_empty(PriorityQueue *q) {

    //using pointer to list to check if queue is empty, not just the queue itself
    if (q->list == NULL) {
        return true;
    } else {
        return false;
    }
}

bool pq_size_is_1(PriorityQueue *q) {
    //q_>list is first element if not null at least 1 element, but could be more
    //in order to check if size 1
    //also need to check if there's any elements after 1st one

    if (q->list == NULL) {
        return false;
    } else if (q->list->next != NULL) {
        return false;
        //first element exists but theres not element after it
    } else {
        return true;
    }
}
void enqueue(PriorityQueue *q, Node *tree) {

    //not gonna give exact same output
    //declaration and memory allocation to pointer
    ListElement *e = (ListElement *) malloc(sizeof(ListElement));
    e->tree = tree;
    e->next = NULL;

    //tree-like structure with if-else statements is checking the current state of the queue then executes what's needed
    //if queue is empty
    if (q->list == NULL) {
        q->list = e;
    }
    //inserting an element if there's nothing at the beginning of the list
    else if (tree->weight < q->list->tree->weight) {
        e->next = q->list;
        q->list = e;
    }
    //inserting an element after an existing element in the list
    else {
        ListElement *prev = q->list;
        while (prev->next != NULL && prev->next->tree->weight <= e->tree->weight) {
            prev = prev->next;
        }
        e->next = prev->next;
        prev->next = e;
    }
}

bool dequeue(PriorityQueue *q, Node **tree) {
    //if queue is empty, returning false
    if (q->list == NULL) {
        return false;
    }

    ListElement *e = q->list;
    q->list = e->next;
    *tree = e->tree;
    free(e);
    return true;
}

void pq_print(PriorityQueue *q) {
    assert(q != NULL);
    ListElement *e = q->list;
    int position = 1;
    while (e != NULL) {
        if (position++ == 1) {
            printf("=============================================\n");
        } else {
            printf("---------------------------------------------\n");
        }
        node_print_tree(e->tree, '<', 2);
        e = e->next;
    }
    printf("=============================================\n");
}
