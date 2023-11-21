#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    struct Node* next;
    int val;
}node;

typedef struct 
{
    node *rear, *front;
    int size;
}QUEUE;

QUEUE* initQueue(int size)
{
    QUEUE* p = (QUEUE*) malloc(sizeof(QUEUE));
    p->size = size;
    p->rear = (node*) malloc(sizeof(node));
    p->front = (node*) malloc(sizeof(node));
    p->rear->val = p->front->val = -1;
    p->front->next = p->rear->next = NULL;
    return p;
}

int isEmpty(QUEUE* p)   {return p->front->val == p->rear->val;}

int isFull(QUEUE* p)    {return p->rear->val == p->size-1;}

node* insert(node* prev, int val)
{
    node* nn = (node*) malloc(sizeof(node));
    nn->next = prev->next;
    prev->next = nn;
    nn->val = val;
    return nn;
}

void enqueue(QUEUE* p, int val)
{
    if(isFull(p))   return;
    if(isEmpty(p))
    {
        p->front->next = insert(p->rear,val);
        p->rear->val++;
        return;
    }
    p->rear->val++;
    p->rear->next = insert(p->rear->next,val);
}

node* dequeue(QUEUE* p)
{
    if(isEmpty(p))  return NULL;
    p->front->val++;
    node* nn = p->front->next;
    p->front->next = nn->next;
    return nn;
}

int main()
{
    QUEUE* p = initQueue(5);
    int flag = 1,x;
    while(flag)
    {
        printf("\nEnter: ");
        int ch;    scanf("%d",&ch);
        switch(ch)
        {
            case 1:
                printf("\nEnter the number to be Enqueued: ");
                scanf("%d",&x);
                enqueue(p,x);
                break;
            case 2:
                node *nn = dequeue(p);
                if(nn)  printf("\n%d\n",nn->val);
                break;
            default:    flag = 0;
        }
    }
    return 0;
}