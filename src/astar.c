#include <stdlib.h>
#include <stdio.h>
#include "../include/map.h"
#include "../include/graph.h"
#include "../include/heap.h"
#include "../include/hashtable.h"
#include "../include/queue.h"
#include "../include/astar.h"
#include "../include/heuristics.h"
#include "../include/stack.h"
#include "../include/util.h"

void getPath(list_node_p node, Stack *sequencia) {
  while(node->father) {
    push(sequencia, node->map->color);

    node = node->father;
  }
}

void heuristics(list_node_p openedNode) {
    int hr2 = (h3(openedNode->map) + h4(openedNode->map))*h1(openedNode->map);
    int hr3 = (h3(openedNode->map))*h6(openedNode->map);
    int hr4 = (h3(openedNode->map));

    if(hr2 > 0)
      openedNode->h = openedNode->vertex->h = hr2;
    else
      if(hr3 > 0)
        openedNode->h = openedNode->vertex->h = hr3;
      else 
        openedNode->h = openedNode->vertex->h = hr4;
}

list_node_p aStar(graph_p graph, Stack *sequencia) {
  //Inicializa openList e closedList e hash
  hashtable_p hash = newHashTable(SIZE, hashFunc);
  heap_p openList = initHeap();
  heap_p closedList = initHeap();
  int *pColor = (int *)malloc(sizeof(int));
  int i = 0;

  // OpenList recebe o primeiro nó do grafo
  graph->array[0].head->g = 0;
  graph->array[0].head->h = (h3(graph->array[0].head->map) + h4(graph->array[0].head->map))*h1(graph->array[0].head->map);
  graph->array[0].head->f = graph->array[0].head->g + graph->array[0].head->h;
  putQueue(hash, openList, graph->array[0].head);

  list_node_p openedNode = (list_node_p)malloc(sizeof(list_node_t));
  if(!openedNode)
      err_exit("Unable to create a new Node!");

  // Enquanto a openList não estiver vazia
  while(openList->size > 0) {

    // Remove o nodo com menor f(n) da openList
    openedNode = getQueue(hash, openList);

    //printf("Passo: %d\n", i);
    //printf("Cor: %d\n", openedNode->map->color);
    //printf("h(n): %d\n", openedNode->h);
    //printf("g(n): %d\n", openedNode->g);

    // Se o mapa tiver uma cor só, retorna
    if(oneColor(openedNode->map, pColor) == 1) {
      getPath(openedNode, sequencia);
      return openedNode;
    }

    //showcolorMap(openedNode->map);

    map_p auxMap = (map_p)malloc(sizeof(map_t));
    copyMap(auxMap, openedNode->map);

    // Insere o nodo na closedlist
    putQueue(hash, closedList, openedNode);

    // Adiciona os sucessores ao grafo
    putSucessors(graph, openedNode, openedNode->map);

    i++;
    list_node_p auxNode = (list_node_p)malloc(sizeof(list_node_t));
    auxNode = openedNode;
    while(auxNode->next) {
      auxNode->next->g = auxNode->next->vertex->g = openedNode->g+1;
      heuristics(auxNode->next);
      if(auxNode->next->h < 500 && isColor(auxNode->next->map) == *pColor)
        auxNode->next->h = 0;
      auxNode->next->f = auxNode->next->vertex->f = auxNode->next->g + auxNode->next->h;

      list_node_p old = searchNode(hash, openList, auxNode->next->vertex);
      if(old) { // node existe em openList
        if(old->g > auxNode->next->vertex->g) {
          old->father = auxNode->next->vertex->father;
          old->g = old->father->g+1;
          old->f = old->g + old->h;
          putQueue(hash, openList, old);
        }
      } else {
        old = searchNode(hash, closedList, auxNode->next->vertex);
        if(old) { // node existe em closedList
          if(old->g > auxNode->next->vertex->g) {
            old->father = auxNode->next->vertex->father;
            old->g = old->father->g+1;
            old->f = old->g + old->h;
            putQueue(hash, openList, old);
          }
        } else {
          putQueue(hash, openList, auxNode->next->vertex);
        }
      }

      auxNode = auxNode->next;
    }
  }
  
  return NULL;
}
