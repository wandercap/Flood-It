#ifndef _STACK_
#define _STACK_

typedef struct item{
  int data;
  struct item *next;
} Item;

typedef struct stack{
  int size;
  Item *top;
} Stack;

Stack* initStack();
void push(Stack *stack, int item);
int pop(Stack* stack);
void printStack(Stack* stack);
void printInvertedStack(Stack* stack);

#endif

