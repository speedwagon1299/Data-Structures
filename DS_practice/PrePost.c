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

int isEmpty(STACK* p) { return p->top == -1;}
int isFull(STACK* p) {  return p->top == p->size-1;}

node* newNode(char* val)
{
    node* nn = (node*) malloc(sizeof(node));
    nn->next = NULL;
    nn->val = strdup(val);
    return nn;
}

void push(STACK* p, char* val)
{
    if(isFull(p))
    return;
    p->top++;
    node* temp = newNode(val);
    temp->next = p->head->next;
    p->head->next = temp;
}

node* top(STACK* p) {return p->head->next;}

node* pop(STACK* p)
{
    if(isEmpty(p))
    return NULL;
    p->top--;
    node* temp = p->head->next;
    p->head->next = temp->next;
    return temp;
}

void rev(char* str)
{
    int len = strlen(str);
    char temp;
    for(int i = 0; i <= len/2; i++)
    {
        temp = str[i];
        str[i] = str[len-i-1];
        str[len-i-1] = temp;
    }
}

void post_pre(char* str)
{
    STACK* p = initStack(20);
    char* op1 = (char*) calloc(strlen(str),sizeof(char));
    char* op2 = (char*) calloc(strlen(str),sizeof(char));
    char* op = (char*) calloc(2,sizeof(char));
    for(int i = 0; i < strlen(str); i++)
    {
        op[0] = str[i]; op[1] = '\0';
        if('a' <= str[i] && str[i] <= 'z')  push(p,op);
        else
        {
            char temp[] = "";
            op2 = pop(p)->val;
            op1 = pop(p)->val;
            strcat(temp,op);
            strcat(temp,op1);
            strcat(temp,op2);
            push(p,temp);
        }
    }
    char* fin = pop(p)->val;
    printf("\nPrefix: %s",fin);
    free(op1); free(op2); free(op);
}

void pre_post(char* str)
{
    STACK* p = initStack(15);
    rev(str);
    char* op = (char*)calloc(2, sizeof(char));
    char* op1 = (char*)calloc(15, sizeof(char));
    char* op2 = (char*)calloc(15, sizeof(char));
    
    for(int i = 0; i < strlen(str); i++)
    {
        op[0] = str[i]; op[1] = '\0';
        if('a' <= str[i] && str[i] <= 'z')  push(p,op);
        else
        {
            char temp[] = "";
            op2 = pop(p)->val;
            op1 = pop(p)->val;
            strcat(temp, op);
            strcat(temp, op1);
            strcat(temp, op2);
            push(p,temp);
        }
    }
    char* fin = pop(p)->val;
    rev(fin);
    printf("\nPostfix:\t%s", fin); 
    free(op); free(op1); free(op2);
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
    switch(x[0])
    {
        case '+': 
        case '-':
            return 1;
        case '*':
        case '/':
            return 2; 
        case '^':
            return 3;
        default: return -1;
    }
}

void in_pre(char* str) {
    rev(str);
    STACK* p = initStack(15);
    char* op = (char*)calloc(2, sizeof(char));
    char* op1 = (char*)calloc(2, sizeof(char));
    char* fin = (char*)calloc(15,sizeof(char));

    for(int i = 0; str[i] != '\0'; i++) 
    {
        op[0] = str[i]; op[1] = '\0';
        if ('a' <= str[i] && str[i] <= 'z') strcat(fin, op);
        else if (str[i] == ')') push(p, op);
        else if (str[i] == '(') 
        {
            while (!isEmpty(p) && strcmp(top(p)->val, ")") != 0) 
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
                while(!isEmpty(p) && strcmp(top(p)->val, ")") != 0) 
                {
                    op1 = pop(p)->val;
                    strcat(fin, op1);
                }
                pop(p);
            }
            push(p, op);
        }
    }
    rev(str);
    while (!isEmpty(p)) {
        op1 = pop(p)->val;
        strcat(fin, op1);
    }
    rev(fin);
    free(p);
    free(op);
    free(op1);

    printf("\nPrefix: %s", fin);
    free(fin); 
}


int main()
{
    char* str = (char*) calloc(10,sizeof(char));
    printf("Enter Infix:\n");
    scanf("%s",str);
    in_pre(str);
    // post_in(str);
    // pre_post(str);
    // post_pre(str);
    // rev(str);
    
    return 0;
}