#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
typedef struct Node
{
    int val;
    struct Node* next;
}node;
typedef struct
{
    node* head;
    node* top;
    int size, i;
}STACK;
void init(STACK* p,int size)
{
    p->head = (node*) malloc(sizeof(node));
    p->head->next = NULL;
    p->top = p->head;
    p->size = size;
    p->i = -1;
}
node* attach(node* prev, int val)
{
    node* NN = (node*) malloc(sizeof(node));
    NN->next = prev->next;
    prev->next = NN;
    NN->val = val;
    return NN;
}
void del(node* prev, node* curr)
{
    prev->next = curr->next;
    curr->next = NULL;
    free(curr);
}
int isEmpty(STACK* p)
{
    return p->top == p->head;
}
int isFull(STACK* p)
{
    return p->i == p->size-1;
}
void push(STACK* p, int val)
{
    if(isFull(p))
    {
        printf("Stack Overflow");
        return;
    }
    p->top = attach(p->top,val);
    p->i++;
}
int pop(STACK* p)
{
    if(isEmpty(p))
    {
        printf("Stack Underflow");
        return -1;
    }
    int a = p->top->val;
    node* curr = p->head;
    for(int i = 0; i < p->i; i++)
    curr = curr->next;
    p->top = curr;
    free(p->top->next);
    p->top->next = NULL;
    p->i--;
    return a;
}
void display(STACK* p)
{
    node* curr = p->head->next;
    for(curr; curr; curr = curr->next)
    printf("%d ",curr->val);
}
int oper(int op1, int op2, char op)
{
    if(op == '+') return op1+op2;
    else if(op == '-') return op1-op2;
    else if(op == '*') return op1*op2;
    else if(op == '/') return op1/op2;
}
int post_eval(char* str)
{
    STACK* p = (STACK*) malloc(sizeof(STACK));
    init(p,20);
    for(int i = 0; str[i] != '\0'; i++)
    {
        if(isdigit(str[i])) push(p,str[i]-'0');
        else
        {
            int op1 = pop(p);
            int op2 = pop(p);       //for pure postfix first pop second operand but in prefix its opposite >:c
            int temp = oper(op1,op2,str[i]);
            push(p,temp);
        }  
    }
    int a = pop(p);
    free(p);
    return a;
}

int main()
{
    char* str = (char*) calloc(20,sizeof(char));
    scanf("%[^\n]s",str);
    char str1[20];
    strcpy(str1,strrev(str));
    printf("\nEval: %d",post_eval(str1));
    return 0;
}