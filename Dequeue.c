#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    int front, rear;
    int* arr;
    int size;
}DEQUEUE;
void init(DEQUEUE* p, int size)
{
    p->front = p->rear = -1;
    p->arr = (int*) malloc(size*sizeof(int));
    p->size = size;
}
int isEmpty(DEQUEUE* p)
{
    return p->front == p->rear;
}
int isFull(DEQUEUE* p)
{
    return p->rear == p->size - 1;
}
void enqueue_r(DEQUEUE* p, int data)
{
    if(!isFull(p))  p->arr[++p->rear] = data;
    else printf("\nQueue Overflow\n");
}
void enqueue_f(DEQUEUE* p, int data)
{
    if(!isFull(p))  p->arr[p->front--] = data;
    else printf("\nQueue Overflow\n");
}
int dequeue_f(DEQUEUE* p)
{
    if(!isEmpty(p)) return p->arr[++p->front];
    printf("\nQueue Underflow\n");
    return -1;
}
int dequeue_r(DEQUEUE* p)
{
    if(!isEmpty(p)) return p->arr[p->rear--];
    printf("\nQueue Underflow\n");
    return -1;
}
void display(DEQUEUE* p)
{
    for(int i = p->front+1; i != p->rear+1; i++)
    printf("%d ",p->arr[i]);
}
int main()
{
    DEQUEUE* p = (DEQUEUE*) malloc(sizeof(DEQUEUE));
    init(p,10);
    int flag = 1;
    while(flag)
    {
        printf("\nEnter: ");
        int ch;
        scanf("%d",&ch);
        printf("\n");
        int x;
        switch(ch)
        {
            case 1:
                printf("Enqueue Rear: ");
                scanf("%d",&x);
                enqueue_r(p,x);
                break;
            case 2:
                printf("Enqueue Front: ");
                scanf("%d",&x);
                enqueue_f(p,x);
                break;
            case 3:
                printf("Dequeue Rear: ");
                printf("%d\n",dequeue_r(p));
                break;
            case 4:
                printf("Dequeue Front: ");
                printf("%d\n",dequeue_f(p));
                break;
            case 5:
                display(p);
                break;
            default:    flag = 0;
        }
    }
    return 0;
}