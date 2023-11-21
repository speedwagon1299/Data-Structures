#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    struct Node* next;
    int val;
}node;

typedef struct 
{
    node* head;
    int top;
    int size;
}STACK;

STACK* initStack(int size)
{
    STACK* p = (STACK*) malloc(sizeof(STACK));
    p->size = size;
    p->top = -1;
    p->head = (node*) malloc(sizeof(node));
    p->head->next = NULL;
    return p;
}

node* insert(node* prev, int val)
{
    node* nn = (node*) malloc(sizeof(node));
    nn->val = val;
    nn->next = prev->next;
    prev->next = nn;
    return nn;
}

int isFull(STACK* p){  return p->top == p->size - 1;}

int isEmpty(STACK* p){   return p->top == -1;}

void push(STACK* p, int val)
{
    if(isFull(p))   return;
    p->top++;
    insert(p->head, val);
}

node* top(STACK* p)
{
    return p->head->next;
}
node* pop(STACK* p)
{
    if(isEmpty(p))  return NULL;
    p->top--;
    node* nn = p->head->next;
    p->head->next = nn->next;
    return nn;
}

int postfix_eval(char* str)
{
    STACK* p = initStack(20);
    for(int i = 0; str[i] != '\0'; i++)
    {
        if(str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
        {
            int t2 = pop(p)->val, t1 = pop(p)->val;
            int temp = 0;
            if(str[i] == '+') temp = t1+t2;
            else if(str[i] == '-') temp = t1-t2;
            else if(str[i] == '*') temp = t1*t2;
            else if(str[i] == '/') temp = t1/t2; 
            push(p,temp);
        }
        else    push(p,str[i]-'0');
    }
    return pop(p)->val;
}

void rev(char* str)
{
    char temp;
    for(int i = 0; i <= strlen(str)/2; i++)
    {
        temp = str[i];
        str[i] = str[strlen(str)-i-1];
        str[strlen(str)-i-1] = temp;
    }
}

int prefix_eval(char* str)
{
    rev(str);
    STACK* p = initStack(10);
    for(int i = 0; str[i] != '\0'; i++)
    {
        if(str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
        {
            int t1 = pop(p)->val, t2 = pop(p)->val;
            int temp = 0;
            if(str[i] == '+') temp = t1+t2;
            if(str[i] == '-') temp = t1-t2;
            if(str[i] == '*') temp = t1*t2;
            if(str[i] == '/') temp = t1/t2;
            push(p,temp);
        }
        else    push(p,str[i]-'0');
    }
    rev(str);
    return pop(p)->val;
}

int main()
{
    printf("Enter the postfix expression:\n");
    char *str = (char*) calloc(20,sizeof(char));
    scanf("%s",str);
    printf("\n%d",postfix_eval(str));
    printf("\nEnter the prefix expression:\n");
    scanf("%s",str);
    printf("\n%d",prefix_eval(str)); 
    printf("%s",str);  
}