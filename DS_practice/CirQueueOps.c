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
}CQUEUE;

CQUEUE* initQueue(int size)
{
    CQUEUE* p = (CQUEUE*) malloc(sizeof(CQUEUE));
    p->size = size;
    p->rear = (node*) malloc(sizeof(node));
    p->front = (node*) malloc(sizeof(node));
    p->rear->val = p->front->val = 0;
    p->front->next = p->rear->next = NULL;
    return p;
}

int isEmpty(CQUEUE* p)   {return (p->front->val)%p->size == (p->rear->val)%p->size;}

int isFull(CQUEUE* p)    {return (p->rear->val+1)%p->size == (p->front->val)%p->size;}

node* insert(node* prev, int val)
{
    node* nn = (node*) malloc(sizeof(node));
    nn->next = prev->next;
    prev->next = nn;
    nn->val = val;
    return nn;
}

void enqueue(CQUEUE* p, int val)
{
    if(isFull(p))   return;
    if(isEmpty(p))
    {
        node* nn = (node*) malloc(sizeof(node));
        nn->val = val;
        p->rear->next = p->front->next = nn;
        nn->next = nn;
        p->rear->val++;
        return;
    }
    p->rear->next = insert(p->rear->next,val);
    p->rear->val++;
}

node* dequeue(CQUEUE* p)
{
    if(isEmpty(p))  return NULL;
    node* nn = p->front->next;
    p->front->next = nn->next;
    p->front->val++;
    p->rear->next->next = nn->next;
    return nn;
}

int main()
{
    CQUEUE* p = initQueue();
    int flag = 1;
    while(flag)
    {
        printf("\nEnter: ");
        int ch;
        scanf("%d",&ch);
        printf("\n");
        switch(ch)
        {
            case 1:
                printf("Enqueue: ");
                int x; scanf("%d",&x);
                enqueue(p,x);
                break;
            case 2:
                node* nn = dequeue(p);
                printf("Dequeue: ");
                if(nn) printf("%d\n",nn->val);
                break;
            default:    flag = 0;
        }
    }
    return 0;
}