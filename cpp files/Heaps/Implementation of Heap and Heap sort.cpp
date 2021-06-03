#include<iostream>
using namespace std;


void print(int arr[], int n)
{
    for(int i=0;i<n;i++)
        cout<<arr[i]<<" ";
    cout<<endl;
}

void insertMinHeap(int H[], int &size, int data, int max_size)
{
    if(size >= max_size)
    {
        cout<<"Max limit reached "<<endl;
        return;
    }
    H[size] = data;
    int temp = size;

    while( (temp-1)/2 >= 0)
    {
        if(H[temp] < H[(temp-1)/2])
            swap(H[temp], H[(temp-1)/2]);
        else
            break;
        temp = (temp-1)/2;
    }
    size++;
    return;
}


void insertMaxHeap(int H[], int &size, int data, int max_size)
{
    if(size >= max_size)
    {
        cout<<"Max limit reached "<<endl;
        return;
    }
    H[size] = data;
    int i = size;

    while( (i-1)/2 >= 0)
    {
        if(H[i] > H[(i-1)/2])
            swap(H[i], H[(i-1)/2]);
        else
            break;
        i = (i-1)/2;
    }
    size++;
    return;
}

void takeInputMinHeap(int H[], int &size, int max_size)
{
    if(size >= max_size)
    {
        cout<<"Max limit reached "<<endl;
        return;
    }
    while(true)
    {
        int temp;
        cin>>temp;
        if(temp == -1)
            break;
        insertMinHeap(H, size, temp, max_size);
    }
}

void takeInputMaxHeap(int H[], int &size, int max_size)
{
    if(size >= max_size)
    {
        cout<<"Max limit reached "<<endl;
        return;
    }
    while(true)
    {
        int temp;
        cin>>temp;
        if(temp == -1)
            break;
        insertMaxHeap(H, size, temp, max_size);
    }
}

int pop_frontMinHeap(int H[], int &size)
{
    if(size<=0)
    {
        cout<<"Empty"<<endl;
        return INT_MAX;
    }
    int temp = H[0];
    size--;
    H[0] = H[size];

    int i = 0;
    while( (2*i +2 < size ) || (2*i+1 < size) )
    {
        int j;
        if( 2*i+2 >= size)
            j = 2*i +1;
        else
            j = ( H[2*i +1] > H[2*i +2 ] ? (2*i+2) : (2*i+1) );
        if(H[i]>H[j])
            swap(H[i], H[j]);
        else
            break;
        i = j;
    }
    return temp;
}

int pop_frontMaxHeap(int H[], int &size)
{
    if(size<=0)
    {
        cout<<"Empty"<<endl;
        return INT_MAX;
    }
    int temp = H[0];
    size--;
    H[0] = H[size];

    int i = 0;
    while( (2*i +2 < size ) || (2*i+1 < size) )
    {
        int j;
        if( 2*i+2 >= size)
            j = 2*i +1;
        else
            j = ( H[2*i +1] < H[2*i +2 ] ? (2*i+2) : (2*i+1) );
        if(H[i]<H[j])
            swap(H[i], H[j]);
        else
            break;
        i = j;
    }
    return temp;
}


void heapifyMin(int arr[], int n, int i=0)
{
    if(2*i+1 >=n)
        return;
    heapifyMin(arr, n, 2*i+1);
    heapifyMin(arr, n, 2*i+2);

    while( (2*i +2 < n ) || (2*i+1 < n) )
    {
        int j;
        if( 2*i+2 >= n)
            j = 2*i +1;
        else
            j = ( arr[2*i +1] > arr[2*i +2 ] ? (2*i+2) : (2*i+1) );
        if(arr[i]>arr[j])
            swap(arr[i], arr[j]);
        else
            break;
        i = j;
    }
}

void heapifyMax(int arr[], int n, int i=0)
{
    if(2*i+1 >=n)
        return;
    heapifyMax(arr, n, 2*i+1);
    heapifyMax(arr, n, 2*i+2);

    while( (2*i +2 < n ) || (2*i+1 < n) )
    {
        int j;
        if( 2*i+2 >= n)
            j = 2*i +1;
        else
            j = ( arr[2*i +1] < arr[2*i +2 ] ? (2*i+2) : (2*i+1) );
        if(arr[i]<arr[j])
            swap(arr[i], arr[j]);
        else
            break;
        i = j;
    }
}

void heapSortAsc(int arr[], int n)
{
    heapifyMax(arr, n);

    int size = n;
    for(int i=0;i<n;i++)
    {
        swap(arr[0], arr[size-1] );
        size--;
        heapifyMax(arr, size);
    }
}


void heapSortDesc(int arr[], int n)
{
    heapifyMin(arr, n);

    int size = n;
    for(int i=0;i<n;i++)
    {
        swap(arr[0], arr[size-1] );
        size--;
        heapifyMin(arr, size);
    }
}

bool isMinHeap(int arr[], int n, int i=0)
{
    if(2*i+1 >=n)
        return true;

    if( (2*i+2) < n)
        if( arr[i] >= min(arr[2*i +1], arr[2*i+2]))
            return false;
    if( arr[i] >= arr[2*i +1])
        return false;
    return ( isMinHeap(arr, n, 2*i+1) && isMinHeap(arr, n, 2*i+2));
}


bool isMaxHeap(int arr[], int n, int i=0)
{
    if(2*i+1 >=n)
        return true;

    if( (2*i+2) < n)
        if( arr[i] <= max(arr[2*i +1], arr[2*i+2]))
            return false;
    if( arr[i] <= arr[2*i +1])
        return false;
    return ( isMaxHeap(arr, n, 2*i+1) && isMaxHeap(arr, n, 2*i+2));
}


int main()
{
    int H[100];
    int size = 0;
    takeInputMinHeap(H, size, 100);
    print(H, size);
    while(size!=0)
        cout<<pop_frontMinHeap(H, size)<<" ";


    /*int arr[] = {5, 9, 3, 6, 2, 4, 8, 1, 7};
    int n = sizeof(arr)/sizeof(arr[0]);
    heapSortDesc(arr, n);
    cout<<"Descending ";  print(arr,n);
    heapSortAsc(arr, n);
    cout<<"Ascending ";  print(arr,n);*/

    /*
    int arr1[] = {1,2,5,3,6,4,8,9,7};
    int n1 = sizeof(arr1)/sizeof(arr1[0]);
    cout<<"Min Heap = "<< isMinHeap(arr1, n1)<<endl;
    cout<<"Max Heap = "<< isMaxHeap(arr1, n1)<<endl<<endl;

    int arr2[] = {1,2,3,6,5,4,8,9,7};
    int n2 = sizeof(arr2)/sizeof(arr2[0]);
    cout<<"Min Heap = "<< isMinHeap(arr2, n2)<<endl;
    cout<<"Max Heap = "<< isMaxHeap(arr2, n2)<<endl<<endl;

    int arr3[] = {9,7,8,6,5,4,3,1,2};
    int n3 = sizeof(arr3)/sizeof(arr3[0]);
    cout<<"Min Heap = "<< isMinHeap(arr3, n3)<<endl;
    cout<<"Max Heap = "<< isMaxHeap(arr3, n3)<<endl<<endl;
    */
    return 0;
}
/// 5 9 3 6 2 4 8 1 7 -1
/// 12, 20,2, 13, 32, 50, 88, 21, 18, 91
