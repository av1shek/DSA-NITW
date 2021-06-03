#include<bits/stdc++.h>
using namespace std;
typedef struct bdnode *bdptr;
void deleteNode(bdptr &, bdptr &, int, int, bdptr &, bool &, int &);
void Delete(bdptr &, int);
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
            for(int j=0;j<temp->cnt;j++)
                cout<<temp->keys[j]<<" ";
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

int inorderPredecessor(bdptr &BD)
{
    if(isLeaf(BD))
        return BD->keys[BD->cnt - 1];
    else
        return inorderPredecessor(BD->cptr[BD->cnt]);
}

int inorderSuccessor(bdptr &BD)
{
    if(isLeaf(BD))
        return BD->keys[0];
    else
        return inorderSuccessor(BD->cptr[0]);
}


bool keyDistribution(bdptr &BD, bdptr &parent, int parentIndex, int data, int index)
{
    /// if prev child exists and more than min key
    if( (parent!=NULL) && parentIndex>0 && (parent->cptr[parentIndex-1]->cnt > MIN_KEY) )
    {
       // cout<<"key distribution with previous sibling"<<endl;
        /// shifting the data to insert in starting
        int tempIndex = index;
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
        // cout<<"key distribution with next sibling"<<endl;
        /// shifting the data to assign the value in end
        int tempIndex = index;
        while(tempIndex < BD->cnt - 1)
        {
            BD->keys[tempIndex] = BD->keys[tempIndex+1];
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
            nextSibling->cptr[tempIndex ] = nextSibling->cptr[tempIndex + 1];
            tempIndex++;
        }
        nextSibling->cptr[tempIndex ] = nextSibling->cptr[tempIndex + 1];
        nextSibling->cptr[nextSibling->cnt] = NULL;
        nextSibling->cnt--;
        return true;
    }
    return false;
}

bool replaceWithLeaf(bdptr &BD, int index)
{
    bdptr lchild = BD->cptr[index];
    bdptr rchild = BD->cptr[index+1];
    if(lchild->cnt > MIN_KEY)
    {
        int temp = inorderPredecessor(lchild);
        BD->keys[index] = temp;
        Delete(lchild, temp);
        return true;
    }
    else if(rchild->cnt > MIN_KEY)
    {
        int temp = inorderSuccessor(rchild);
        BD->keys[index] = temp;
        Delete(rchild, temp);
        return true;
    }
    return false;
}

void mergeNodeWithParent(bdptr &BD, bdptr &parent, int parentIndex, int index, bdptr &Head, int &mergedParentIndex)
{
    /// first removing the key which is to be deleted
    int tempIndex = index;
    while(tempIndex < BD->cnt - 1)
    {
        BD->keys[tempIndex] = BD->keys[tempIndex +1];
        BD->cptr[tempIndex + 1] = BD->cptr[tempIndex + 2];
        tempIndex++;
    }
    BD->cnt--;

    /// if prev child exist merge with that
    if( (parent!=NULL) && parentIndex>0)
    {
        // cout<<" merging with previous sibling "<<endl;
        mergedParentIndex = parentIndex - 1;
        bdptr node1 = parent->cptr[parentIndex - 1];

        /// assign parent keys in prev node
        int shiftedData = parent->keys[parentIndex - 1];
        node1->keys[node1->cnt] = shiftedData;
        node1->cptr[node1->cnt + 1] = BD->cptr[0];
        node1->cnt++;

        /// merging curr and prev leafs
        for(int i=0;i<BD->cnt;i++)
        {
            node1->keys[node1->cnt] = BD->keys[i];
            node1->cptr[node1->cnt + 1] = BD->cptr[i+1];
            node1->cnt++;
        }
        BD = NULL;
    }
    /// if next exist merge with next child
    else
    {
        // cout<<"merging with next sibling"<<endl;
        mergedParentIndex = parentIndex;
        bdptr node1 = parent->cptr[parentIndex + 1];

        /// assigning the parent keys in curr node
        int shiftedData = parent->keys[parentIndex];
        BD->keys[BD->cnt] = shiftedData;
        BD->cptr[BD->cnt+1] = node1->cptr[0];
        BD->cnt++;

        /// merging curr leaf and next leaf
        for(int i=0;i<node1->cnt;i++)
        {
            BD->keys[BD->cnt] = node1->keys[i];
            BD->cptr[BD->cnt + 1] = node1->cptr[i+1];
            BD->cnt++;
        }
        parent->cptr[parentIndex+1] = NULL;
    }
    return;
}
void mergeChild(bdptr BD, int index)
{
    bdptr &lchild = BD->cptr[index];
    bdptr &rchild = BD->cptr[index + 1];

    for(int i=0;i<rchild->cnt; i++)
    {
        lchild->keys[lchild->cnt] = rchild->keys[i];
        lchild->cptr[lchild->cnt + 1] = rchild->cptr[i+1];
        lchild->cnt++;
        rchild->cptr[i+1] = NULL;
    }
    rchild = NULL;
}
void deleteNode(bdptr &BD, bdptr &parent, int parentIndex, int data, bdptr &Head, bool &merged, int &mergedParentIndex)
{
    if(BD==NULL)
        return;
    if(isLeaf(BD) && parent==NULL)
    {
        int i=0;
        for(i=0;i<BD->cnt;i++)
        {
            if(BD->keys[i]==data)
            {
                while(i<BD->cnt - 1)
                {
                    BD->keys[i] = BD->keys[i+1];
                    i++;
                }
                BD->cnt--;
                break;
            }
        }
        if(BD->cnt == 0)
            BD = NULL;
    }

    int i;
    bool flag = false;
    for(i=0;i<BD->cnt;i++)
    {
        if(data < BD->keys[i])
        {
            deleteNode(BD->cptr[i], BD, i, data, Head, merged, mergedParentIndex);
            flag = true;
        }
        else if(data == BD->keys[i])
        {

            if(isLeaf(BD))
            {
                /// if count is greater than min key delete and decrease the count
                if(BD->cnt > MIN_KEY)
                {
                    //cout<<"Node has more than min key so directly deleting and decreasing the count"<<endl;
                    for(i=0;i<BD->cnt;i++)
                    {
                        if(BD->keys[i]==data)
                        {
                            while(i<BD->cnt - 1)
                            {
                                BD->keys[i] = BD->keys[i+1];
                                i++;
                            }
                            BD->cnt--;
                            break;
                        }
                    }
                }
                /// if count is less than min key then first check key distribution
                /// if not possible then merge the node
                else if( !keyDistribution(BD, parent, parentIndex, data, i) )
                {
                    // cout<<"Key distribution is not possible so merging"<<endl;
                    mergeNodeWithParent(BD, parent, parentIndex, i, Head, mergedParentIndex);
                    merged = true;
                }

            }
            else
            {
                if(!replaceWithLeaf(BD, i) )
                {
                    // cout<<"can not be replaced with either of predecessor or successor"<<endl;
                    mergeChild(BD, i);
                    mergeNodeWithParent(BD, parent, parentIndex, i, Head, mergedParentIndex);
                    merged = true;
                }
                else
                {
                    // cout<<"replaced with predecessor or successor"<<endl;
                }

            }

            break;
        }
    }

    if( (BD!=NULL) && (i==BD->cnt) && (data > BD->keys[i-1]) )
    {
        deleteNode(BD->cptr[i], BD, i, data, Head, merged, mergedParentIndex);
        flag = true;
    }
    if( flag && merged )
    {
        //cout<<"recursively managing parent node"<<endl;
        merged = false;
        /// simply remove the key and adjust the pointer
        if( (BD->cnt==1) && (parent==NULL))
        {
            BD = BD->cptr[0];
        }
        else if(BD->cnt > (MIN_KEY + 1))
        {
            // cout<<" recursive parent has more than min key so just deleting and decreasing the count "<<endl;
            int tempIndex = mergedParentIndex;
            /// shifting the data of parent node
            while( tempIndex < BD->cnt -1 )
            {
                BD->keys[tempIndex] = BD->keys[tempIndex + 1];
                BD->cptr[tempIndex + 1] = BD->cptr[tempIndex + 2];
                tempIndex++;
            }
            BD->cnt--;
        }
        else if(!keyDistribution(BD, parent, parentIndex, data, mergedParentIndex))
        {
            // cout<<"recursively merging the parent"<<endl;
            mergeNodeWithParent(BD, parent, parentIndex, mergedParentIndex, Head, mergedParentIndex);
            merged=true;
        }
        else
        {
            // cout<<"recursively key distribution has been done"<<endl;
        }

    }
    return;
}

void Delete(bdptr &BD, int data)
{
    bool merged = false;
    int mergedParentIndex = -1;
    bdptr parent = NULL;
    int parentIndex = 0;
    deleteNode(BD, parent, parentIndex, data, BD, merged, mergedParentIndex);
}


int main()
{
    //cin>>M;
    M = 5;
    int temp;
    treeType();

    bdptr BD = NULL;
    takeInput(BD);

    cin>>temp;  Delete(BD, temp);
    cin>>temp;  Delete(BD, temp);
    cin>>temp;  Delete(BD, temp);
    cin>>temp;  Delete(BD, temp);
    cin>>temp;  Delete(BD, temp);
    printLevelOrder(BD);
    return 0;
}
