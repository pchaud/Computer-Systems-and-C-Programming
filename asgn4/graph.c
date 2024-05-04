#include "graph.h"

#include "path.h"
#include "stack.h"
#include "vertices.h"

#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct graph {
    uint32_t vertices;
    bool directed;
    bool *visited;
    char **names;
    uint32_t **weights;
} Graph;

Graph *graph_create(uint32_t vertices, bool directed) {

    Graph *g = calloc(1, sizeof(Graph));
    g->vertices = vertices;
    g->directed = directed;
    // use calloc to initialize everything with zeroes
    g->visited = calloc(vertices, sizeof(bool));
    g->names = calloc(vertices, sizeof(char *));
    // allocate g->weights with a pointer for each row
    g->weights = calloc(vertices, sizeof(g->weights[0]));
    // allocate each row in the adjacency matrix
    for (uint32_t i = 0; i < vertices; ++i) {
        g->weights[i] = calloc(vertices, sizeof(g->weights[0][0]));
    }
    return g;
}

void graph_free(Graph **gp) {
    if (gp == NULL || *gp == NULL) {
        return;
    }
    //frees all memory used by the graph
    Graph *g = *gp;
    free(g->visited);

    //frees all the items I calloced in graph_create so: names, vertices, and weights
    for (uint32_t i = 0; i < g->vertices; i += 1) {
        free(g->names[i]);
    }
    free(g->names);

    //in these loops we are iterating through weights and previously names and free each
    //individual weight/name
    for (uint32_t i = 0; i < g->vertices; i++) {
        free(g->weights[i]);
    }
    free(g->weights);
    free(g);

    *gp = NULL;
}

uint32_t graph_vertices(const Graph *g) {
    //simply finds the number of vertices in the graph
    return g->vertices;
}

void graph_add_edge(Graph *g, uint32_t start, uint32_t end, uint32_t weight) {
    //adds an edge between start and end and assigns this calculation to weight
    //if statement if its directed
    if (g->directed) {
        g->weights[start][end] = weight;
        //otherwise it does both for undirected
    } else {
        g->weights[start][end] = weight;
        g->weights[end][start] = weight;
    }
}
uint32_t graph_get_weight(const Graph *g, uint32_t start, uint32_t end) {
    //looks up weight of edge bw start and end
    //returns retrieved weight
    return g->weights[start][end];
}

void graph_visit_vertex(Graph *g, uint32_t v) {
    //checks if vertex is greater than or equal to the vertices and in range
    if (v >= g->vertices) {
        return;
    }
    //sets visited status of each vertex to true, flagged as visited
    g->visited[v] = true;
}

void graph_unvisit_vertex(Graph *g, uint32_t v) {
    if (v < g->vertices) {
        //sets vertices that were visited as false
        g->visited[v] = false;
    }
}

bool graph_visited(const Graph *g, uint32_t v) {
    //checks if vertex is visited, will return
    if (g->visited[v]) {
        return true;
    } else {
        return false;
    }
}

char **graph_get_names(const Graph *g) {
    //returns the names of every city in the graph array
    //returning a double pointer
    return g->names;
}

void graph_add_vertex(Graph *g, const char *name, uint32_t v) {
    if (g->names[v]) {
        free(g->names[v]);
    } else {

        g->names[v] = strdup(name);
    }
}

const char *graph_get_vertex_name(const Graph *g, uint32_t v) {
    //similar logic to graph_get_names but here we return the name of the city
    //with a specific vertex from the graph array
    return g->names[v];
}

void graph_print(const Graph *g) {
    printf("Graph Info:\n");
    printf("Number of Vertices: %u\n", g->vertices);
    printf("Vertex Names:\n");
    for (uint32_t i = 0; i < g->vertices; i++) {
        printf("%u: %s\n", i, g->names[i]);
    }
    printf("Edge Weights:\n");
    for (uint32_t i = 0; i < g->vertices; i++) {
        for (uint32_t j = 0; j < g->vertices; j++) {
            printf("[%u][%u]: %u\n", i, j, g->weights[i][j]);
        }
    }
}
