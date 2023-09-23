#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    char* arr;
    int top;
    int size;
}STACK;
void init(STACK* p, int size)
{
    p->arr = (char*) calloc(size,sizeof(char));
    p->top = -1;
    p->size = size;
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
    if(!isFull(p))
    {
        p->arr[++p->top] = ch;
    }
    else    printf("\nStack Overflow\n");
}
char pop(STACK* p)
{
    if(!isEmpty(p))
    {
        return p->arr[p->top--];
    }
    printf("\nStack Underflow\n");
}
void display(STACK* p)
{
    printf("\n");
    for(int i = 0; i < p->size; i++)
    {
        printf("%c ",p->arr[i]);
    }
    printf("\n");
}
int isOperand(char ch)
{
    return (('a' <= ch) && ('z' >= ch))||(('A' <= ch) && ('Z' >= ch));
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
        case '%':
            return 2;
            break;
        default: return -1;
    }
}
void in_to_post(char* str)
{
    STACK* p = (STACK*) malloc(sizeof(STACK));
    init(p,strlen(str));
    for(int i = 0; i < strlen(str); i++)
    {
        if(isOperand(str[i]))   printf("%c",str[i]);
        else if(str[i] == '(')  push(p,str[i]);
        else if(str[i] == ')')
        {
            while(p->arr[p->top] != '(')
            printf("%c",pop(p));
            pop(p);
        }
        else
        {
            if(isEmpty(p))   push(p,str[i]);
            else
            {
                if(prec(str[i]) <= prec(p->arr[p->top]))
                while(!isEmpty(p))
                printf("%c",pop(p));
                push(p,str[i]);
            }
        }
    }
    while(!isEmpty(p))  printf("%c",pop(p));
    free(p->arr);
    free(p);
}
int main()
{
    printf("Enter infix: ");
    char s[20];
    scanf("%s",s);
    char* str = (char*) calloc(strlen(s)+1,sizeof(char));
    strcpy(str,s);
    printf("\nInput taken\n\n");
    in_to_post(str);
    return 0;
}