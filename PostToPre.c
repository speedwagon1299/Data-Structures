#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    char** arr;
    int top;
    int size;
}STACK;
void init(STACK* p, int size)
{
    p->arr = (char**) calloc(size,sizeof(char*));
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
void push(STACK* p, char* ch)
{
    if(!isFull(p))
    {
        p->arr[++(p->top)] = strdup(ch);
    }
    else    printf("\nStack Overflow\n");
}
char* pop(STACK* p)
{
    if(!isEmpty(p))
    {
        return p->arr[(p->top)--];
    }
    printf("\nStack Underflow\n");
}
void display(STACK* p)
{
    printf("\n");
    for(int i = p->top; i >= 0; i--)
    {
        printf("%s\n",p->arr[i]);
    }
    printf("\n");
}
int isOperand(char ch)
{
    return (('a' <= ch) && ('z' >= ch))||(('A' <= ch) && ('Z' >= ch));
}
char* post_to_pre(char* str)
{
    STACK* p = (STACK*) malloc(sizeof(STACK));
    init(p,strlen(str));
    char* op1 = (char*) calloc(strlen(str)+1,sizeof(char));
    char* op2 = (char*) calloc(strlen(str)+1,sizeof(char));
    char* op = (char*) malloc(2*sizeof(char));
    int j = 0;
    for(int i = 0; i < strlen(str); i++)
    {
        op[0] = str[i]; op[1] = '\0';
        if(isOperand(str[i]))   push(p,op);
        else
        {
            op1 = pop(p);
            op2 = pop(p);
            char fin[] = "";
            strcat(fin,op);
            strcat(fin,op2);
            strcat(fin,op1);
            push(p,fin);
        }
    }
    char* temp = pop(p);
    free(op);
    free(op1);
    free(op2);
    free(p->arr);
    free(p);
    return temp;
}
int main()
{
    char* str = (char*) calloc(10,sizeof(char));
    printf("Enter postfix:\n");
    scanf("%s",str);
    printf("\nprefix:\n%s",post_to_pre(str));
    return 0;
}