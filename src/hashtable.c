#include <stdio.h>
#include <stdlib.h>
#include "../include/hashtable.h"
#include "../include/graph.h"
#include "../include/util.h"

int hashFunc(int key) {
  return key % SIZE;
}

hashtable_p newHashTable(int size, int (*func)(int key)) {
  hashtable_p hash = (hashtable_p)malloc(sizeof(hashtable_t));
  if(!hash)
    err_exit("Unable to create a new Hashtable!");

  hash->size = size;
  hash->func = func;

  hash->buckets = (htNode_p*)calloc(size, sizeof(htNode_t));
  if(!hash->buckets)
    err_exit("Unable to create new Hashtable Nodes!");

  hash->count = 0;

  return hash;
}

htNode_p putHashNode(hashtable_p hash, int key, list_node_p graphNode) {
  if(!hash)
    err_exit("The Hashtable is empty!");

  if(hash->count >= (hash->size/2)) {
    hash->size = hash->size*2;

    hash->buckets = (htNode_p*)realloc(hash->buckets, hash->size*sizeof(htNode_t));
    if(!hash->buckets)
      err_exit("Unable to reallocate the Hashtable nodes!");
  }

  int index = hash->func(key)&(hash->size - 1);
  htNode_p node;

  // Se não houver colisao...
  if(hash->buckets[index] == NULL) {
    hash->buckets[index] = (htNode_p)malloc(sizeof(htNode_t));
    if(!hash->buckets[index])
      err_exit("Unable to create a new Hashtable Node!");

    hash->buckets[index]->key = key;
    hash->buckets[index]->graphNode = graphNode;
    hash->buckets[index]->left = NULL;
    hash->buckets[index]->right = NULL;

    node = hash->buckets[index];

  // Se houver colisao... **TREE**
  } else {
    htNode_p prev = NULL, left = NULL, right = NULL;
    htNode_p curr = hash->buckets[index];

    while(curr) {
      if((curr->key == key) && (curr->graphNode->map->color == graphNode->map->color)) {
        return NULL;
      }

      prev = curr;
      if(curr->key >= key) {
        curr = left;
      } else {
        curr = right;
      }
    }

    htNode_p newNode = (htNode_p)malloc(sizeof(htNode_t));
    if(!newNode)
      err_exit("Unable to create a new Hashtable Node!");

    newNode->key = key;
    newNode->graphNode = graphNode;
    newNode->left = NULL;
    newNode->right = NULL;

    if(prev->key >= key)
      prev->left = newNode;
    else
      prev->right = newNode;

    node = newNode;
  }

  hash->count++;

  return node;
}

void *getHashNode(hashtable_p hash, int key, int color) {
  if(!hash)
    err_exit("The Hashtable is empty!");

  int index = hash->func(key)&(hash->size - 1);

  htNode_p curr = hash->buckets[index];

  while(curr) {
    if((curr->key == key) && (curr->graphNode->map->color == color)) {
      return curr->graphNode;
    }
    
    if(curr->key >= key)
      curr = curr->left;
    else
      curr= curr->right;
  }

  return NULL;
}

void clearHashTable(hashtable_p hash) {
  if(!hash)
    err_exit("The Hashtable is empty!");
  htNode_p curr;
  int i;

  for(i=0; i<hash->size; i++) {
    curr = hash->buckets[i];
    free(curr);
  }

  free(hash->buckets);
  free(hash);

  return;
}

int countHashTable(hashtable_p hash) {
  if(!hash)
    err_exit("The Hashtable is empty!");

  return hash->count;
}
