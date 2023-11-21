#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    struct Node* next;
    char* val;
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

node* insert(node* prev, char* val)
{
    node* nn = (node*) malloc(sizeof(node));
    nn->val = (char*) calloc(15,sizeof(char));
    nn->val = strdup(val);
    nn->next = prev->next;
    prev->next = nn;
    return nn;
}

int isFull(STACK* p){  return p->top == p->size - 1;}

int isEmpty(STACK* p){   return p->top == -1;}

void push(STACK* p, char* val)
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

void post_pre(char* str)
{
    STACK* p = initStack(20);
    char* op = (char*)calloc(2, sizeof(char));
    char* op1 = (char*)calloc(10, sizeof(char));
    char* op2 = (char*)calloc(10, sizeof(char));
    for (int i = 0; str[i] != '\0'; i++) {
        op[0] = str[i]; op[1] = '\0';
        if ('a' <= str[i] && str[i] <= 'z') {
            push(p, op);
        } else {
            char temp[] = "";
            op1 = pop(p)->val;
            op2 = pop(p)->val;
            strcat(temp, op);
            strcat(temp, op2);
            strcat(temp, op1);
            push(p, temp);
        }
    }
    char* fin = pop(p)->val; 
    free(op); free(op1); free(op2); free(p);
    printf("\nprefix:\n%s", fin); 
}

void pre_post(char* str)
{
    STACK* p = initStack(15);
    rev(str);
    char* op = (char*)calloc(2, sizeof(char));
    char* op1 = (char*)calloc(15, sizeof(char));
    char* op2 = (char*)calloc(15, sizeof(char));
    for(int i = 0; str[i] != '\0'; i++)
    {
        op[0] = str[i]; op[1] = '\0';
        if('a' <= str[i] && str[i] <= 'z')  push(p,op);
        else
        {
            op2 = pop(p)->val;
            op1 = pop(p)->val;
            char temp[] = "";
            strcat(temp, op);
            strcat(temp, op2);
            strcat(temp, op1);
            push(p,temp);
        }
    }
    char* fin = pop(p)->val;
    rev(fin);
    free(op); free(op1); free(op2); free(p);
    printf("\npostfix:\n%s", fin); 
}

void post_in(char* str)
{
    STACK* p = initStack(15);
    char* op = (char*) calloc(2,sizeof(char));
    char* op1 = (char*) calloc(15,sizeof(char));
    char* op2 = (char*) calloc(15,sizeof(char));
    for(int i = 0; str[i] != '\0'; i++)
    {
        op[0] = str[i]; op[1] = '\0';
        if('a' <= str[i] && str[i] <= 'z')  push(p,op);
        else
        {
            op1 = pop(p)->val;
            op2 = pop(p)->val;
            char temp[] = "";
            strcat(temp,op2);
            strcat(temp,op);
            strcat(temp,op1);
            push(p,temp);
        }
    }
    char* fin = pop(p)->val;
    free(op); free(op1); free(op2); free(p);
    printf("\ninfix:\n%s", fin); 
}

int prec(char* x)
{
    if(!strcmp(x,"+") || !strcmp(x,"-"))    return 1;
    if(!strcmp(x,"*") || !strcmp(x,"/"))    return 2;
    return -1;
}

void in_post(char* str) {
    STACK* p = initStack(15);
    char* op = (char*)calloc(2, sizeof(char));
    char* op1 = (char*)calloc(2, sizeof(char));
    char* fin = (char*)calloc(15,sizeof(char));

    for(int i = 0; str[i] != '\0'; i++) 
    {
        op[0] = str[i]; op[1] = '\0';
        if ('a' <= str[i] && str[i] <= 'z') strcat(fin, op);
        else if (str[i] == '(') push(p, op);
        else if (str[i] == ')') 
        {
            while (strcmp(top(p)->val, "(") != 0) 
            {
                op1 = pop(p)->val;
                strcat(fin, op1);
            }
            pop(p);
        } 
        else 
        {
            if(isEmpty(p) || prec(op) <= prec(top(p)->val)) 
            {
                while(!isEmpty(p) && strcmp(top(p)->val, "(") != 0) 
                {
                    op1 = pop(p)->val;
                    strcat(fin, op1);
                }
            }
            push(p, op);
        }
    }

    while (!isEmpty(p)) {
        op1 = pop(p)->val;
        strcat(fin, op1);
    }

    free(p);
    free(op);
    free(op1);

    printf("\nPostfix: %s", fin);
    free(fin); 
}


int main()
{
    char* str = (char*) calloc(10,sizeof(char));
    printf("Enter Infix:\n");
    scanf("%s",str);
    in_post(str);
    // post_in(str);
    // post_pre(str);
    // rev(str);
    // pre_post(str);
    return 0;
}