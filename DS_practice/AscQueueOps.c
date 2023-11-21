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
}AQUEUE;

AQUEUE* initQueue(int size)
{
    AQUEUE* p = (AQUEUE*) malloc(sizeof(AQUEUE));
    p->size = size;
    p->rear = (node*) malloc(sizeof(node));
    p->front = (node*) malloc(sizeof(node));
    p->rear->val = p->front->val = -1;
    p->front->next = p->rear->next = NULL;
    return p;
}

int isEmpty(AQUEUE* p)   {return p->front->val == p->rear->val;}

int isFull(AQUEUE* p)    {return p->rear->val == p->size-1;}

node* insert(node* prev, int val)
{
    node* nn = (node*) malloc(sizeof(node));
    nn->next = prev->next;
    nn->val = val;
    prev->next = nn;
    return nn;
}

void enqueue(AQUEUE* p, int val)
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

node* dequeue(AQUEUE* p)
{
    if(isEmpty(p))  return NULL;
    node* curr = p->front->next;
    int min = curr->val;
    p->front->val++;
    while(curr)
    {
        if(min > curr->val) min = curr->val;
        curr = curr->next;
    }
    curr = p->front;
    while(curr->next->val != min)
    curr = curr->next;
    node* nn = curr->next;
    curr->next = nn->next;
    return nn;
}

int main()
{
    AQUEUE* p = initQueue(5);
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