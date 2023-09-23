#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
typedef struct
{
    int size, topf, topb;
    int *arr;
}STACK;
void init(STACK* p, int size)
{
    p->size = size;
    p->arr = (int*)calloc(size,sizeof(int));
    p->topf = -1;
    p-> topb = size;
}
void push(STACK* p, int ch, int a)
{
    if(p->topf+1 == p->topb)
    {
        printf("Stack Overflow");
        return;
    }
    else if(ch == 1) p->arr[++(p->topf)] = a;
    else p->arr[--(p->topb)] = a;
}
int pop(STACK* p, int ch)
{
    if(ch == 1 && p->topf != -1)    return p->arr[(p->topf)--];
    else if(ch == 2 && p->topf != p->size) return p->arr[(p->topb)++];
    return -1;
}
void display(STACK* p)
{
    int i;
    printf("\n");
    for(i = 0; i <= p->topf; i++)
    printf("%d ",p->arr[i]);
    for(i = p->topf+1; i < p->topb; i++)
    printf("_ ");
    for(i = p->topb; i < p->size; i++)
    printf("%d ",p->arr[i]);
    printf("\n");
}
int main()
{
    STACK s,*p;
    p = &s;
    init(p,8);
    int ch,st;
    printf("Enter 1 for front and 2 for back and 3 to EXIT:\n");
    scanf("%d",&ch);
    printf("\nEnter 1.Push 2.Pop 3.Display\n");
    scanf("%d",&st);
    do
    {
        switch(st)
        {
            case 1:
            printf("\nEnter the element to be pushed:\n");
            int e; scanf("%d",&e);
            push(p,ch,e);
            break;
            case 2:
            printf("\nPopped: %d",pop(p,ch));
            break;
            case 3:
            display(p);
        }
        printf("\nEnter 1 for front and 2 for back and 3 to EXIT:\n");
        scanf("%d",&ch);
        printf("\nEnter 1.Push 2.Pop 3.Display\n");
        scanf("%d",&st);
    } while (ch != 3);
    return 0;   
}