#include "elevator.h"

int main(void){
  int floors; // f
  int start; // s
  int goal; // g
  int up; // u
  int down; // d

  // User input
  printf("Enter 5 integer values: f s g u d\n");
  if (!scanf("%d %d %d %d %d", &floors, &start, &goal, &up, &down)){
    fprintf(stderr, "Invalid input. Ensure there are 5 inputted integers separated by spaces and no extra spaces.");
    exit(1);
  }
  else {
    if (floors == 0 || floors > 100){
      fprintf(stderr, "Invalid f input. use the stairs\n");
      exit(1);
    }
    if (start < 1 || start > 100){
      fprintf(stderr, "Invalid s input. use the stairs\n");
      exit(1);
    }
    if (goal < 1 || goal > 100 || goal > floors){
      fprintf(stderr, "Invalid g input. use the stairs\n");
      exit(1);
    }
    if (up < 0 || up > floors){
      fprintf(stderr, "Invalid u input. use the stairs\n");
      exit(1);
    }
    if (down > 100 || down > floors){
      fprintf(stderr, "Invalid d input. use the stairs\n");
      exit(1);
    }
  }

  // Create graph
  Graph* graph = createGraph(floors, start, up, down);

  // Print graph
  //printGraph(graph);

  // Main algorithm
  bfs_shortest_path(graph, start, goal);
  
  return 0;
}
