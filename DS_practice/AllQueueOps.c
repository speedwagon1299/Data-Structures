#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    struct Node* next;
    int val;
}node;

typedef struct
{
    node* front;
    node* rear;
    int f, r;
}DQ;

DQ* initDQ()
{
    DQ* p = (DQ*) malloc(sizeof(DQ));
    p->front = (node*) malloc(sizeof(node));
    p->rear = (node*) malloc(sizeof(node));
    p->front->next = p->rear->next = NULL;
    p->f = p->r = -1;
    return p;
}

node* newNode(int val)
{
    node* nn = (node*) malloc(sizeof(node));
    nn->next = NULL;
    nn->val = val;
    return nn;
}

int isEmpty(DQ* p)
{
    return p->r == p->f;
}

void enqueue_r(DQ* p, int val)
{
    node* nn = newNode(val);
    if(isEmpty(p))
    {
        p->rear->next = p->front->next = nn;
        p->r++;
    }
    else
    {
        node* temp = p->rear->next;
        temp->next = nn;
        p->rear->next = nn;
        p->r++;
    }
}


void enqueue_f(DQ* p, int val) 
{
    node* nn = newNode(val);
    if(isEmpty(p))
    {
        nn->next = p->front->next;
        p->front->next = p->rear->next = nn;
        p->f--;
    }
    else
    {
        nn->next = p->front->next;
        p->front->next = nn;
        p->f--;
    }
}

node* dequeue_r(DQ* p)
{
    if(isEmpty(p))
    {
        printf("\nQU\n");
        return NULL;
    }
    node* curr = p->front->next;
    if(curr != p->rear->next)
    {
        p->r--;
        for(curr; curr->next != p->rear->next; curr = curr->next);
        p->rear->next = curr;
        node* temp = curr->next;
        curr->next = NULL;
        return temp;
    }
    p->r--;
    p->front->next = p->rear->next = NULL;
    return curr;
}

node* dequeue_f(DQ* p)
{
    if(isEmpty(p))
    {
        printf("\nQU\n");
        return NULL;
    }
    node* temp = p->front->next;
    if(temp == p->rear->next)
    {
        p->f++;
        p->front->next = p->rear->next = NULL;
        return temp;
    }
    p->f++;
    p->front->next = temp->next;
    return temp;
}

node* dequeue_prio(DQ* p)
{
    if(isEmpty(p))
    {
        printf("\nQU\n");
        return NULL;
    }
    node* curr = p->front->next;
    p->r--;
    if(curr != p->rear->next)
    {
        int min = curr->val;
        for(curr; curr; curr = curr->next)
        {
            if(curr->val < min)
            {
                min = curr->val;
            }
        }
        curr = p->front;
        for(curr; curr; curr = curr->next)
        {
            if(curr->next->val == min)
            break;
        }
        if(curr->next == p->rear->next)
        {
            p->rear->next = curr;
            // node* temp = curr->next;
            // curr->next = NULL;
            // return temp;
        }
        node* temp = curr->next;
        curr->next = curr->next->next;
        return temp;
    }
    p->rear->next = p->front->next = NULL;
    return curr;
}

int main()
{
    DQ* p = initDQ();
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
                node* n2 = dequeue_prio(p);
                printf("Dequeue prio: ");
                if(n2) printf("%d\n",n2->val);
                break;
            default:    flag = 0;
        }
    }
    return 0;
}