#include "elevator.h"

Graph* createGraph(int floors, int start, int up, int down)
{
  Graph* graph = (Graph*)malloc(sizeof(Graph));
  if (graph == NULL){
    fprintf(stderr, "Malloc failure.");
    exit(1);
  }
  graph->size = floors;

  graph->visited = malloc(graph->size * sizeof(int));
  if (graph->visited == NULL){
    fprintf(stderr, "Malloc failure.");
    exit(1);
  }

  graph->nodes = (GraphNode**)malloc(graph->size * sizeof(GraphNode*));
  if (graph->nodes == NULL){
    fprintf(stderr, "Malloc failure.");
    exit(1);
  }

  for (int i = 0; i < floors; i++){
    GraphNode* newNode = (GraphNode*)malloc(sizeof(GraphNode));
    graph->nodes[i] = newNode;
    if (newNode == NULL){
      fprintf(stderr, "Malloc failure.");
      exit(1);
    }
    graph->visited[i] = 0;
    graph->nodes[i]->head = NULL;
    graph->nodes[i]->next = NULL;
    graph->nodes[i]->floor = i + 1;
    graph->nodes[i]->prev_visited = NULL;
  }

  for (int i = 0; i < floors; i++){
    if (i + 1 + up <= floors){
      GraphNode* adjUpNode = (GraphNode*)malloc(sizeof(GraphNode));
      if (adjUpNode == NULL){
        fprintf(stderr, "Malloc failure.");
        exit(1);
      }
      adjUpNode->floor = i + 1 + up;
      graph->nodes[i]->head = adjUpNode;
      graph->nodes[i]->next = NULL;
      adjUpNode->next = NULL;
      adjUpNode->prev_visited = NULL;
    } 
    else {
      break;
    }
  }

  for (int i = floors-1; i >= 0; i--){
    if (i - down >= 0){
      GraphNode* adjDownNode = (GraphNode*)malloc(sizeof(GraphNode));
      if (adjDownNode == NULL){
        fprintf(stderr, "Malloc failure.");
        exit(1);
      }
      adjDownNode->floor = i + 1 - down;
      adjDownNode->prev_visited = NULL;
      GraphNode* temp = graph->nodes[i]->head;
      graph->nodes[i]->head = adjDownNode;
      graph->nodes[i]->next = NULL;
      graph->nodes[i]->head->next = temp;
    } 
    else {
      break;
    }
  }
  
  return graph;
}

void printGraph(Graph* graph) {
  int v;
  for (v = 0; v < graph->size; v++) {
    GraphNode* temp = graph->nodes[v]->head;
    printf("\n Adjacency list of floor %d\n ", v + 1);
    while (temp) {
      printf("%d -> ", temp->floor);
      temp = temp->next;
    }
    printf("\n");
  }
}

Queue* createQueue(Graph* graph) {
  Queue* q = (Queue*)malloc(sizeof(Queue));
  if (q == NULL){
    fprintf(stderr, "Malloc failure.");
    exit(1);
  }
  q->items = malloc(sizeof(int)*graph->size);
  if (q->items == NULL){
    fprintf(stderr, "Malloc failure.");
    exit(1);
  }
  q->front = -1;
  q->rear = -1;
  return q;
}

int isEmpty(Queue* q) {
  if (q->rear == -1)
    return 1;
  else
    return 0;
}

void enqueue(Queue* q, int value, int size) {
  if (q->rear == size - 1)
    printf("\nQueue is Full!!");
  else {
    if (q->front == -1)
      q->front = 0;
    q->rear++;
    q->items[q->rear] = value;
  }
}

int dequeue(Queue* q) {
  int item;
  if (isEmpty(q)) {
    //printf("Queue is empty");
    item = -1;
  } else {
    item = q->items[q->front];
    q->front++;
    if (q->front > q->rear) {
      //printf("Resetting queue ");
      q->front = q->rear = -1;
    }
  }
  return item;
}

// Custom BFS shortest path algorithm (Similar to Dijkstra's algorithm)
void bfs_shortest_path(Graph* graph, int start, int goal) {
  // check if empty
  if (!graph->size){
    fprintf(stderr, "Graph empty.\n");
    exit(1);
  }
  if (graph->size < 1){
    fprintf(stderr, "Graph empty.\n");
    exit(1);
  }

  Queue* q = createQueue(graph);

  graph->visited[start-1] = 1;
  enqueue(q, start-1, graph->size);

  while (!isEmpty(q)) {
    int current = dequeue(q);
    
    if (current == goal - 1){
      GraphNode* current_prev = graph->nodes[current];
      int length = 0;

      // count length of path
      while (current_prev){
        length++;
        current_prev = current_prev->prev_visited;
      }

      // create array of correct length
      int* pathArr = malloc(sizeof(int)*length);

      // restart from current_prev and put in array from end index to start index
      int index = length-1;
      current_prev = graph->nodes[current];

      while (current_prev){
        pathArr[index] = current_prev->floor;
        current_prev = current_prev->prev_visited;
        index--;
      }

      // go through array and print out with arrows separating and then exit(0)
      for (int i = 0; i < length; i++){
        if (i < length - 1){
          printf("%d -> ", pathArr[i]);
        }
        else {
          printf("%d\n", pathArr[i]);
        }
      }
      exit(0);
    }

    GraphNode* temp = graph->nodes[current]->head;

    while (temp) {
      int adjVertex = temp->floor;

      if (graph->visited[adjVertex-1] == 0) { // unvisited
        graph->visited[adjVertex-1] = 1; // visited
        enqueue(q, adjVertex-1, graph->size);
        graph->nodes[adjVertex-1]->prev_visited = graph->nodes[current]; // set node being enqueued's prev visited to node that was dequeued
      }
      temp = temp->next;
    }
  }
  printf("use the stairs\n");
  exit(0);
}
