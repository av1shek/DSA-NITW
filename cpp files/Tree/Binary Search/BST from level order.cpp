#include<bits/stdc++.h>
using namespace std;
typedef struct bstnode *bstptr;

void takeInput(bstptr &);           /// takes input till -1
void insert(bstptr &, int);         /// insert a integer value


struct bstnode
{
    struct bstnode *lchild;
    int data;
    int x;
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

void buildTreeLevelOrder(bstptr &T)
{
    T = new bstnode;
    bstptr t = new bstnode;
    cin>>T->data;
    queue<bstptr> q;
    q.push(T);
    q.push(new bstnode(INT_MIN));
    q.push(new bstnode(INT_MAX));

    cin>>t->data;
    if(t->data == -1)
        return;

    while(true)
    {
        bstptr frontNode =   q.front();  q.pop();
        bstptr low = q.front(); q.pop();
        bstptr high = q.front(); q.pop();

        if(t->data > low->data && t->data < frontNode->data)
        {
            frontNode->lchild = new bstnode(t->data);
            q.push(frontNode->lchild);
            q.push(low);
            q.push(new bstnode(frontNode->data));

            cin>>t->data;
            if(t->data == -1)
                break;
        }
        if(t->data > frontNode->data && t->data < high->data )
        {
            frontNode->rchild = new bstnode(t->data);
            q.push(frontNode->rchild);
            q.push(new bstnode(frontNode->data));
            q.push(high);

            cin>>t->data;
            if(t->data == -1)
                break;

        }
    }
}


void print(bstptr temp)
{
    for(int i=1;i<=temp->x; i++)
        cout<<setw(2)<<" ";
    if(temp->data != -1)
        cout<<setw(2)<<temp->data;
    else
        cout<<setw(2)<<"_";
}

void printLevelOrder(bstptr T)
{
    queue<bstptr> q;
    q.push(T);
    bstptr temp = new bstnode;
    temp->data = INT_MIN;
    q.push(temp);
    int pos = 0;
    while(!q.empty())
    {
        temp = q.front(); q.pop();
        temp->x -= (pos);
        pos += temp->x+1;
        print(temp);
        if(temp->lchild)
            q.push(temp->lchild);
        if(temp->rchild)
            q.push(temp->rchild);
        if( q.front()->data==INT_MIN)
        {
            bstptr temp2 = q.front(); q.pop();
            if(!q.empty())
            {
                cout<<endl;
                pos = 0;
                q.push(temp2);
            }
        }
    }
}

void inorderIndex(bstptr T, int &i)
{
    if(T == NULL)
        return;
    inorderIndex(T->lchild, i);
    T->x = i++;
    inorderIndex(T->rchild, i);
    return;
}
int getHeight(bstptr T)
{
    if(T==NULL)
        return 0;
    return max(getHeight(T->lchild), getHeight(T->rchild)) + 1;
}
void completeTree(bstptr &T, int currH, int height)
{
    if(currH == height)
    {
        if(T == NULL)
            T = new bstnode(-1);
        return;
    }
    if(T->lchild == NULL)
        T->lchild = new bstnode(-1);
    if(T->rchild == NULL)
        T->rchild = new bstnode(-1);
    completeTree(T->lchild, currH+1, height);
    completeTree(T->rchild, currH+1, height);
    return;
}

void draw(bstptr T)
{
    int i=0, h = getHeight(T);
    completeTree(T, 1, h);
    inorderIndex(T, i);
    printLevelOrder(T);
}
int main()
{
    bstptr T = NULL;
    buildTreeLevelOrder(T);
    cout<<"check"<<endl;
    draw(T);


    return 0;
}
