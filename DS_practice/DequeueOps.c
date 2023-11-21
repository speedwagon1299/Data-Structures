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
}DEQUEUE;

DEQUEUE* initQueue(int size)
{
    DEQUEUE* p = (DEQUEUE*) malloc(sizeof(DEQUEUE));
    p->size = size;
    p->rear = (node*) malloc(sizeof(node));
    p->front = (node*) malloc(sizeof(node));
    p->rear->val = p->front->val = -1;
    p->front->next = p->rear->next = NULL;
    return p;
}

int isEmpty(DEQUEUE* p)   {return p->front->val == p->rear->val;}

int isFull(DEQUEUE* p)    {return p->rear->val == p->size-1;}

node* insert(node* prev, int val)
{
    node* nn = (node*) malloc(sizeof(node));
    nn->next = prev->next;
    nn->val = val;
    prev->next = nn;
    return nn;
}

void enqueue_f(DEQUEUE* p, int val)
{
    if(p->front->val == -1) return;
    node* nn = (node*) malloc(sizeof(node));
    nn->val = val;
    nn->next = p->front->next;
    p->front->next = nn;
    p->front->val--;
}

void enqueue_r(DEQUEUE* p, int val)
{
    if(isFull(p))   return;
    if(isEmpty(p))
    {
        p->front->next = insert(p->rear, val);
        p->rear->val++;
        return;
    }
    p->rear->next = insert(p->rear->next, val);
    p->rear->val++;
}

node* dequeue_f(DEQUEUE* p)
{
    if(isEmpty(p)) return NULL;
    node* nn = p->front->next;
    p->front->next = nn->next;
    p->front->val++;
    return nn;
}

node* dequeue_r(DEQUEUE* p)
{
    if(isEmpty(p))  return NULL;
    node* curr;
    p->rear->val--;
    if(p->front->next == p->rear->next)     return p->front->next;
    for(curr = p->front->next; curr->next != p->rear->next; curr = curr->next);
    p->rear->next = curr;
    return curr->next;
}

int main()
{
    DEQUEUE* p = initQueue(10);
    int flag = 1;
    while(flag)
    {
        printf("\nEnter: ");
        int ch;
        scanf("%d",&ch);
        printf("\n");
        int x;
        switch(ch)
        {
            case 1:
                printf("Enqueue Rear: ");
                scanf("%d",&x);
                enqueue_r(p,x);
                break;
            case 2:
                printf("Enqueue Front: ");
                scanf("%d",&x);
                enqueue_f(p,x);
                break;
            case 3:
                node* n1 = dequeue_r(p);
                printf("Dequeue Rear: ");
                if(n1) printf("%d\n",n1->val);
                break;
            case 4:
                node* n2 = dequeue_f(p);
                printf("Dequeue Front: ");
                if(n2) printf("%d\n",n2->val);
                break;
            default:    flag = 0;
        }
    }
    return 0;
}