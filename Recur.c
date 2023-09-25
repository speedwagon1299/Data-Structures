#include <stdlib.h>
#include <stdio.h>
static int count = 0;
int fibo(int a)
{
    if(a <= 1)  return a;
    return fibo(a-1) + fibo(a-2);
}
int binary_search(int low, int high, int arr[], int search)
{
    int mid = low + (high-low)/2;
    if(low > high)  return -1;
    else if(arr[mid] == search) return mid;
    else if(search > arr[mid])  return binary_search(mid+1,high,arr,search);
    return binary_search(low,mid-1,arr,search);
}
void hanoi(int n,char start, char end, char inter)
{
    if(n == 1)
    {
        printf("Move Disk %d from  %c to %c.\n",n,start,end);
        count++;
        return;
    }
    hanoi(n-1,start,inter,end);
    printf("Move Disk %d from  %c to %c.\n",n,start,end);
    count++;
    hanoi(n-1,inter,end,start);
}
int str_len(char* str)
{
    static int len = 0;
    if(*str == '\0')    return len;
    len++;
    return str_len(++str);
}
int main()
{
    // hanoi(5,'A','B','C');
    // printf("%d",count);
    char* str = (char*)malloc(10*sizeof(char));
    scanf("%[^\t]s",str);
    printf("\nSize: %d",str_len(str));
    return 0;
}