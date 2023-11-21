#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int front,rear, size;
    int* arr;
}QUEUE;

void init(QUEUE* p, int size)
{
    p->front = p->rear = -1;
    p->arr = (int*) malloc(size*sizeof(int));
    p->size = size;
}

int isEmpty(QUEUE* p)
{
    return p->front == p->rear;
}

void enqueue(QUEUE* p, int val)
{
    if(p->rear == p->size-1)
    {
        printf("\nQUEUE OVERFLOW\n");
        return;
    }
    p->arr[++p->rear] = val;
}

int dequeue(QUEUE* p)
{
    if(isEmpty(p))
    {
        printf("QUEUE UNDERFLOW");
        return -1;
    }
    return p->arr[++p->front];
}

void rev(QUEUE* p)
{
    if(isEmpty(p))
    return;
    int temp = dequeue(p);
    rev(p);
    printf("%d ",temp);
    return;
}

int main()
{
    QUEUE* p = (QUEUE*) malloc(sizeof(QUEUE));
    init(p,10);
    enqueue(p,1);
    enqueue(p,2);
    enqueue(p,3);
    enqueue(p,4);
    enqueue(p,5);
    enqueue(p,6);
    rev(p);
}