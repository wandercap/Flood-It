#include <stdio.h>
#include <stdlib.h>
#include "../include/graph.h"
#include "../include/map.h"
#include "../include/util.h"

void putSucessors(graph_p graph, list_node_p node, map_p map) {
  int i, color;

  color = 0;

  for(i=1; i<=node->map->ncolors; i++) {  // Adiciona os sucessores do nodo no grafo
    list_node_p newSucessor = createVertice(graph); // Cria um novo vertice

    newSucessor->father = node;

    if(map->map[0][0] == i) {
      color = i+1;
    } else {
      if(color == i) {
        color++;
      } else {
        color = i;
      }
    }

    copyMap(newSucessor->map, map); // Copia o mapa do nodo atual para o filho

    mapPaint(newSucessor->map, color); // Pinta o mapa com a cor;

    addEdge(graph, node, newSucessor, i-1);  // Adiciona a aresta entre os vertices 

  }
}

list_node_p createNode(map_p map) {
  list_node_p node = (list_node_p)malloc(sizeof(list_node_t));
  if(!node)
    err_exit("Unable to create a new Node!");

  if(map) {
    node->map = map;
  } else {
    node->map = (map_p)malloc(sizeof(map_t));
    if(!node->map)
      err_exit("Unable to create a new Node Map!");
  }
  node->next = NULL;

  return node;
}

list_node_p createVertice(graph_p graph) {
  graph->vertices++;

  graph->array = (list_p)realloc(graph->array, (graph->vertices)*sizeof(list_t));
  if(!graph->array)
    err_exit("Unable to realloc the Graph!");

  list_node_p newNode = createNode(NULL);

  graph->array[graph->vertices-1].head = newNode;
  graph->array[graph->vertices-1].length = 0;

  return graph->array[graph->vertices-1].head;
}

void addEdge(graph_p graph, list_node_p src, list_node_p dest, int index) {

  list_node_p node = createNode(dest->map);
  
  list_node_p aux = src;
  
  while(aux->next) {
    aux = aux->next;
  }

  aux->next = node;
  aux->next->vertex = dest;
  aux->next->vertex->father = src;
  aux->next->father = aux;

  graph->array[(graph->vertices)-(src->map->ncolors-1)-index].length++;
  
}

graph_p createGraph(int n) {
  int i;

  graph_p graph = (graph_p)malloc(sizeof(graph_t));
  if(!graph)
    err_exit("Unable to create a new Graph!");

  graph->vertices = n;

  graph->array = (list_p)malloc(n*sizeof(list_t));
  if(!graph->array)
    err_exit("Unable to create a new Array!");

  for(i=0; i<n; i++) {
    graph->array[i].head = NULL;
    graph->array[i].length = 0;
  }

  return graph;
}

void destroyGraph(graph_p graph) {
  if(graph) {
    if(graph->array) {
      int v;
    
      for(v=0; v<graph->vertices; v++) {
        list_node_p listPtr = graph->array[v].head;

        while(listPtr) {
          list_node_p tmp = listPtr;
          listPtr = listPtr->next;
          free(tmp);
        }

      }

      free(graph->array);
    }

    free(graph);
  } else {
    err_exit("The Graph is empty!");
  }

}

void printGraph(graph_p graph) {
  if(!graph)
    err_exit("The Graph is empty!");

  int i;

  for(i=0; i<graph->vertices; i++) {
    list_node_p listPtr = graph->array[i].head;
    printf("\nVertice %d: head->", i);
  
    while(listPtr) {
      showcolorMap(listPtr->map);
      listPtr = listPtr->next;
      printf("->");
    }
    
    printf("NULL\n");
  }
}
