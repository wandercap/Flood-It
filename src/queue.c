#include <stdlib.h>
#include <stdio.h>
#include "../include/graph.h"
#include "../include/heap.h"
#include "../include/hashtable.h"
#include "../include/util.h"
#include "../include/queue.h"

// Adiciona item na queue 
void putQueue(hashtable_p hash, heap_p heap, list_node_p node) { 
  htNode_p newNode = putHashNode(hash, node->f, node);
  insertHeapNode(heap, node->f, newNode);
}

list_node_p getQueue(hashtable_p hash, heap_p heap) {

  htNode_p node = heap->elem[0].hashNode;

  removeHeapNode(heap);

  return node->graphNode;
}

void removeQueue(heap_p heap, list_node_p node){
  int ind = -1;

  search(heap, node, 0, &ind);

  if(ind != -1){
    heap->size--;
    heap->elem[ind] = heap->elem[heap->size]; // Substitui nodo removido com o nodo mais fundo a direita
    heap->elem = (node_p)realloc(heap->elem, heap->size*sizeof(node_t));
    if(!heap->elem)
      err_exit("Unable to reallocate the Heap Element!");

    heapify(heap, 0);

  }else{
    err_exit("Node doesn't exist!");

    return;
  }
};

list_node_p searchNode(hashtable_p hash, heap_p heap, list_node_p node) {
  int ind =-1;

  search(heap,node,0, &ind);
    
  if(ind!=-1)
    return getHashNode(hash, heap->elem[ind].f, node->map->color);

  else
    return NULL;
}

void search(heap_p heap,list_node_p node, int i, int *ind){
  if (heap->elem[i].f == node->f){
    *ind = i;
    return ;
  }

  if((LCHILD(i)<heap->size) && (heap->elem[LCHILD(i)].f <= node->f))
    search(heap,node,LCHILD(i),ind);

  if((RCHILD(i)<heap->size) && (heap->elem[RCHILD(i)].f <= node->f))
    search(heap,node,RCHILD(i),ind);

  return ;
}

