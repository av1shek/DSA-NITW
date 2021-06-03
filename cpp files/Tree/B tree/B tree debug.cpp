#include<bits/stdc++.h>
using namespace std;
typedef struct bdnode *bdptr;

int M;
struct bdnode
{
    int cnt;
    int *keys = new int[M-1];
    bdptr *cptr = new bdptr[M];

    bdnode()
    {
        for(int i=0; i<M; i++)
            cptr[i] = NULL;
        cnt = 0;
    }
};


bool isLeaf(bdptr BD)
{
    if(BD==NULL)
        return false;
    for(int i=0; i<M-1; i++)
        if(BD->cptr[i] != NULL)
            return false;
    return true;
}

bool isOverflow(bdptr BD)
{
    if(BD==NULL)
        return false;

    if(BD->cnt >= M-1)
        return true;

    return false;
}


void printInorder(bdptr T)
{
    if(T==NULL)
        return;


    for(int i=0;i<T->cnt;i++)
    {
        printInorder(T->cptr[i]);
        cout<<T->keys[i]<<"("<< T->cnt<<")"<<" ";
    }
    printInorder(T->cptr[T->cnt]);
}

/*
void split(bdptr &BD, int retData, bdptr &newNode, int *overflowKeys, bdptr *overflowCptrs)
{
    newNode = new bdnode;

    int medianIndex = M/2 - 1; /// ----- when m is even left biased;
    /// int medianIndex = M/2;  /// ----- when m is odd or even and right biased

    retData = overflowKeys[medianIndex];

    for(int i=medianIndex+1, j=0; i<M; i++,j++)
        newNode->keys[j] = overflowKeys[i];

    BD->cnt = medianIndex;

    for(int i=medianIndex+1, j=0; i<M+1; i++, j++)
        newNode->cptr[j] = overflowCptrs[i];

    for(int i=BD->cnt+1; i<M; i++)
        BD->cptr[i] = NULL;
}
*/

void insert(bdptr &BD, int data, int &retData, bdptr &newNode)
{
    if(BD==NULL)
    {
        BD = new bdnode;
        BD->cnt++;
        BD->keys[0] = data;
        return;
    }

    if(isLeaf(BD))
    {
        if(isOverflow(BD))
        {
            int *overflowKeys = new int[M] {0};

            for(int j=0; j<M-1; j++)
                overflowKeys[j] = BD->keys[j];

            overflowKeys[M-1] = data;

            int index = M - 1;

            while(index > 0)
            {
                if(overflowKeys[index] < overflowKeys[index-1])
                    swap(overflowKeys[index], overflowKeys[index-1]);
                else
                    break;
                index--;
            }

            newNode = new bdnode;

            int medianIndex = M/2 - 1; /// ----- when m is even left biased;
            /// int medianIndex = M/2;  /// ----- when m is odd or even and right biased

            retData = overflowKeys[medianIndex];
            cout<<"overflow keys "<<endl;
            for(int i=0;i<M;i++)
                cout<<overflowKeys[i]<<" ";
            cout<<endl;

            for(int i=0; i<medianIndex; i++)
                BD->keys[i] = overflowKeys[i];

            for(int i=medianIndex+1, j=0; i<M; i++,j++, newNode->cnt++)
                newNode->keys[j] = overflowKeys[i];

            BD->cnt = medianIndex;
        }
        else
        {
            int index = BD->cnt;
            BD->keys[index] = data;

            while(index>0)
            {
                if(BD->keys[index] < BD->keys[index-1])
                    swap(BD->keys[index], BD->keys[index-1]);
                else
                    break;
                index--;
            }


            BD->cnt++;
        }
    }
    else
    {
        int i;
        for(i=0; i<BD->cnt; i++)
        {
            if(data < BD->keys[i])
            {
                insert(BD->cptr[i], data, retData, newNode);
                break;
            }
        }
        if(i==BD->cnt)
            insert(BD->cptr[i], data, retData, newNode);

        if(newNode == NULL)
            return;

        if(isOverflow(BD))
        {
            /// ----------------------
            int *overflowKeys = new int[M] {0};
            bdptr *overflowCptrs = new bdptr[M+1] {NULL};

            for(int j=0; j<M-1; j++)
                overflowKeys[j] = BD->keys[j];
            for(int j=0; j<M; j++)
                overflowCptrs[j] = BD->cptr[j];

            overflowKeys[M-1] = retData;
            overflowCptrs[M]  = newNode;

            int index = M - 1;
            int tempIndex = index;
            while(tempIndex > i)
            {
                swap(overflowKeys[tempIndex], overflowKeys[tempIndex-1]);
                tempIndex--;
            }

            tempIndex = index + 1;
            while(tempIndex > i+1)
            {
                swap(overflowCptrs[tempIndex], overflowCptrs[tempIndex-1]);
                tempIndex--;
            }

            newNode = new bdnode;

            int medianIndex = M/2 - 1; /// ----- when m is even left biased;
            /// int medianIndex = M/2;  /// ----- when m is odd or even and right biased

            retData = overflowKeys[medianIndex];

            for(int i=0; i<medianIndex; i++)
                BD->keys[i] = overflowKeys[i];
            for(int i=0; i<(medianIndex+1); i++)
                BD->cptr[i] = overflowCptrs[i];
            for(int i=medianIndex+1; i<M; i++)
                BD->cptr[i] = NULL;

            BD->cnt = medianIndex;
            for(int i=medianIndex+1, j=0; i<M; i++,j++, newNode->cnt++)
                newNode->keys[j] = overflowKeys[i];

            for(int i=medianIndex+1, j=0; i<(M+1); i++, j++)
                newNode->cptr[j] = overflowCptrs[i];

        }
        else
        {
            int index = BD->cnt;
            BD->keys[index] = retData;
            BD->cptr[index+1] = newNode;

            int tempIndex = index;
            while(tempIndex > i)
            {
                swap(BD->keys[tempIndex], BD->keys[tempIndex-1]);
                tempIndex--;
            }

            tempIndex = index + 1;
            while(tempIndex > i+1)
            {
                swap(BD->cptr[tempIndex], BD->cptr[tempIndex-1]);
                tempIndex--;
            }

            BD->cnt++;
            newNode = NULL;
        }

    }

}

void takeInput(bdptr &BD)
{
    int cnt = 10;
    cin>>cnt;
    while(cnt--)
    {
        int data;
        int retVal;
        bdptr newNode = NULL;
        cin>>data;
        insert(BD, data, retVal, newNode);
        if( newNode != NULL )
        {
            bdptr temp = new bdnode;
            temp->keys[0] = retVal;
            temp->cptr[0] = BD;
            temp->cptr[1] = newNode;
            temp->cnt++;
            cout<<" ------------------------------------------------\n";
            cout<<"changing head node"<<endl;
            cout<<"current head node value = "<<temp->keys[0]<<endl;
            cout<<"inorder left = ";printInorder(temp->cptr[0]); cout<<endl;
            cout<<"inorder right = ";printInorder(temp->cptr[1]); cout<<endl;
            cout<<" ------------------------------------------------\n";

            BD = temp;
        }
        cout<<"-------------------------------------------------------------"<<endl;
        printInorder(BD); cout<<endl;
        cout<<"-------------------------------------------------------------"<<endl;
    }
}



int main()
{
    //cin>>M;
    M = 4;
    bdptr BD = NULL;
    takeInput(BD);
    printInorder(BD);
    return 0;
}
