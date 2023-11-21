#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
typedef struct Node
{
    int val;
    struct Node* next;
}node;
typedef struct 
{
    node *front,*rear;
    int size,ind_f,ind_r;
}DQ;
void init(DQ* p, int size)
{
    p->front = (node*) malloc(sizeof(node));
    p->front->next = NULL;
    p->rear = p->front;
    p->size = size;
    p->ind_f = p->ind_r = -1;
}
node* attach(node* prev, int val)
{
    node* NN = (node*) malloc(sizeof(node));
    NN->next = prev->next;
    prev->next = NN;
    NN->val = val;
    return NN;
}
void del(node* prev)
{
    node* curr = prev->next;
    prev->next = curr->next;
    free(curr);
}
int isEmpty(DQ* p)
{
    return p->ind_f == p->ind_r;
}
int isFullR(DQ* p)
{
    return p->ind_r >= p->size-1;
}
int isFullF(DQ* p)
{
    return p->ind_f <= -1;
}
void enq_r(DQ* p, int val)
{
    if(isFullR(p))
    {
        printf("\nQueue Overflow\n");
        return;
    }
    p->rear = attach(p->rear,val);
    p->ind_r++;
}
int deq_f(DQ* p)
{
    if(isEmpty(p))
    {
        printf("\nQueue Underflow\n");
        return -1;
    }
    int a = p->front->next->val;
    del(p->front);
    p->ind_f++;
    return a;
}
void enq_f(DQ* p, int val)
{
    if(isFullF(p))
    {
        printf("\nQueue Overflow\n");
        return;
    }
    attach(p->front,val);
    p->ind_f--;
}
int deq_r(DQ* p)
{
    if(isEmpty(p))
    {
        printf("\nQueue Underflow\n");
        return -1;
    }
    node* prev = p->front;
    for(prev;prev->next->next;prev = prev->next);
    int a = p->rear->val;
    del(prev);
    p->rear = prev;
    p->ind_r--;
    return a;
}
void display(DQ* p)
{
    node* curr = p->front->next;
    for(curr;curr;curr=curr->next)
    printf("%d ",curr->val);
}
int main()
{
    DQ* p = (DQ*) malloc(sizeof(DQ));
    init(p,10);
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
                enq_r(p,x);
                break;
            case 2:
                printf("Enqueue Front: ");
                scanf("%d",&x);
                enq_f(p,x);
                break;
            case 3:
                printf("Dequeue Rear: ");
                printf("%d\n",deq_r(p));
                break;
            case 4:
                printf("Dequeue Front: ");
                printf("%d\n",deq_f(p));
                break;
            case 5:
                display(p);
                break;
            default:    flag = 0;
        }
    }
    return 0;
}