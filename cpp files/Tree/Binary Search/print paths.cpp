#include<bits/stdc++.h>
using namespace std;
typedef struct bstnode *bstptr;

void insert(bstptr &, int);                     /// insert an integer value
void takeInput(bstptr &);                       /// takes input till -1
void print(int [], int);                        /// prints an array
void printAllPaths(bstptr);                     /// prints all path from root to leaf
void printAllPathsUtils(bstptr, int [], int);   /// utility function
void printLeftMostPath(bstptr);                 /// prints leftmost path
void printRightMostPath(bstptr);                /// prints rightmost path
void printSumPath(bstptr, int);                 /// prints path having sum equal to given value
void printSumPath(bstptr, string);              /// prints path having maximum or minimum sum
void printMaxOddEvenPath(bstptr, string);       /// prints path having maximum count of odd/even number
bstptr getFinalPos(bstptr, int, int);           /// returns pointer to leaf node of path having sum equal to given value
bstptr getFinalPos(bstptr, int &, int, string); /// returns pointer to leaf node of path having maximum or minimum sum
bstptr getPath(bstptr, bstptr, stack<int> &);   /// stores the path from source to destination in a stack
bstptr getFinalPosMaxOddEven(bstptr, int &, int, string type);  /// returns a pointer to leaf node of path having maximum count of odd/even

struct bstnode
{
    struct bstnode *lchild;
    int data;
    struct bstnode *rchild;
    bstnode()
    {
        lchild = NULL;
        rchild = NULL;
    }
    bstnode(int k)
    {
        lchild = NULL;
        data = k;
        rchild = NULL;
    }
};


void insert(bstptr &T, int k)
{
    if(T==NULL)
        T = new bstnode(k);
    else if(k > T->data)
        insert(T->rchild, k);
    else if(k < T->data)
        insert(T->lchild, k);
    return;
}

void takeInput(bstptr &T)
{
    while(true)
    {
        int temp;
        cin>>temp;

        if(temp == -1)
            break;
        insert(T, temp);
    }
}

void print(int a[], int n)
{
    for(int i=0;i<n;i++)
        cout<<a[i]<<" ";
    cout<<endl;
}

void printAllPathsUtils(bstptr T, int a[], int pos)
{
    if(T == NULL)
        return;
    if(T->lchild==NULL && T->rchild==NULL)
    {
        a[pos++] = T->data;
        print(a, pos);
        return;
    }
    a[pos++] = T->data;

    printAllPathsUtils(T->lchild, a, pos);
    printAllPathsUtils(T->rchild, a, pos);
    return;
}


void printAllPaths(bstptr T)
{
    int a[100];
    printAllPathsUtils(T, a, 0);
    return;
}


void printLeftMostPath(bstptr T)
{
    if(T==NULL)
        return;
    cout<<T->data<<" ";
    if(T->lchild)
        printLeftMostPath(T->lchild);
    else
        printLeftMostPath(T->rchild);
    return;
}


void printRightMostPath(bstptr T)
{
    if(T==NULL)
        return;
    cout<<T->data<<" ";
    if(T->rchild)
        printRightMostPath(T->rchild);
    else
        printRightMostPath(T->lchild);
    return;
}

bstptr getPath(bstptr src, bstptr dest, stack<int> &s)
{
    if( src==NULL)
        return src;
    if(src == dest)
    {
        s.push(src->data);
        return src;
    }

    bstptr dest1 = getPath(src->lchild, dest, s);
    bstptr dest2 = getPath(src->rchild, dest, s);

    if(dest1==dest)
    {
        s.push(src->data);
        return dest1;
    }
    if(dest2==dest)
    {
        s.push(src->data);
        return dest2;
    }
    return src;
}

bstptr getFinalPos(bstptr T, int &totalSum, int sum, string type)
{
    if(T==NULL)
        return T;
    if( (T->lchild==NULL) && (T->rchild==NULL))
    {
        if(type=="max")
        {
            if(sum+T->data > totalSum)
            {
                totalSum = sum + T->data;
                return T;
            }
        }
        else
        {
            if(sum+T->data < totalSum)
            {
                totalSum = sum + T->data;
                return T;
            }
        }

        return NULL;
    }
    bstptr temp = getFinalPos(T->lchild, totalSum, sum+T->data, type);
    bstptr temp2 = getFinalPos(T->rchild, totalSum, sum+T->data, type);

    return ( temp2==NULL ? temp : temp2);
}

void printSumPath(bstptr T, string type)
{
    int totalSum = 0;
    if(type!="max")
        totalSum = INT_MAX;
    stack<int> s;
    bstptr dest = getFinalPos(T, totalSum, 0, type);
    getPath(T, dest, s);
    while(!s.empty())
    {
        cout<<s.top()<<" ";
        s.pop();
    }
    return;
}

bstptr getFinalPos(bstptr T, int sum, int total)
{
    if(T==NULL)
        return T;

    if( (T->lchild==NULL) && (T->rchild==NULL))
    {
        if(sum+T->data == total)
            return T;
        return NULL;
    }

    bstptr temp = getFinalPos(T->lchild, sum+T->data, total);
    bstptr temp2 = getFinalPos(T->rchild, sum+T->data, total);

    return ( temp2==NULL ? temp : temp2);
}

void printSumPath(bstptr T, int total)
{
    stack<int> s;
    bstptr dest = getFinalPos(T, 0, total);
    getPath(T, dest, s);
    while(!s.empty())
    {
        cout<<s.top()<<" ";
        s.pop();
    }
    return;
}

bstptr getFinalPosMaxOddEven(bstptr T, int &totalCount, int count, string type)
{
    if(T==NULL)
        return T;

    if(type=="odd")
        count = count+ (T->data % 2);
    else
        count = count+ !(T->data % 2);
    if( (T->lchild==NULL) && (T->rchild==NULL))
    {
        if(type=="odd")
        {
            if(count > totalCount)
            {
                totalCount = count;
                return T;
            }
        }
        else
        {
            if(count > totalCount)
            {
                totalCount = count;
                return T;
            }
        }

        return NULL;
    }
    bstptr temp = getFinalPosMaxOddEven(T->lchild, totalCount, count, type);
    bstptr temp2 = getFinalPosMaxOddEven(T->rchild, totalCount, count, type);

    return ( temp2==NULL ? temp : temp2);
}

void printMaxOddEvenPath(bstptr T, string type)
{
    int totalCount = 0;
    stack<int> s;
    bstptr dest = getFinalPosMaxOddEven(T, totalCount, 0, type);
    getPath(T, dest, s);
    while(!s.empty())
    {
        cout<<s.top()<<" ";
        s.pop();
    }
    return;
}

int main()
{
    bstptr T = NULL, temp;
    int k;
    takeInput(T);
    printAllPaths(T);
    printLeftMostPath(T);           cout<<endl;
    printRightMostPath(T);          cout<<endl;
    printSumPath(T, "max");         cout<<endl;
    printSumPath(T, "min");         cout<<endl;
    printSumPath(T, 22);            cout<<endl;
    printMaxOddEvenPath(T, "even"); cout<<endl;
    printMaxOddEvenPath(T, "odd");  cout<<endl;
    return 0;
}
