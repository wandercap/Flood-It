#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "map.h"

typedef struct list_node {
  map_p map;
  struct list_node *vertex;
  struct list_node *next;
  struct list_node *father;
  int f, g, h;
} list_node_t, *list_node_p;

typedef struct list {
  int length;
  list_node_t *head;
} list_t, *list_p;

typedef struct graph {
  int vertices;
  list_p array;
} graph_t, *graph_p;

void putSucessors(graph_p graph, list_node_p node, map_p map);
graph_p splitMap(map_p map);
list_node_p createNode(map_p map);
list_node_p createVertice(graph_p graph);
graph_p createGraph(int n);
void destroyGraph(graph_p graph);
void addEdge(graph_p graph, list_node_p src, list_node_p dest, int index);
void printGraph(graph_p graph);

#endif
