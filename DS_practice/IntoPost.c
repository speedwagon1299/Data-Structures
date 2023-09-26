#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
typedef struct
{
    char *arr;
    int top;
    int size;
}STACK;
void init(STACK* p, int size)
{
    p->arr = (char*) calloc(size+1,sizeof(char));
    p->size = size;
    p->top = -1;
}
int isEmpty(STACK* p)
{
    return p->top == -1;
}
int isFull(STACK* p)
{
    return p->top == p->size-1;
}
void push(STACK* p, char ch)
{
    if(isFull(p))
    {
        printf("\nStack Overflow\n");
        return;
    }
    p->arr[++p->top] = ch;
}
char pop(STACK* p)
{
    if(isEmpty(p))
    {
        printf("Stack Underflow");
        return -1;
    }
    return p->arr[p->top--];
}
int isOperand(char ch)
{
    return ('a' <= ch && ch <= 'z');
}
int prec(char ch)
{
    switch(ch)
    {
        case '+':
        case '-':
            return 1;
            break;
        case '*':
        case '/':
            return 2;
            break;
        default: return -1;
    }
}
void brackets(char* str)
{
    for(int i = 0; i < strlen(str); i++)
    {
        if(str[i] == '(')   str[i] = ')';
        else if (str[i] == ')') str[i] = '(';
    }
}
char* in_to_post(char* str)
{
    STACK* p = (STACK*) malloc(sizeof(STACK));
    init(p,20);
    char* fin = (char*) calloc(strlen(str)+1,sizeof(char));   int j = 0;
    for(int i = 0; str[i] != '\0'; i++)
    {
        if(isOperand(str[i]))   fin[j++] = str[i];
        else if(str[i] == '(')  push(p,str[i]);
        else if(str[i] == ')')
        {
            while(p->arr[p->top] != '(')
            fin[j++] = pop(p);
            pop(p);
        }
        else
        {
            if(isEmpty(p))  push(p,str[i]);
            else
            {
                if(prec(str[i]) <= prec(p->arr[p->top]))
                while(!isEmpty(p) && p->arr[p->top] != '(')
                fin[j++] = pop(p);
                push(p,str[i]);
            }
        }
    }
    while(!isEmpty(p))
    fin[j++] = pop(p);
    return fin;
}
int main()
{
    printf("Enter infix: ");
    char s[20];
    scanf("%s",s);
    char* str = (char*) calloc(strlen(s)+1,sizeof(char));
    strcpy(str,s);
    printf("\nInput taken\n\n");
    printf("%s",in_to_post(str));
    return 0;
}