#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    char* month;
    int day;
    char* event;
}MONTHLYSCHEDULE;
void init(MONTHLYSCHEDULE* p)
{
    p->month = (char*)calloc(30,sizeof(char));
    p->day = 0;
    p->event = (char*)calloc(30,sizeof(char));
    return;
}
void Schedule(MONTHLYSCHEDULE* p)
{
    init(p);
    printf("\n\nEnter the month: ");
    scanf("%s",p->month);
    printf("\nEnter the day: ");
    int d; scanf("%d",&d);
    p->day = d;
    printf("\nEnter the Activity: ");
    scanf("%s",p->event);
    return;    
}
void Modify(MONTHLYSCHEDULE* p, int D)
{
    if(p->day != D) return;
    printf("\nChange activity into: ");
    scanf("%s",p->event);
    return;
}
void Display(MONTHLYSCHEDULE* p)
{
    printf("\n\nMonth: %s",p->month);
    printf("\nDay: %d",p->day);
    printf("\nActivity: %s",p->event);
    return;
}
int main()
{
    MONTHLYSCHEDULE* ptr = (MONTHLYSCHEDULE*)calloc(30,sizeof(MONTHLYSCHEDULE));
    printf("Enter the number of days:\n");
    int D,i; scanf("%d",&D);
    for(i = 0; i < D; i++)
    Schedule(ptr+i);
    printf("\nEnter the day to be changed");
    int d; scanf("%d",&d);
    for(i = 0; i < D; i++)
    Modify(ptr+i,d);
    printf("\n\n");
    for(i = 0; i < D; i++)
    Display(ptr+i);
    return 0;
}