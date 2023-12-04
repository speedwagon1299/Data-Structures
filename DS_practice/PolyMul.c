#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int c,e;
    struct Node* next;
    struct Node* prev;
}node;

typedef struct 
{
    int size;
    node* head;
}POLY;

POLY* initPoly()
{
    POLY* p = (POLY*) malloc(sizeof(POLY));
    p->size = 0;
    p->head = (node*) malloc(sizeof(node));
    p->head->next = NULL;
    p->head->prev = p->head;
    p->head->c = p->head->e = 0;
    return p;
}

void polyattach(POLY* p, int c, int e)
{
    node* nn = (node*) malloc(sizeof(node));
    nn->c = c;
    nn->e = e;
    if(p->size == 0)
    {
        p->head->next = nn;
        nn->prev = nn->next = nn;
        p->size++;
        return;
    }
    nn->next = p->head->next;
    nn->prev = nn->next->prev;
    nn->next->prev->next = nn;
    nn->next->prev = nn;
    p->head->next = nn;
    p->size++;
}

POLY* add(POLY* a, POLY* b)
{
    POLY* c = initPoly();
    node *p1 = a->head->next, *p2 = b->head->next;
    int f1 = 1,f2 = 1;
    while((p1 != a->head->next && p2 != b->head->next) || (f1 || f2))
    {
        if(p1->e == p2->e)
        {
            polyattach(c,p1->c + p2->c, p1->e);
            p1 = p1->next;
            p2 = p2->next;
            f1 = f2 = 0;
        }
        else if(p1->e > p2->e)
        {
            polyattach(c,p1->c,p1->e);
            p1 = p1->next;
            f1 = 0;
        }
        else
        {
            polyattach(c,p2->c,p2->e);
            p2 = p2->next;
            f2 = 0;
        }
    }
    while(p1 != a->head->next || f1)
    {
        polyattach(c,p1->c,p1->e);
        f1 = 0;
        p1 = p1->next;
    }
    while(p2 != b->head->next || f2)
    {
        polyattach(c,p2->c,p2->e);
        f2 = 0;
        p2 = p2->next;
    }
    return c;
}

POLY* mul(POLY* a, POLY* b)
{
    POLY* c = initPoly();
    node *p1 = a->head->next, *p2 = b->head->next, *p3;
    int f1 = 1, f2 = 1, f3 = 1, flag = 0;
    for(p1; p1 != a->head->next || f1; p1 = p1->next)
    {
        for(p2; p2 != b->head->next || f2; p2 = p2->next)
        {
            if(f1 == 1) 
            {
                polyattach(c,p1->c*p2->c,p1->e+p2->e);
            }
            else
            {
                for(p3 = c->head->next; p3 != c->head->next || f3; p3 = p3->next)
                {
                    if(p3->e == p1->e + p2->e)
                    {
                        p3->c += p1->c*p2->c;
                        flag = 1;
                        break;
                    }
                    f3 = 0;
                }
                if(flag == 0)
                polyattach(c,p1->c*p2->c,p1->e+p2->e);
                flag = 0;
            }
            f2 = 0; f3 = 1;
        }
        f1 = 0; f2 = 1;
    }
    return c;
}

int main()
{
    POLY* a = initPoly(); 
    POLY* b = initPoly();
    polyattach(a,3,4);
    polyattach(a,4,5);
    polyattach(b,4,2);
    polyattach(b,7,3);
    POLY* c = mul(a,b);
    node* curr = c->head;
    do
    {
        printf("%dx^%d + ",curr->next->c,curr->next->e); 
        curr = curr->next;
    }
    while(curr->next != c->head->next);
    return 0;
}