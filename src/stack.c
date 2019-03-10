#include <stdio.h>
#include <stdlib.h>
#include "../include/stack.h"

Stack* initStack() {
  Stack *stack = (Stack*) malloc(sizeof(Stack));
  stack->size = 0;
  stack->top = NULL;

  return stack;
}

void push(Stack *stack, int item){
  Item *aux = (Item*)malloc(sizeof(Item));    
  aux->data = item;
  aux->next = stack->top;
  stack->top = aux;
  stack->size++;
}

int pop(Stack* stack){
  if(stack->top==NULL){
    return -1;
  }else{
    Item *aux = (Item*) malloc(sizeof(Item));
    aux = stack->top;
    stack->top = stack->top->next;
    return aux->data;
    free(aux);
  }
}

void printStack(Stack* stack){
  Item *aux = (Item*) malloc(sizeof(Item));
  printf("%d\n", stack->size);
  for(aux = stack->top; aux!= NULL ; aux=aux->next)
    printf("%d ", aux->data);

  printf("\n");
}   

void printInvertedStack(Stack *stack){
  if(stack->top != NULL){
    int aux = pop(stack);
    printInvertedStack(stack);
    printf("%d ",aux);
  }
}

