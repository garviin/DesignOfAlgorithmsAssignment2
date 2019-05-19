/*
 * Problem 1 in Assignment 2
 * COMP20007 Design of Algorithms
 * Semester 1 2019
 *
 * Written by: [ YOUR NAME HERE ]
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RIGHT_MAX_HEAP 1
#define MAX_HEAP 0

// Function prototypes
int read_input_size();
int *read_input();
void build_max_heap(int* integers, int size, int isRightHeap);
void max_heapify(int* integers, int size, int parent, int isRightHeap);
void swap_node(int* a, int* b);
void print_array(int *integers, int size);

/* --- DO NOT CHANGE THE CODE BELOW THIS LINE --- */

void problem_1_a();
void problem_1_b();
void print_usage_and_exit(char **argv);

int main(int argc, char **argv) {
  if (argc != 2) {
    print_usage_and_exit(argv);
  }

  /* If the argument provided is "a" then run problem_1_a(),
   * run problem_1_b() for "b", and fail otherwise. */
  if (strcmp(argv[1], "a") == 0) {
    problem_1_a();
  } else if (strcmp(argv[1], "b") == 0) {
    problem_1_b();
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

/* TODO: Implement your solution to Problem 1.a. in this function. */
void problem_1_a() {
  int N = read_input_size();
  int *integers = read_input(N);
  build_max_heap(integers, N, MAX_HEAP);
  print_array(integers, N);
  free(integers);
}


/* TODO: Implement your solution to Problem 1.b. in this function. */
void problem_1_b() {
  int N = read_input_size();
  int *integers = read_input(N);
  build_max_heap(integers, N, RIGHT_MAX_HEAP);
  print_array(integers, N);
  free(integers);
}

/* Helper functions */

void build_max_heap(int* integers, int size, int isRightHeap){
  for(int i = (size)/2 - 1; i >= 0; i--){
    max_heapify(integers, size, i, isRightHeap);
  }
}

void max_heapify(int* integers, int size, int parent, int isRightHeap){
  // Initialize indexes for the current tree
  int largest_node = parent;
  int left_child = 2*parent + 1;
  int right_child = 2*parent + 2;

  // Getting largest element
  if(left_child < size && integers[left_child] > integers[parent]){
    largest_node = left_child;
  }
  if(right_child < size && integers[right_child] > integers[largest_node]){
    largest_node = right_child;
  }

  // swap with child if parent is not the largest
  if(largest_node !=  parent){
    swap_node(&integers[parent], &integers[largest_node]);
    max_heapify(integers, size, largest_node, isRightHeap);
  }

  // For creating right max heaps. Swaps the children if right child is smaller than the left.
  if(isRightHeap == RIGHT_MAX_HEAP &&
    right_child < size &&
    left_child < size &&
    integers[left_child] > integers[right_child]){
      swap_node(&integers[left_child], &integers[right_child]);
    }
}

// Function to swap values of two pointers
void swap_node(int *a, int *b){
  int temp = *a;
  *a = *b;
  *b = temp;
}

// Reads the input size
int read_input_size(){
  int N;
  scanf("%d", &N);
  return N;
}

// Reads N inputs, and returns a pointer array for the inputs
int *read_input(int N){
  // intialize pointer for an array of size N
  int *integers = (int *)malloc(N*sizeof(int));

  // Puts the input values in the array
  for (int i = 0; i < N; i++){
    scanf("%d", integers + i);
  }

  return integers;
}

// Prints an array of integers
void print_array(int *integers, int size){
  for (int i = 0; i < size; i++){
    printf("%d\n", *(integers + i));
  } 
}