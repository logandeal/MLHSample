#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <limits.h>

typedef struct GraphNode {
  struct GraphNode *head; // pointer to head (from main node)
  struct GraphNode *next; // pointer to next (from head node)
  struct GraphNode *prev_visited; // pointer to next (from head node)
  int floor;
} GraphNode;

typedef struct Graph {
  GraphNode** nodes; // array of pointers to Node to represent an adjacency list
  int* visited;
  int size;
} Graph;

typedef struct Queue {
  int* items;
  int front;
  int rear;
} Queue;

Graph* createGraph(int floors, int start, int up, int down);
void printGraph(Graph* graph);
Queue* createQueue(Graph* graph);
void enqueue(Queue* q, int value, int size);
int dequeue(Queue* q);
void bfs_shortest_path(Graph* graph, int start, int goal);
