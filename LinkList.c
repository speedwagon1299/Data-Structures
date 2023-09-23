#include <stdio.h>
#include <stdlib.h>
typedef struct Node
{
    int val;
    int pri;
    struct Node* next;
}node;
node* attach(node* prev, int val, int pri)
{
    node* nn = (node*) malloc(sizeof(node));
    nn->next = prev->next;
    prev->next = nn;
    nn->val = val;
    nn->pri = pri;
    return nn;
}
void display(node* head)
{
    node* curr = head->next;
    for(curr; curr; curr = curr->next)
    printf("%d(%d) ",curr->val,curr->pri);
}
node* reverse(node* head)
{
    node *prev = head, *curr = prev->next, *after;
    while(curr)
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
int main()
{
    node* head = (node*) malloc(sizeof(node));
    head->next = NULL;
    node* curr = head;
    printf("Enter the number of elements: ");
    int x,y,n;  scanf("%d",&n);
    for(int i = 0; i < n; i++)
    {
        printf("\nEnter the element and priority: ");
        scanf("%d",&x);
        scanf("%d",&y);
        attach(curr,x,y);
        curr=curr->next;
    }
    display(head);
    printf("\n\n");
    display(reverse(head));
    // node* Head = (node*) malloc(sizeof(node));
    // node* rear = (node*) malloc(sizeof(node));
    // node* start = (node*) malloc(sizeof(node));
    // start->next = NULL;
    // Head->next = start;
    // rear->next = start;
    // curr = head->next;
    // for(curr; curr; curr = curr->next)
    // {
    //     if(curr->pri%2 == 0)    attach(Head,curr->val,curr->pri);
    //     else    rear->next = attach(rear->next,curr->val,curr->pri);
    // }
    // for(curr = Head->next; curr; curr = curr->next)
    // if(curr->next == start)
    // curr->next = start->next;
    // display(Head);
}