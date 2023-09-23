#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
typedef struct
{
    int size, top;
    int* arr;
}STACK;
void init(STACK* p, int size)
{
    p->size = size;
    p->arr = (int*) calloc(size,sizeof(int));
    p->top = -1;
}
int isEmpty(STACK* p) {return p->top == -1;}
int isFull(STACK* p) {return p->top == p->size-1;}
void push(STACK* p, int a)
{
    if(isFull(p)) printf("Stack Overflow\n");
    else p->arr[++(p->top)] = a;
}
int pop(STACK* p)
{
    if(isEmpty(p)) 
    {
        printf("Stack Underflow\n");
        return -1;
    }
    return p->arr[(p->top)--];
}
void display(STACK* p)
{
    int i;
    for(i = p->top; i >= 0; i--) printf("%c\n",p->arr[i]);
}
void rev(char* str)
{
    int i; char temp;
    int len = strlen(str);
    for(i = 0; i <= len/2; i++)
    {
        temp = str[i];
        str[i] = str[len-i-1];
        str[len-i-1] = temp;
    }
}
int postEval(char* str)
{
    STACK* p = (STACK*) malloc(sizeof(STACK));
    int sum = 0;
    init(p,strlen(str));
    for(int i = 0; i < strlen(str); i++)
    {
        if(str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
        {
            int op1 = pop(p);
            int op2 = pop(p);
            if(str[i] == '+') sum = op1+op2;
            else if(str[i] == '-') sum = op1-op2;
            else if(str[i] == '*') sum = op1*op2;
            else if(str[i] == '/') sum = op1/op2;
            push(p,sum);
        }
        else    push(p,str[i]-'0');
    }
    free(p->arr);
    free(p);
    return pop(p);
}
int main()
{
    printf("Enter the postfix expression:\n");
    char *str = (char*) calloc(20,sizeof(char));
    scanf("%s",str);
    rev(str);    //to get prefix
    printf("\n%d",postEval(str));
}
