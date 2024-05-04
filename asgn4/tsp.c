

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
#include <unistd.h>

#define OPTIONS   "i:o:dh"
#define MAX_NAMES 200

void dfs(uint32_t n, Graph *g, Path *curr_path, Path *best_path) {

    //printf("%d\n",n); prints nodes
    //lev's pseudocode
    //only use best path here

    //assignment's dfs pseudocode
    //marking n as visited, and adds vertex to the path
    graph_visit_vertex(g, n);
    path_add(curr_path, n, g);

    //this code is relying on n which we create in path_add
    //if path has n vertices
    if (path_vertices(curr_path) == graph_vertices(g)) {
        //uint32_t last_vertex = 0;
        //stack_pop(curr_path->vertices, &last_vertex);

        //if last vertex in path adjacent to start: there's a path that exists from current to start
        if (graph_get_weight(g, n, START_VERTEX) != 0) {
            //best_path += START_VERTEX;
            //g->vertices += weight;

            //add to path
            path_add(curr_path, START_VERTEX, g);

            //if shorter than best or best distance is equal to 0
            if (path_distance(curr_path) < path_distance(best_path)
                || path_distance(best_path) == 0) {
                path_copy(best_path, curr_path);
            }
            //might need to put path remove more than
            path_remove(curr_path, g);
        }
    }

    //for every one of n's edges
    //i is our vertices and n is the current vertex
    for (uint32_t i = 0; i < graph_vertices(g); i++) {
        //if edge is not visited and if the edge exists(seeing if they are neighbors of n and filtering)
        if (!graph_visited(g, i) && graph_get_weight(g, n, i)) {
            dfs(i, g, curr_path, best_path);
        }
    }

    //marks n as unvisited, and removed vertex from the path
    graph_unvisit_vertex(g, n);
    path_remove(curr_path, g);
}

int main(int argc, char **argv) {

    int op = 0;
    FILE *infile = stdin;
    FILE *outfile = stdout;
    bool directed = false;
    uint32_t vertices;
    uint32_t edges;
    uint32_t weight;
    uint32_t last_vertex;
    uint32_t start_vertex;
    char vertex_names[MAX_NAMES] = { 0 };
    Path *curr_path = NULL;
    Path *best_path = NULL;
    Graph *g = NULL;

    //switch case for command-line options
    while ((op = getopt(argc, argv, OPTIONS)) != -1) {
        switch (op) {
        case 'i': {
            infile = fopen(optarg, "r");
            if (infile == NULL) {
                printf("Error occured opening file, please enter a valid input file.");
                exit(EXIT_FAILURE);
            }
            break;
        }
        case 'o': {
            outfile = fopen(optarg, "w");
            break;
        }
        case 'd': {
            directed = true;
            break;
        }
        case 'h': {
            fprintf(stdout, "Usage: tsp [options]\n");
            fprintf(stdout,
                "-i infile     Specify the input file path containing the cities and edges\n"
                "of a graph. If not specified, the default input should be set as stdin.\n"
                "-o outfile   Specify the output file path to print to. If not specified, the "
                "default output should be set as stdout.\n"
                "-d           Specifies the graph to be directed.\n"
                "-h           Prints out a help message describing the purpose of the graph and "
                "the command-line options it accepts, exiting the 		program "
                "afterwards.\n");
            break;
        }
        }
    }

    //read file fscanf w table
    //use it w dfs to make actual path

    //scanning through number of vertices

    if (fscanf(infile, "%u\n", &vertices) != 1) {
        fprintf(stderr, "tsp: error reading number of vertices\n");
        graph_free(&g);
        path_free(&curr_path);
        path_free(&best_path);
        exit(1);
    }

    //creates graph and paths utilized by dfs function
    g = graph_create(vertices, directed);
    curr_path = path_create(vertices + 1);
    best_path = path_create(vertices + 1);

    //this is causing a newline issue
    for (uint32_t i = 0; i < vertices; i++) {
        fgets(vertex_names, sizeof(vertex_names), infile);

        //this removes the newline character added by the fgets function
        size_t len = strlen(vertex_names);
        if (len > 0 && vertex_names[len - 1] == '\n') {
            vertex_names[len - 1] = '\0';
        }
        graph_add_vertex(g, vertex_names, i);
    }

    //scanning through edges
    fscanf(infile, "%u\n", &(edges));

    //for loop w edges parameter
    //read each edge start vertex
    for (uint32_t i = 0; i < edges; i++) {
        fscanf(infile, "%u %u %u\n", &start_vertex, &last_vertex, &weight);
        graph_add_edge(g, start_vertex, last_vertex, weight);
    }

    //call dfs
    dfs(START_VERTEX, g, curr_path, best_path);

    //path printing statements + conditions
    if (path_vertices(best_path) == 0) {
        fprintf(outfile, "No path found! Alissa is lost!\n");
    } else {
        fprintf(outfile, "Alissa starts at:\n");
        path_print(best_path, outfile, g);
        fprintf(outfile, "Total Distance:%u\n", path_distance(best_path));
    }

    //free graphs and dfs paths
    graph_free(&g);
    path_free(&curr_path);
    path_free(&best_path);

    //closing infile and outfile then returning 0
    if (infile != stdin) {
        fclose(infile);
    }

    fclose(outfile);

    return 0;
}
