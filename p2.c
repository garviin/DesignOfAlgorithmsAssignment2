/*
 * Problem 2 in Assignment 2
 * COMP20007 Design of Algorithms
 * Semester 1 2019
 *
 * Written by: [ Garvin Prathama Bulkin ]
 */

#include "p2.h"
#define INFINITY 2000000000

/* --- DO NOT CHANGE THE CODE BELOW THIS LINE --- */

void problem_2_a();
void problem_2_b();
void print_usage_and_exit(char **argv);

int main(int argc, char **argv) {
  if (argc != 2) {
    print_usage_and_exit(argv);
  }

  /* If the argument provided is "a" then run problem_2_a(),
   * run problem_2_b() for "b", and fail otherwise. */
  if (strcmp(argv[1], "a") == 0) {
    problem_2_a();
  } else if (strcmp(argv[1], "b") == 0) {
    problem_2_b();
  } else {
    print_usage_and_exit(argv);
  }

  return 0;
}

/* Print the usage information and exit the program. */
void print_usage_and_exit(char **argv) {
  fprintf(stderr, "usage: %s [ab]\n", argv[0]);
  exit(EXIT_FAILURE);
}

/* --- DO NOT CHANGE THE CODE ABOVE THIS LINE --- */

/* TODO: Implement your solution to Problem 2.a. in this function. */
void problem_2_a() {
  // Reads input data
  int N = read_vertex_size();
  Vertex *vertices = read_vertices(N);
  
  // Get the shortest path
  Distance *distance_array = initialize_distance_array(N);
  find_shortest_path(distance_array, vertices, N);
  int shortest_path_cost = (distance_array+ N-1)->cost;
  
  // Checks if path exists
  path_exist(shortest_path_cost);

  // Prints the results in the required format
  print_answers(distance_array, N);
  
  // Freeing memory
  free(distance_array);
  free_vertex_array(vertices, N);
}

/* TODO: Implement your solution to Problem 2.b. in this function. */
void problem_2_b() {
  // Reads input data
  int N, k;
  scanf("%d %d", &N, &k);
  Vertex *vertices = read_vertices(N);
  
  // Get the shortest path
  Distance *distance_array = initialize_distance_array(N);
  find_shortest_path_k(distance_array, vertices, N, k);
  int shortest_path_cost = (distance_array+ N-1)->cost;
  
  // Checks if path exists
  path_exist(shortest_path_cost);

  // Prints the results in the required format
  print_answers(distance_array, N);
  
  // Freeing memory
  free(distance_array);
  free_vertex_array(vertices, N);
}

// Reads the number of vertices
int read_vertex_size(){
  int N;
  scanf("%d", &N);
  return N;
}

// Reads N vertices and its edges. Returns an array of Vertices containing all of the edges.
Vertex *read_vertices(int N){
  // intialize pointer for a Vertex array of size N
  Vertex *vertices = (Vertex *)malloc(N*sizeof(Vertex));

  // Puts the input values in the array
  int i;
  for(i = 0; i < N; i++){
    // Puts all of the edges in the vertex struct
    scanf("%d", &(vertices +i)->out_degree);
    Edge *next = NULL;
    int k;
    for (k = 0; k < (vertices +i)->out_degree; k++){
      // Initialize a new edge
      Edge *edge = new_edge();

      // Read input data
      scanf("%d %d", &edge->destination, &edge->weight);

      // Set pointer values for the edge
      if(next == NULL){
        (vertices +i)->edges = edge;
      } else {
        next->next = edge;
      }
      next = edge;
    }
  }
  
  // Returns an array of N vertices containing all of its edges
  return vertices;
}

// Initialize a new edge
Edge *new_edge(){
  Edge *edge = malloc(sizeof *edge);
  assert(edge);
  edge->next = NULL;
	return edge;
}

// Frees an edge pointer
void free_edge(Edge *edge){
  assert(edge);
  free(edge);
}

// Frees an adjacency list
void free_edges(Edge *edges, int size){
  Edge *edge = edges;
  Edge *next;
  // Iterates through the linked list of edges
  while(edge != NULL){
    next = edge->next;
    free(edge);
    edge = next;
	}
}

// Frees the array all of the adjacency list in an array of vertices 
void free_vertex_array(Vertex *vertices, int size){
  assert(vertices);

  // Loop through each vertex and free the list of edges
  int i;
  for(i = 0; i < size; i++){
    free_edges((vertices+i)->edges, (vertices+i)->out_degree);
  }
  free(vertices);
}

// Initializes an array of distances, the index of the array is also the vertex index.
Distance *initialize_distance_array(int N){
  // Memory allocation
  Distance *distance_array = malloc(sizeof(Distance) * N);
  
  // Assigns values for vertex 0
  distance_array->cost = 0;
  distance_array->previous_vertex = -1;
  distance_array->edge_count = 0;
  
  // Assigns values for remaining vertices
  int i;
  for(i = 1; i < N; i++){
    (distance_array+i)->cost = INFINITY;
    (distance_array+i)->previous_vertex = -1;
  }
  
  // Return the array created
  return distance_array;
}

Distance **initialize_distance_array_k(int N, int k){
  Distance **distance_k = (Distance **)malloc(20 * sizeof(Distance*));
  int i;
  for (i = 0; i < k; ++i){
    distance_k[i] = initialize_distance_array(N);
  }
  return distance_k;
}

// Finds the shortest path for a topologically sorted array of vertices of size N
void find_shortest_path(Distance *distance, Vertex *vertices, int N){
  // Loop through all the vertices starting from 0
  int i;
  for(i = 0; i < N; i++){
    Vertex *current_vertex = vertices + i;

    // Iterate through each edge and updates the distance array
    Edge *current_edge = (current_vertex->edges);
    int j;
    for(j = 0 ; j < current_vertex->out_degree; j++){
      // The distance from the source vertex to the destination of the edge
      Distance *destination = distance + current_edge->destination;
      // The distance from the source vertex tot the origin of the edge
      Distance *origin = distance + i;

      // Updates the distance array based on the edge weights
      if(destination->cost > origin->cost + current_edge->weight){
        destination->cost = origin->cost + current_edge->weight;
        // Storing the index of the origin vertex of the edge
        destination->previous_vertex = i;
        // Dynamically update the number of edges for the path
        destination->edge_count = origin->edge_count + 1;
      }
      // Updates the pointer to move on to the next edge 
      if(current_edge != NULL){
        current_edge = current_edge->next;
      }
    }
  }
}

void find_shortest_path_k(Distance *distance, Vertex *vertices, int N, int k){
  // Loop through all the vertices starting from 0
  // while path exist && path lenght < k
  int i;
  for(i = 0; i < N+1; i++){
    Vertex *current_vertex = vertices + i;
    // Iterate through each edge and updates the distance array
    Edge *current_edge = (current_vertex->edges);
    int j;
    for(j = 0 ; j < current_vertex->out_degree; j++){
      // The distance from the source vertex to the destination of the edge
      Distance *destination = distance + current_edge->destination;
      // The distance from the source vertex tot the origin of the edge
      Distance *origin = distance + i;

      // Updates the distance array based on the edge weights
      // Only update when the edge_count is less than k
      if(origin->edge_count + 1 <= k){
        if((destination->cost > origin->cost + current_edge->weight)){
          destination->cost = origin->cost + current_edge->weight;
          // Storing the index of the origin vertex of the edge
          destination->previous_vertex = i;
          // Dynamically update the number of edges for the path
          destination->edge_count = origin->edge_count + 1;
        }
      }
      // Updates the pointer to move on to the next edge 
      if(current_edge != NULL){
        current_edge = current_edge->next;
      }
    }
  }
}

// Prints the vertices in the path from the source vertex to the nth vertex
void print_path(Distance *distance_array, int vertex_count){
  // Get the distance information of the last vertex
  Distance *last_vertex = distance_array + vertex_count - 1;
  int edge_count = last_vertex->edge_count;

  // Initialize an array to store the vertices in the path
  int *path_array= malloc(sizeof(int) * edge_count+1);
  assert(path_array);

  // Traverse through the distance array to get all the vertices in the path
  path_array[0] = vertex_count - 1;
  Distance *current_vertex = last_vertex;
  int i;
  for(i = 1; i < edge_count; i++){
    path_array[i] = current_vertex->previous_vertex;
    current_vertex = distance_array + path_array[i];
  }

  // Traverse through the path array in reverse order to get all of the vertices in the path starting from source
  for(i = edge_count; i >= 0; i--){
    printf("%d\n", path_array[i]);
  }

  // Frees the path array
  free(path_array);
}

// Outputs the results
void print_answers(Distance *distance_array, int N){
  Distance *to_last_vertex = distance_array + N-1;
  
  // Prints path cost and number of edges
  printf("%d\n%d\n", to_last_vertex->cost, to_last_vertex->edge_count);

  // Prints all vertices in the path
  print_path(distance_array, N);
}

// Checks if path exists depending on path cost
int path_exist(int path_cost){
  // When path cost is infinite, there is no path
  if (path_cost == INFINITY){
    printf("No Path");
    exit(EXIT_SUCCESS);
  }
  return 1;
}

// Checks if path exists depending on path cost
int path_exist_k(int path_cost){
  // When path cost is infinite, there is no path
  if (path_cost == INFINITY){
    return 0;
  }
  return 1;
}

int min(int a, int b){
  if (a < b){
    return a;
  }
  return b;
}