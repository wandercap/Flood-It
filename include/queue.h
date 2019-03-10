#ifndef __QUEUE_H__
#define __QUEUE_H__

void search(heap_p heap,list_node_p node, int i, int *find);
void putQueue(hashtable_p hash, heap_p heap, list_node_p node);
list_node_p getQueue(hashtable_p hash, heap_p heap);
void removeQueue(heap_p heap, list_node_p node);
list_node_p searchNode(hashtable_p hash, heap_p heap, list_node_p node);

#endif