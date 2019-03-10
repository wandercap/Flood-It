#ifndef HASHTABLE_H
#define HASHTABLE_H

#define SIZE 100

#include "graph.h"

typedef struct htNode {
  int key;
  list_node_p graphNode;
  struct htNode *left, *right;
} htNode_t, *htNode_p;

typedef struct hashtable {
  int size;
  int (*func)(int key);
  int count;
  htNode_t **buckets;
} hashtable_t, *hashtable_p;


int hashFunc(int key);
hashtable_p newHashTable(int size, int (*func)(int key));
htNode_p putHashNode(hashtable_p hash, int key, list_node_p graphNode);
void *getHashNode(hashtable_p hash, int key, int color);
void clearHashTable(hashtable_p hash);
int countHashTable(hashtable_p hash);

#endif