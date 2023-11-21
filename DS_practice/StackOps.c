#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    struct Node* next;
    int val;
}node;

typedef struct 
{
    node* head;
    int top;
    int size;
}STACK;

STACK* initStack(int size)
{
    STACK* p = (STACK*) malloc(sizeof(STACK));
    p->size = size;
    p->top = -1;
    p->head = (node*) malloc(sizeof(node));
    p->head->next = NULL;
    return p;
}

node* insert(node* prev, int val)
{
    node* nn = (node*) malloc(sizeof(node));
    nn->val = val;
    nn->next = prev->next;
    prev->next = nn;
    return nn;
}

int isFull(STACK* p){  return p->top == p->size - 1;}

int isEmpty(STACK* p){   return p->top == -1;}

void push(STACK* p, int val)
{
    if(isFull(p))   return;
    p->top++;
    insert(p->head, val);
}

node* pop(STACK* p)
{
    if(isEmpty(p))  return NULL;
    p->top--;
    node* nn = p->head->next;
    p->head->next = nn->next;
    return nn;
}

int main()
{
    STACK* p = initStack(5);
    push(p,1);
    push(p,2);
    push(p,3);
    push(p,4);
    push(p,5);
    push(p,6);
    node* n1 = pop(p);
    node* n2 = pop(p);
    node* n3 = pop(p);
    node* n4 = pop(p);
    node* n5 = pop(p);
    printf("%d %d %d %d %d", n1->val, n2->val, n3->val, n4->val, n5->val);
    return 0;
}