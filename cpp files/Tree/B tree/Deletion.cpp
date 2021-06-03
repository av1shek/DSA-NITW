#include<bits/stdc++.h>
using namespace std;
typedef struct bdnode *bdptr;

int M;
int MEDIAN_INDEX;
int MIN_KEY;

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

    MIN_KEY = (M-1)/2;
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

void inorderPredecessor(bdptr &BD, bdptr &predNode)
{
    if(BD==NULL)
        return;
    if( (BD->cnt>MIN_KEY) && (BD->cptr[BD->cnt] == NULL) )
        predNode = BD;
    else if( (BD->cnt>MIN_KEY) && isLeaf(BD) )
        predNode = BD;
    inorderPredecessor(BD->cptr[BD->cnt]);
}

void inorderSuccessor(bdptr &BD, bdptr &succNode)
{
    if(BD==NULL)
        return;
    if( (BD->cnt>MIN_KEY) && (BD->cptr[0] == NULL) )
        succNode = BD;
    else if( (BD->cnt>MIN_KEY) && isLeaf(BD) )
        succNode = BD;
    inorderSuccessor(BD->cptr[0]);
}

bool keyDistribution(bdptr &BD, bdptr &parent, int parentIndex, int data, int index)
{
    /// if prev child exists and more than min key
    if( (parent!=NULL) && parentIndex>0 && (parent->cptr[parentIndex-1]->cnt > MIN_KEY) )
    {
        /// shifting the data to insert in starting
        int tempIndex = index
        while(tempIndex > 0)
        {
            BD->keys[tempIndex] = BD->keys[tempIndex - 1];
            tempIndex--;
        }
        tempIndex = index+1;
        while(tempIndex > 0)
        {
            BD->cptr[tempIndex] = BD->cptr[tempIndex-1];
            tempIndex--;
        }

        bdptr prevSibling = parent->cptr[parentIndex-1];
        /// assigning data to right child
        BD->keys[0] = parent->keys[parentIndex - 1];
        BD->cptr[0] = prevSibling->cptr[prevSibling->cnt];

        /// assigning data to parent node
        parent->keys[parentIndex - 1] = prevSibling->keys[prevSibling->cnt - 1];

        /// removing data from previous sibling which was stored in last
        /// so only decrease the count
        prevSibling->cptr[prevSibling->cnt] = NULL;
        prevSibling->cnt--;

        return true;
    }
    /// if next child exists and more than min key
    else if( (parent!=NULL) && (parentIndex<M-1) && (parent->cptr[parentIndex+1] != NULL) && (parent->cptr[parentIndex+1]->cnt > MIN_KEY) )
    {
        /// shifting the data to assign the value in end
        int tempIndex = index;
        while(tempIndex < BD->cnt - 1)
        {
            BD->keys[tempIndex] = BD->keys[tempIndex+1]
            tempIndex++;
        }
        tempIndex = index+1;
        while(tempIndex < BD->cnt)
        {
            BD->cptr[tempIndex] = BD->cptr[tempIndex+1];
            tempIndex++;
        }

        /// assigning data to left child
        bdptr nextSibling = parent->cptr[parentIndex + 1];
        BD->keys[BD->cnt - 1] = parent->keys[parentIndex];
        BD->cptr[BD->cnt] = nextSibling->cptr[0];

        /// assigning data to parent node
        parent->keys[parentIndex] = nextSibling->keys[0];

        /// removing data from next sibling which was stored in first
        /// so it is to be shifted
        tempIndex = 0;
        while(tempIndex < (nextSibling->cnt - 1) )
        {
            nextSibling->keys[tempIndex] = nextSibling->keys[tempIndex + 1];
            nextSibling->cptr[tempIndex + 1] = nextSibling->cptr[tempIndex + 2];
        }
        nextSibling->cptr[nextSibling->cnt] = NULL;
        nextSibling->cnt--;
        return true;
    }
    return false;
}

void deleteStableNode(bdptr &BD, int data, int index)   /// when key is more than minimum number of key
{
    if(BD==NULL)
        return;

    if(isLeaf(BD))
    {
        BD->cptr[index + 1] = NULL;
        while(index < (BD->cnt - 1) )
        {
            BD->keys[index] = BD->keys[index + 1];
            BD->cptr[index + 1] = BD->cptr[index + 2];
            index++;
        }
        BD->cnt--;
    }
    else
    {

    }
}

void deleteUnstableNode(bdptr &BD, bdptr &parent, int parentIndex, int data, int index)  /// when key is less than minimum number of key
{
    if(BD==NULL)
        return;

    bool flag = false;
    flag = keyDistribution(BD, parent, parentIndex, data, index);
    if(flag)
        return;
    if(isLeaf(BD))
    {

    }
    else
    {

    }
}


void deleteInternalNode(bdptr &BD, bdptr &parent, int parentIndex, int data, int index)
{
    if(BD==NULL)
        return;
    bdptr predNode = NULL, succNode = NULL;
    inorderPredecessor(BD->cptr[index], predNode);
    if(pred==NULL)
        inorderSuccessor(BD, succNode);

    if(predNode != NULL)
    {
        BD->keys[index] = predNode->keys[predNode->cnt - 1];
        predNode->cptr[predNode] = NULL;
        predNode->cnt--;
    }
    else if(succNode != NULL)
    {
        BD->keys[index] = succNode->keys[0];
        succNode->cptr[0] = NULL;

        int tempIndex = 0;
        while(tempIndex < succNode->cnt - 1)
        {
            succNode->keys[tempIndex] = succNode->keys[tempIndex + 1];
            tempIndex++;
        }
        tempIndex = 0;
        while(tempIndex < succNode->cnt)
        {
            succNode->cptr[tempIndex] = succNode->cptr[tempIndex+1];
            tempIndex++;
        }
        succNode->cnt--;
    }
    else
    {

    }


}


void deleteNode(bdptr &BD, bdptr &parent, int parentIndex, int data)
{
    if(BD==NULL)
        return;

    int i;
    for(i=0;i<BD->cnt;i++)
    {
        if(data < BD->keys[i])
            deleteNode(BD->cptr[i], BD, i, data);
        else if(data == BD->keys[i])
        {
            cout<<"data found "<<endl;

            if(isLeaf(BD))
            {
                if(BD->cnt > MIN_KEY)
                    deleteStableNode(BD, data, i);
                else
                    deleteUnstableNode(BD, parent, parentIndex, data, i);
            }
            else
                deleteInternalNode(BD, parent, parentIndex, data, i);
        }
    }

    if(i==BD->cnt && (data > BD->keys[i-1]) )
        deleteNode(BD->cptr[i], BD, i, data);
}


void Delete(bdptr &BD, int data)
{
    bool flag;
    bdptr parent = NULL;
    int parentIndex = 0;
    deleteNode(BD, parent, parentIndex, data);
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

    cout<<"---------------Deleting-------------"<<endl;
    Delete(BD, 10);
    printInorder(BD); cout<<endl;
    printLevelOrder(BD);

    return 0;
}
