/*
 * Problem 3 in Assignment 2
 * COMP20007 Design of Algorithms
 * Semester 1 2019
 *
 * Written by: [ Garvin Prathama Bulkin]
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define START_INDEX 0 // Index of the first element in arrays

// Struct definition for a node in the binary tree
typedef struct node Node;
struct node{
  int data; // Contains the integer value of the node
  Node *left, *right; // Pointers to the left and right child of the node
};

// Function prototypes
int read_input_size();
Node *read_input(int N);
Node *new_node(int data);
Node *insert(Node *tree, int data);
int height(Node *tree);
int max(int a, int b);
int *get_sorted_array(Node *b_tree, int n);
void btree_to_array(Node *b_tree, int *array);
int count_nodes(Node *tree);
Node *get_balanced_tree(int *sorted_array, int start, int end);
void print_level_order(Node *tree);
void print_level(Node *node, int level);
int count_lines(Node *tree);
void count_level(Node *node, int level, int *k);
void free_tree(Node *node);
void print_answers(int node_count, Node *normal_tree, Node *balanced_tree);

int sorted_array_index = 0;

/* --- DO NOT CHANGE THE CODE BELOW THIS LINE --- */

void problem_3();

int main(int argc, char **argv) {
  problem_3();
  return 0;
}

/* --- DO NOT CHANGE THE CODE ABOVE THIS LINE --- */

/* TODO: Implement your solution to Problem 3 in this function. */
void problem_3(){
  // Reading input size
  int n = read_input_size();

  // Reading in the input straight into a binary tree
  Node *normal_tree = read_input(n);

  // Variable to store the number of nodes read into the tree
  int node_count = count_nodes(normal_tree);

  // An array that stores the integers in a sorted order
  int *sorted_int = get_sorted_array(normal_tree, node_count);

  // Creating a balanced tree from the sorted array of integers
  Node *balanced_tree = get_balanced_tree(sorted_int, START_INDEX, node_count-1);

  // Prints answers in required format
  print_answers(node_count, normal_tree, balanced_tree);

  // Frees the trees used
  free_tree(normal_tree);
  free_tree(balanced_tree);
}

// Reads the input size n and returns it
int read_input_size(){
  int N;
  scanf("%d", &N);
  return N;
}

// Reads the input integers, inserts it to a binary tree, and returns the root of the tree
Node *read_input(int N){
  // Temporary variable to hold integer
  int tmp;
  scanf("%d", &tmp);
  // Tree intially empty
  Node *tree = NULL;

  //Reads the first input, insert into empty tree
  tree = insert(tree, tmp);
  
  // Reads in the remaining inputs and insert it into the tree
  int i;
  for(i = 1; i <= N; i++){
    scanf("%d", &tmp);
    insert(tree, tmp);
  }

  // Return a normal tree
  return tree;
}

// Takes in an integer n and returns a binary tree node with the data n
Node *new_node(int data){
  Node *node = malloc(sizeof(Node));
  assert(node);
  node->data = data;

  // Initially no children
  node->left = node->right = NULL;
  return node;
}

// A recursive functon that inserts an integer into a bintary tree and returns the root of the tree
Node *insert(Node *tree, int data){
  // Create new leaf node
  if(tree == NULL){
    return new_node(data);
  }

  // Assign it to right child when integer is larger than root node
  if(data > tree->data){
    tree->right = insert(tree->right, data);
  } 
  // Assign it to left child otherwise
  else if(data < tree->data){
    tree->left = insert(tree->left, data);
  }

  // When element already exists in tree, no insert is done
  return tree;
}

// Function to find the height of a tree
int height(Node *tree){
  if(tree == NULL){
    return 0;
  }

  // Recursive call to measure the height of left and right subtree
  int left_height = height(tree->left) + 1;
  int right_height = height(tree->right) + 1;

  // Return the largest height from left and right subtree
  return max(left_height, right_height);
}

// Helper function that takes in two integers and returns the largest one
int max(int a, int b){
  if (a > b){
    return a;
  }
  return b;
}

// Function that takes in a binary search tree and returns a sorted array
int *get_sorted_array(Node *b_tree, int n){
  int *sorted = malloc(sizeof(int) * n);
  btree_to_array(b_tree, sorted);

  return sorted;
}

// Function that takes in an array pointer and a binary search tree. Assigns array to integers in an increasing order
void btree_to_array(Node *b_tree, int *array){
  if(!b_tree){
    return;
  }
  // In-order traversal of binary search tree
  btree_to_array(b_tree->left, array);
  array[sorted_array_index++] = b_tree->data;
  btree_to_array(b_tree->right, array);
}

// Counts the number of nodes
int count_nodes(Node *tree){
  // Counting called node itself
  int nodes = 1;

  // When it reaches the end of the tree
  if(tree == NULL){
    return 0;
  } 
  // Recursive call to count nodes in each subtree
  else{
    nodes += count_nodes(tree->left);
    nodes += count_nodes(tree->right);
    return nodes;
  }
}

// Function takes in a sorted integer array and returns 
Node *get_balanced_tree(int *sorted_array, int start, int end){
  // Terminates when start index is greater than end index
  if (start > end){
    return NULL;
  }

  // The index for the middle element in the array
  int mid = (start + end)/2;

  // Create new node to insert into tree
  Node *node = new_node(sorted_array[mid]);

  // Assign the child nodes as the return value of a recursive call to the left and right half of the array
  node->left = get_balanced_tree(sorted_array, start, mid - 1);
  node->right = get_balanced_tree(sorted_array, mid + 1, end);

  // Returns the root of the tree
  return node;
}

// Prints a binary search tree in level order
void print_level_order(Node *tree){
  int tree_height = height(tree);

  // Prints each level using print_level() function
  int i;
  for(i = 0; i <= tree_height; i++){
    print_level(tree, i);
  }
}

// Prints a given level of a binary search tree
void print_level(Node *node, int level){
  // If node is NULL, subtree does not have a child, prints "-1"
  if(!node){
    printf("-1\n");
    return;
  }
  // Prints the nodes using level order traversal
  if(level == 1){
    printf("%d\n", node->data);
  } else if(level > 1){
    print_level(node->left, level-1);  
    print_level(node->right, level-1); 
  }
}

// Returns the number of lines required to print a tree in the required formal
int count_lines(Node *tree){
  int tree_height = height(tree);
  int k = 0;
  // Counts number of lines for each level using count_level()
  int i;
  for(i = 0; i <= tree_height; i++){
    count_level(tree, i, &k);
  }
  return k;
}

// Counts number of lines needed to print the tree at a given level
void count_level(Node *node, int level, int *k){
  if(!node){
    (*k)++;
    return;
  }
  // Counts using level order traversal
  if(level == 1){
    (*k)++;
  } else if(level > 1){
    count_level(node->left, level-1, k);  
    count_level(node->right, level-1, k); 
  }
}

// Frees the memory of a binary search tree
void free_tree(Node *node){
  if(!node){
    return;
  }
  // Freeing tree in postorder traversal
  free_tree(node->left);
  free_tree(node->right);
  free(node);
}

// Function prints the answers in the required format
void print_answers(int node_count, Node *normal_tree, Node *balanced_tree){
  // Prints number of nodes, height of unbalanced tree, and lines required to output the balanced tree
  printf("%d\n%d\n%d\n", node_count, height(normal_tree), count_lines(balanced_tree));
  // Prints the balanced tree in level order
  print_level_order(balanced_tree);
}