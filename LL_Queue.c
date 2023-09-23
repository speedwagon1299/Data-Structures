#include <stdio.h>
#include <stdlib.h>
typedef struct Node
{
    int val;
    struct Node* next;
}node;
typedef struct 
{
    node* front;
    node* rear;
    int index_f, index_r, size;
}QUEUE;
void init(QUEUE* p, int size)
{
    p->front = (node*) malloc(sizeof(node));
    p->front->next = NULL;
    p->rear = p->front;
    p->size = size;
    p->index_f = 0;
    p->index_r = -1;
}
node* attach(node* prev, int val)
{
    node* nn = (node*) malloc(sizeof(node));
    nn->next = prev->next;
    prev->next = nn;
    nn->val = val;
    return nn;
}
void del(node* prev, node* curr)
{
    prev->next = curr->next;
    free(curr);
}
int isEmpty(QUEUE* p)
{
    return p->index_f > p->index_r;
}
int isFull(QUEUE* p)
{
    return p->index_r == p->size-1;
}
void enqueue(QUEUE* p, int val)
{
    if(isFull(p))
    {
        printf("\nQUEUE Overflow\n");
        return;
    }
    p->rear = attach(p->rear,val);
    p->index_r++;
}
int dequeue(QUEUE* p)
{
    if(isEmpty(p))
    {
        printf("\nQUEUE Underflow\n");
        return -1;
    }
    int a = p->front->next->val;
    del(p->front,p->front->next);
    p->index_f++;
    return a;
}
void display(QUEUE* p)
{
    node* curr = p->front->next;
    for(curr; curr; curr = curr->next)
    printf("%d ",curr->val);
}
int main()
{
    QUEUE* p = (QUEUE*) malloc(sizeof(QUEUE));
    init(p,8);
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
                printf("\n%d\n",dequeue(p));
                break;
            case 3:
                display(p);
                break;
            default:    flag = 0;
        }
    }
    return 0;
}