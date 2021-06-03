
#include<bits/stdc++.h>
using namespace std;

void insert(int H[], int data, int &size)
{
     H[size] = data;
    int temp = size;

    while( (temp-1)/4 >= 0)
    {
        if(H[temp] < H[(temp-1)/4])
            swap(H[temp], H[(temp-1)/4]);
        else
            break;
        temp = (temp-1)/4;
    }
    size++;
    return;
}
/*
int comp(int H[], int i, int size)
{
    n = i+4;
    int index = i;
    int mini = H[i];
    for( ; i<min(n, size); i++)
        if(H[i]<mini)
        {
            mini = H[i]
            index = i;
        }
    return index;
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
*/
void takeInput(int H[], int &size)
{
    while(true)
    {
        int temp;
        cin>>temp;
        if(temp == -1)
            break;
        insert(H, temp, size);
    }
}

void printLevelOrder(int H[], int size)
{
    int i = 0;
    int level = 0;
    while(i<size)
    {
        for( ; i<=min(size-1, int(pow(4, level))); i++)
            cout<<H[i]<<" ";
        cout<<endl;
        level++;
    }
}
int main()
{
    int H[100];
    int size = 0;
    takeInput(H, size);
    printLevelOrder(H, size);
    return 0;
}

/// 3 18 54 6 8 25 45 63 81 1 3 10 12 30 36 72 75 90 -1
