#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    int front, rear;
    int* arr;
    int size;
}CQUEUE;
void init(CQUEUE* p, int size)
{
    p->front = p->rear = 0;
    p->arr = (int*) malloc(size*sizeof(int));
    p->size = size;
}
int isEmpty(CQUEUE* p)
{
    return p->front == p->rear;
}
int isFull(CQUEUE* p)
{
    return (p->rear+1)%p->size == (p->front)%p->size;
}
void enqueue(CQUEUE* p, int data)
{
    if(!isFull(p))  p->arr[(++p->rear)%p->size] = data;
    else printf("\nQueue Overflow\n");
}
int dequeue(CQUEUE* p)
{
    if(!isEmpty(p)) return p->arr[(++p->front)%p->size];
    printf("\nQueue Underflow\n");
    return -1;
}
void display(CQUEUE* p)
{
    for(int i = (p->front+1)%p->size; i != (p->rear+1)%p->size; i=(i+1)%p->size)
    printf("%d ",p->arr[i]);
}
int main()
{
    CQUEUE* p = (CQUEUE*) malloc(sizeof(CQUEUE));
    init(p,5);
    int flag = 1;
    while(flag)
    {
        printf("\nEnter: ");
        int ch;
        scanf("%d",&ch);
        printf("\n");
        switch(ch)
        {
            case 1:
                printf("Enqueue: ");
                int x; scanf("%d",&x);
                enqueue(p,x);
                break;
            case 2:
                printf("Dequeue: ");
                printf("%d\n",dequeue(p));
                break;
            case 3:
                display(p);
                break;
            default:    flag = 0;
        }
    }
    return 0;
}