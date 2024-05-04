
#include "path.h"

#include "graph.h"
#include "stack.h"

#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct path {
    uint32_t total_weight;
    Stack *vertices;
} Path;

Path *path_create(uint32_t capacity) {
    //Creates a path data structure & dynamically allocate memory for the Path
    Path *p = (Path *) malloc(sizeof(Path));
    //Sets capacity to the specified value assigned to capacity
    //(p->vertices->capacity)?
    //Assigns a weight of 0 to the total_weight
    p->total_weight = 0;
    //Creates a new stack object (with a specified capacity) for the path to point to
    p->vertices = stack_create(capacity);
    return p;
}

void path_free(Path **pp) {
    if (pp != NULL && *pp != NULL) {

        stack_free(&(*pp)->vertices);
    }
    free(*pp);
    *pp = NULL;

    if (pp != NULL) {
        *pp = NULL;
    }
}

uint32_t path_vertices(const Path *p) {
    return stack_size(p->vertices);
}

uint32_t path_distance(const Path *p) {

    return p->total_weight;
}

void path_add(Path *p, uint32_t val, const Graph *g) {

    //checks if there's an empty path
    if (stack_empty(p->vertices)) {
        //checks if there's an empty path
        //pushes vertex onto stack
        stack_push(p->vertices, val);
        //ensures distance remains 0
        p->total_weight = 0;
    }
    //if not an empty path
    else {
        //otherwise we look up the distance of the most recently added vertex
        uint32_t prev_vertex = 0;
        stack_peek(p->vertices, &prev_vertex);
        uint32_t weight = graph_get_weight(g, prev_vertex, val);
        //pushes vertex onto stack
        stack_push(p->vertices, val);
        //then we get this distance and add it to the total_weight
        p->total_weight += weight;
    }
}

uint32_t path_remove(Path *p, const Graph *g) {
    //could assert the stack isn't empty

    uint32_t remove;
    uint32_t curr_vertex;

    if (stack_pop(p->vertices, &remove)) {

        if (stack_empty(p->vertices)) {

            //ensures distance remains 0
            p->total_weight = 0;
            //if not an empty path
        } else {
            //otherwise we look up the distance of the most recently added vertex
            stack_peek(p->vertices, &curr_vertex);
            uint32_t weight = graph_get_weight(g, curr_vertex, remove);
            p->total_weight -= weight;
        }
    }
    return remove;
}

void path_copy(Path *dst, const Path *src) {

    //call stack_copy
    //ensure weight is correct
    //set destination's weight to total_weight

    //copying total weight
    dst->total_weight = src->total_weight;

    stack_copy(dst->vertices, src->vertices);
}

void path_print(const Path *p, FILE *f, const Graph *g) {
    stack_print(p->vertices, f, graph_get_names(g));
}
