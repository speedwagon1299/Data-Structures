#include <stdio.h>
#include <stdlib.h>
typedef struct Node
{
    int val;
    struct Node* next;
}node;
typedef struct 
{
    node* head;
    node* top;
    int index, size;
}STACK;
void init(STACK* p, int size)
{
    p->head = (node*) malloc(sizeof(node));
    p->head->next = NULL;
    p->top = p->head;
    p->size = size;
    p->index = -1;
}
node* attach(node* prev, int val)
{
    node* nn = (node*) malloc(sizeof(node));
    nn->next = prev->next;
    prev->next = nn;
    nn->val = val;
    return nn;
}
int isEmpty(STACK* p)
{
    return p->index == -1;
}
int isFull(STACK* p)
{
    return p->index == p->size-1;
}
void push(STACK* p, int val)
{
    if(isFull(p))
    {
        printf("\nStack Overflow\n");
        return;
    }
    p->top = attach(p->top,val);
    p->index++;
}
int pop(STACK* p)
{
    if(isEmpty(p))
    {
        printf("\nStack Underflow\n");
        return -1;
    }
    int a = p->top->val;
    node* curr = p->head;
    for(int i = 0; i < p->index; i++)
    curr = curr->next;
    p->top = curr;
    free(p->top->next);
    p->top->next = NULL;
    p->index--;
    return a;
}
void display(STACK* p)
{
    node* curr = p->head->next;
    for(curr; curr; curr = curr->next)
    printf("%d ",curr->val);
}
int main()
{
    STACK* p = (STACK*) malloc(sizeof(STACK));
    init(p,8);
    int flag = 1,x;
    while(flag)
    {
        printf("\nEnter: ");
        int ch;    scanf("%d",&ch);
        switch(ch)
        {
            case 1:
                printf("\nEnter the number to be pushed: ");
                scanf("%d",&x);
                push(p,x);
                break;
            case 2:
                printf("\n%d\n",pop(p));
                break;
            case 3:
                display(p);
                break;
            default:    flag = 0;
        }
    }
    return 0;
}