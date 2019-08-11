#ifndef P2_H
#define P2_H

// Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>


// An edge stored by the source vertex, contains destination, and edge weight
typedef struct edge Edge;
struct edge{
    Edge *next;         // Pointer to the next edge
    int destination;    // Index of the vertex that the edge directs to
    int weight;         // Weight of the edge
};

// Each vertex stores an array of its edges, and its out degree
typedef struct vertex Vertex;
struct vertex{
    Edge *edges;      // An array of of edges
    int out_degree;   // The out degree of the vertex
};

// The path cost between a vertex to the source vertex. Also stores the previous vertex in the path, and number of edges. 
// This is used to create and distance matrix, and the index i of the array corresponds to the path cost from v0 to vi
typedef struct distance Distance;
struct distance{
    int cost;               // The cost of the path from v0 to this vertex
    int previous_vertex;    // The index of the previous vertex in the path
    int edge_count;         // How many edges are in the path
};


typedef struct edge2 Edge2;
struct edge2{
    int src;
    int destination;    // Index of the vertex that the edge directs to
    int weight;         // Weight of the edge
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
void find_shortest_path_k(Distance *distance, Vertex *vertices, int N, int k);
int min(int a, int b);


#endif


