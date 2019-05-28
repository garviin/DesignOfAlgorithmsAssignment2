#ifndef P2_H
#define P2_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>


// An edge stored by the source vertex, contains destination, and edge weight
typedef struct edge Edge;
struct edge{
    Edge *next;
    int destination;
    int weight;
};

// Each vertex stores an adjacency list, and its out degree
typedef struct vertex Vertex;
struct vertex{
    Edge *edges;
    int out_degree;
};

// The path cost between a vertex to the source vertex. Also stores the previous vertex in the path, and number of edges. 
typedef struct distance Distance;
struct distance{
    int cost;
    int previous_vertex;
    int edge_count;
};


Vertex *read_vertices(int N);
int read_vertex_size();
void print_vertices(Vertex *vertices, int N);
Distance *initialize_distance_array(int N);
void find_shortest_path(Distance *distance, Vertex *vertices, int N);
void print_path(Distance *distance_array, int vertex_count);
void free_edge(Edge *edge);
void free_edges(Edge *edges, int size);
void free_vertex_array(Vertex *vertices, int size);
Edge *new_edge();
int path_exist(int path_cost);
void print_answers(Distance *distance_array, int N);

#endif


