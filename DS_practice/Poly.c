#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
typedef struct Node
{
    int c,e;
    struct Node* next;
}node;
node* init()
{
    node* head = (node*) malloc(sizeof(node));
    head->next = NULL;
    return head;
}
node* attach(node* prev, int c, int e)
{
    node* NN = (node*) malloc(sizeof(node));
    NN->next = prev->next;
    prev->next = NN;
    NN->c = c; NN->e = e;
    return NN;
}
node* rev(node*head)
{
    node *prev, *curr, *after;
    prev = head; curr = prev->next;
    while(prev)
    {
        after = curr->next;
        if(prev == head) prev = NULL;
        curr->next = prev;
        prev = curr;
        curr = after;
    }
    head->next = prev;
    return head;
}
node* add(node* a, node* b)
{
    node *p1 = a->next, *p2 = b->next;
    node* c = init();
    node* curr = c;
    while(p1 && p2)
    {
        if(p1->e == p2->e) 
        {
            printf("1a");
            curr = attach(curr,p1->c + p2->c,p1->e);
            printf("1a");
            p1 = p1->next; p2 = p2->next;
            printf("1b");
        }
        else if(p1->e > p2->e)
        {
            curr = attach(curr,p1->c,p1->e);
            p1 = p1->next;
            printf("2");
        }
        else
        {
            curr = attach(curr,p2->c,p2->e);
            p2 = p2->next;
            printf("3");
        }
    }
    if(!p1)
    {
        while(p2)
        {
            curr = attach(curr,p2->c,p2->e);
            p2 = p2->next;
        }
    }
    if(!p2)
    {
        while(p1)
        {
            curr = attach(curr,p1->c,p1->e);
            p1 = p1->next;
        }
    }
    return c;
}
void display(node* head)
{
    node* curr = head->next;
    for(curr; curr; curr = curr->next)
    printf("%d(%d)",curr->c,curr->e);
}
int main()
{
    node* a = init();
    node* b = init();
    node* curr;
    curr = attach(a,3,14);
    curr = attach(curr,2,8);
    curr = attach(curr,1,0);
    display(a);
    curr = attach(b,8,14);
    curr = attach(curr,-3,10);
    curr = attach(curr,10,6);
    display(b);
    node* sum = add(a,b);
    curr = sum->next;
    printf("\n");
    for(curr;curr;curr=curr->next)
    printf("%dx^%d + ",curr->c,curr->e);
    printf("0");
    return 0;
}