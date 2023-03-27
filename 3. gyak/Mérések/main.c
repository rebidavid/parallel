#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 5

void arrf(int arr[], int n);
int sumf(int arr[], int n);
int maxf(int arr[], int n);
int minf(int arr[], int n);

int max(int a, int b);
int findMaxRec(int arr[], int n);
int min(int a, int b);
int findMinRec(int arr[], int n);

int sumRec(int arr[], int n);

int main(){
    int n=N;
    int arr[n];
    int sum;

    arrf(arr,n);
    sum=sumf(arr,n);
    printf("Sum: %d\n", sum);

    int max, min;

    max=maxf(arr,n);
    printf("Max: %d\n", max);

    min=minf(arr,n);
    printf("Min: %d\n", min);

    n = sizeof(arr)/sizeof(arr[0]);
    printf("Largest in given array is %d\n", findMaxRec(arr, n));
    printf("Smallest in given array is %d\n", findMinRec(arr, n));

    int sum_rec;
    sum_rec=sumRec(arr,n);
    printf("Recursive sum: %d\n", sum_rec);

    return 0;
}
void arrf(int arr[], int n){
    int i;
    for ( i = 0; i < n; i++)
    {
        arr[i]=i+1;
        printf("%d.element:%d\n", i+1, arr[i]);
    }   
}
int sumf(int arr[], int n){
    int i, sum=0;
    for ( i = 0; i < n; i++)
    {
        sum+=arr[i];
    }   

    return sum;
    
}
int maxf(int arr[],int n){
    int i, max;
    max=arr[0];
    for ( i = 0; i < n; i++)
    {
        if(arr[i]>max){
            max=arr[i];
        }
    }
    return max;
}
int minf(int arr[],int n){
    int i, min;
    min=arr[0];
    for ( i = 0; i < n; i++)
    {
        if(arr[i]<min){
            min=arr[i];
        }
    }
    return min;
}
int max(int a, int b){

    return a>b?a:b;
}

int findMaxRec(int arr[], int n)
{
    if (n == 1)
        return arr[0];
    return max(arr[n-1], findMaxRec(arr, n-1));
}

int min(int a, int b){

    return a<b?a:b;
}
int findMinRec(int arr[], int n)
{
    if (n == 1)
        return arr[0];
    return min(arr[n-1], findMinRec(arr, n-1));
}

int sumRec(int arr[], int n){
    if(0>=n){
        return 0;
    }
    return (sumRec(arr, n-1)+arr[n-1]);
}