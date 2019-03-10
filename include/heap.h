#ifndef _HEAP_H_
#define _HEAP_H_

#include "hashtable.h"

#define LCHILD(x) 2*x+1
#define RCHILD(x) 2*x+2
#define PARENT(x) (x-1)/2

typedef struct node {
  int f;
  htNode_p hashNode;
} node_t, *node_p;

typedef struct heap {
  int size;
  node_p elem;
} heap_t, *heap_p;

heap_p initHeap();
void insertHeapNode(heap_p heap, int f, htNode_p hashNode);
void swap(node_p n1, node_p n2);
void heapify(heap_p heap, int i);
void removeHeapNode(heap_p heap);
void newHeap(heap_p heap, int *array, int size);
void inOrder(heap_p heap, int i);
void preOrder(heap_p heap, int i);
void postOrder(heap_p heap, int i);
void levelOrder(heap_p heap);

#endif
