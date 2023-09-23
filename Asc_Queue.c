#include <stdio.h>
#include <stdlib.h>
typedef struct
{
    int* arr;
    // int* pri;
    int size, front, rear;
}AQUEUE;
void init(AQUEUE* p, int size)
{
    p->arr = (int*) calloc(size,sizeof(int));
    // p->pri = (int*) calloc(size,sizeof(int));
    p->size = size;
    p->front = p->rear = -1;
}
int isEmpty(AQUEUE* p)
{
    return p->front == p->rear;
}
int isFull(AQUEUE* p)
{
    return (p->rear+1)%p->size == (p->front)%p->size;
}
void enqueue(AQUEUE* p, int data)
{
    if(isEmpty(p))
    {
        p->arr[++p->rear] = data;
        return;
    }
    if(isFull(p))
    {
        printf("\nQueue Overflow\n");
        return;
    }
    int poi = ++p->rear;
    for(int i = p->front+1; i <= p->rear; i++)
    {
        if(p->arr[i] >= data)
        {
            poi = i;
            break;
        }
    }
    for(int i = p->rear; i >= poi; i--)
    p->arr[i+1] = p->arr[i];
    p->arr[poi] = data;
    return;
}
int dequeue(AQUEUE* p)
{
    if(!isEmpty(p)) return p->arr[++p->front];
    printf("\nQueue Underflow\n");
    return -1;
}
void display(AQUEUE* p)
{
    printf("\n");
    for(int i = p->front+1; i!= p->rear+1; i++)
    printf("%d ",p->arr[i]);
    printf("\n");
}
int main()
{
    AQUEUE* p = (AQUEUE*) malloc(sizeof(AQUEUE));
    init(p,10);
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