#include<bits/stdc++.h>
using namespace std;
typedef struct bdnode *bdptr;
typedef struct ovNode *ovptr;

int M;
int MEDIAN_INDEX;
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

void treeType(char type='R')
{
    if( M%2 || (type=='R') || (type=='r'))
        MEDIAN_INDEX = M/2;
    else
        MEDIAN_INDEX = M/2 -1;
}

void printInorder(bdptr T)
{
    if(T==NULL)
        return;


    for(int i=0;i<T->cnt;i++)
    {
        printInorder(T->cptr[i]);
        cout<<T->keys[i]<<" ";
    }
    printInorder(T->cptr[T->cnt]);
}

void printLevelOrder(bdptr BD)
{
    if(BD==NULL)
        return;
    queue<bdptr> q;
    q.push(BD);

    while(!q.empty())
    {
        int n = q.size();
        for(int i=0;i<n;i++)
        {
            bdptr temp = q.front(); q.pop();
            cout<<"(";
            for(int j=0;j<temp->cnt;j++)
                cout<<temp->keys[j]<<" ";
            cout<<")";
            for(int j=0;j<=temp->cnt;j++)
            {
                if(temp->cptr[j])
                    q.push(temp->cptr[j]);
            }
        }
        cout<<endl;
    }
}


void insertInNode(bdptr &BD, int &data, bdptr &newNode)
{
    int *overflowKeys = new int[M] {0};
    bdptr *overflowCptrs = new bdptr[M+1] {NULL};
    int index = BD->cnt;

    /// copying the data in overflow node
    for(int i=0; i<index; i++)
        overflowKeys[i] = BD->keys[i];
    for(int i=0; i<=index; i++)
        overflowCptrs[i] = BD->cptr[i];

    /// assigning the data to be inserted
    overflowKeys[index] = data;
    overflowCptrs[index + 1]  = newNode;

    /// sorting the overflow node along with pointers
    int currIndex = index;
    while(currIndex>0)
    {
        if(overflowKeys[currIndex] < overflowKeys[currIndex - 1])
        {
            swap(overflowKeys[currIndex], overflowKeys[currIndex - 1]);
            swap(overflowCptrs[currIndex+1], overflowCptrs[currIndex]);
        }
        else
            break;
        currIndex--;
    }

    /// if node was not full then no need to split
    if(index < M-1)
    {
        index++;
        for(int i=0; i<index; i++)
            BD->keys[i] = overflowKeys[i];
        for(int i=0; i<=index; i++)
            BD->cptr[i] = overflowCptrs[i];
        BD->cnt++;
        newNode=NULL;
        return;
    }

    /// node is full and need to split

    /// assigning the data and pointer to be returned
    int medianIndex = MEDIAN_INDEX;
    data = overflowKeys[medianIndex];
    newNode = new bdnode;

    /// copying half of the data in original node;
    for(int i=0; i<medianIndex; i++)
        BD->keys[i] = overflowKeys[i];


    for(int i=0; i<(medianIndex+1); i++)
        BD->cptr[i] = overflowCptrs[i];
    for(int i=medianIndex+1; i<M; i++)
        BD->cptr[i] = NULL;
    BD->cnt = medianIndex;

    /// copying other half data in newNode
    for(int i=medianIndex+1, j=0; i<M; i++,j++, newNode->cnt++)
        newNode->keys[j] = overflowKeys[i];
    for(int i=medianIndex+1, j=0; i<(M+1); i++, j++)
        newNode->cptr[j] = overflowCptrs[i];

}

void insert(bdptr &BD, int &data, bdptr &newNode)
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
        insertInNode(BD, data, newNode);

    }
    else
    {
        int i;
        for(i=0; i<BD->cnt; i++)
            if(data < BD->keys[i]){
                insert(BD->cptr[i], data, newNode);
                break;
            }
        if(i==BD->cnt)
            insert(BD->cptr[i], data, newNode);

        if(newNode!=NULL)
            insertInNode(BD, data, newNode);
    }
}

void takeInput(bdptr &BD)
{
    while(true)
    {
        int data;
        bdptr newNode=NULL;
        cin>>data;

        if(data == 0)
            break;
        insert(BD, data, newNode);
        if(newNode != NULL)
        {
            bdptr temp = new bdnode;
            temp->keys[0] = data;
            temp->cptr[0] = BD;
            temp->cptr[1] = newNode;
            temp->cnt++;
            BD = temp;
        }
    }
}

int main()
{
    //cin>>M;
    M = 3;
    treeType();
    bdptr BD = NULL;
    takeInput(BD);
    printInorder(BD); cout<<endl;
    printLevelOrder(BD);

    return 0;
}
