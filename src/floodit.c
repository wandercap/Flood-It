#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "../include/map.h"
#include "../include/graph.h"
#include "../include/heap.h"
#include "../include/hashtable.h"
#include "../include/astar.h"
#include "../include/stack.h"
#include "../include/util.h"

int main(int argc, char **argv) {
  map_p map = (map_p)malloc(sizeof(map_t));
  if(!map)
    err_exit("Unable to create a new Map!");

  /********************************/
  // Ler Instância
  /**/
  if(argc != 2) {
    printf("uso: %s <arquivo instancia>\n", argv[0]);
    exit(1);
  }

  readMap(argv[1], map);
  /********************************/

  /********************************/
  // Gerar Mapa Aleatório
  /**
  int seed;
  map->nlines = atoi(argv[1]);
  map->ncolumns = atoi(argv[2]);
  map->ncolors = atoi(argv[3]);

  if(argc == 5)
     seed = atoi(argv[4]);
  else
     seed = -1;

  newMap(map, seed);
  ********************************/

  showcolorMap(map);

  graph_p graph = createGraph(1);

  list_node_p newNode = createNode(map);
  graph->array[0].head = newNode;

  Stack *sequencia = initStack();

  list_node_p resultNode = aStar(graph, sequencia);

  showcolorMap(resultNode->map);

  printStack(sequencia);

  return 0;
}
