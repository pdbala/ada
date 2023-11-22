#include <iostream>
#include<omp.h>

using namespace std;


void swap(int *a, int *b)
{
    int t=*a;
    *a=*b;
    *b=t;
}

int partition(int arr[],int start,int end)
{
    int pivot =arr[end];
    int i=start-1;
    for (int j=start;j<end;j++)
    {
        if (arr[j]<pivot)
        {
            i++;
            swap(&arr[i],&arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[end]);
    return i+1;
}

void quicksort(int arr[],int start,int end)
{
    int index;
    if(start<end)
    {
        index = partition(arr,start,end);
        #pragma omp parallel sections
        {
            #pragma omp section
            {
                quicksort(arr,start,index-1);
            }
            #pragma omp section
            {
                quicksort(arr,index+1,start);
            }
        }
    }
}


int main()
{
    int n;
    cout<<"Enter Number of elements:";
    cin>>n;
    cout<<"Enter "<<n<<" elements:\n";
    int arr[n];
    for(int i=0;i<n;i++)
    {
        cin>>arr[i];
    }
    quicksort(arr,0,n-1);
    cout<<"Sorted array:\n";
    for(int i=0;i<n;i++)
    {
        cout<<arr[i]<<" ";
    }
    return 0;
}
