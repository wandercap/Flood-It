#include <stdio.h>
#include <stdlib.h>
#include "../include/heap.h"
#include "../include/hashtable.h"
#include "../include/util.h"

heap_p initHeap() {
  heap_p heap = (heap_p)malloc(sizeof(heap_t));
  if(!heap)
    err_exit("Unable to create a new Heap!");

  heap->size = 0;

  return heap;
}

void insertHeapNode(heap_p heap, int f, htNode_p hashNode) {
  if(!heap)
    err_exit("The Heap is empty!");

  if(heap->size > 0) {
    heap->elem = (node_p)realloc(heap->elem, (heap->size+1)*sizeof(node_t));
    if(!heap->elem)
      err_exit("Unable to reallocate the Heap Elements!");

  } else {
    heap->elem = (node_p)malloc(sizeof(node_t));
    if(!heap->elem)
      err_exit("Unable to create a Heap Element!");
  }

  node_t newNode;
  newNode.f = f;
  newNode.hashNode = hashNode;

  int i = (heap->size)++;
  while(i && newNode.f < heap->elem[PARENT(i)].f) { 
    heap->elem[i] = heap->elem[PARENT(i)];
    i = PARENT(i);
  }

  heap->elem[i] = newNode;
}

void swap(node_p n1, node_p n2) {
  if(!n1)
    err_exit("Node 1 is empty!");

  if(!n2)
    err_exit("Node 2 is empty!");

  node_t tmp = *n1;
  *n1 = *n2;
  *n2 = tmp;
}

void heapify(heap_p heap, int i) {
  if(!heap)
    err_exit("The Heap is empty!");

  int smallest; //smallest
  if(LCHILD(i) < heap->size && heap->elem[LCHILD(i)].f < heap->elem[i].f) {
    smallest = LCHILD(i);

  } else {
    smallest = i;
  }

  if(RCHILD(i) < heap->size && heap->elem[RCHILD(i)].f < heap->elem[smallest].f) {
    smallest = RCHILD(i);
  }

  if(smallest != i) {
    swap(&(heap->elem[i]), &(heap->elem[smallest]));
    heapify(heap, smallest);
  }
}

void removeHeapNode(heap_p heap) {
  if(!heap)
    err_exit("The Heap is empty!");

  if(heap->size > 1) {

    heap->elem[0] = heap->elem[heap->size-1];
    heap->size --;
    heap->elem = (node_p)realloc(heap->elem, heap->size*sizeof(node_t));
    if(!heap->elem)
      err_exit("Unable to reallocate the Heap Elements!");

    heapify(heap, 0);

  } else {
    free(heap->elem);
    heap->size--;
  }
}

void newHeap(heap_p heap, int *array, int size) {
  if(!heap)
    err_exit("The Heap is empty!");

  int i;
  for(i=0; i<size; i++) {
    if(heap->size) {
      heap->elem = (node_p)realloc(heap->elem, (heap->size+1)*sizeof(node_t));
      if(!heap->elem)
        err_exit("Unable to reallocate the Heap Elements!");

    } else {
      heap->elem = (node_p)malloc(sizeof(node_t));
      if(!heap->elem)
        err_exit("Unable to create a Heap Element!");
    }

    node_t newNode;
    newNode.f = array[i];
    heap->elem[(heap->size)++] = newNode;
  }

  for(i=(heap->size-1)/2; i>=0; i--) {
    heapify(heap, i);
  }
}

void inOrder(heap_p heap, int i) {
  if(!heap)
    err_exit("The Heap is empty!");

  if(LCHILD(i) < heap->size) {
    inOrder(heap, LCHILD(i));
  }

  printf("%d ", heap->elem[i].f);
  if(RCHILD(i) < heap->size) {
    inOrder(heap, RCHILD(i));
  }
}

void preOrder(heap_p heap, int i) {
  if(!heap)
    err_exit("The Heap is empty!");

  if(LCHILD(i) < heap->size) {
    preOrder(heap, LCHILD(i));
  }

  if(RCHILD(i) < heap->size) {
    preOrder(heap, RCHILD(i));
  }

  printf("%d ", heap->elem[i].f);
}

void postOrder(heap_p heap, int i) {
  if(!heap)
    err_exit("The Heap is empty!");

  printf("%d ", heap->elem[i].f);
  if(LCHILD(i) < heap->size) {
    preOrder(heap, LCHILD(i));
  }
  
  if(RCHILD(i) < heap->size) {
    preOrder(heap, RCHILD(i));
  }
}

void levelOrder(heap_p heap) {
  if(!heap)
    err_exit("The Heap is empty!");

  int i;
  for(i=0; i<heap->size; i++) {
    printf("%d ", heap->elem[i].f);
  }
}
