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

int findIndex(vector<bstptr> v, bstptr k)
{
    for(int i=0;i<v.size();i++)
    {
        if(v[i]==k)
            return i;
    }
    return INT_MAX;
}
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

void print(int k, int n, queue<char> &q, bool lef, bool righ)
{
    for(int i=0;i<n; i++)
    {
        cout<<setw(2)<<" ";
        q.push(' ');
        q.push(' ');
    }

    if(k== -1)
    {
        cout<<setw(2)<<" ";
        q.push(' ');
        //q.push(' ');
        q.push(' ');
    }

    else
    {
        cout<<setw(2)<<k;
        if(lef)
            q.push('/');
        else
            q.push(' ');

        //q.push(' ');

        if(righ)
            q.push('\\');
        else
            q.push(' ');
    }

}

void levelOrder(bstptr T, vector<bstptr> &v)
{
    queue<bstptr> q;
    q.push(T);
    q.push(new bstnode(INT_MIN));
    while(!q.empty())
    {
        bstptr temp = q.front(); q.pop();
        v.push_back(temp);
        if(temp->lchild)
            q.push(temp->lchild);
        if(temp->rchild)
            q.push(temp->rchild);
        if( q.front()->data==INT_MIN)
        {
            bstptr temp2 = q.front(); q.pop();
            if(!q.empty())
            {
                v.push_back(NULL);
                q.push(temp2);
            }
        }
    }
}

void inorderIndex(bstptr T, vector<bstptr> &v)
{
    if(T == NULL)
        return;
    inorderIndex(T->lchild, v);
    v.push_back(T);
    inorderIndex(T->rchild, v);
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


void printSlash(queue<char> &q)
{
    while(!q.empty())
    {
        cout<<q.front();
        q.pop();
    }
    cout<<endl;
}
void printAll(vector<bstptr> inorder, vector<bstptr> levelorder)
{
    int index = 0;
    int pos = 0;
    queue<char> q;
    for(int i=0;i<levelorder.size();i++)
    {
        if(levelorder[i]==NULL)
        {
            cout<<endl;
            pos = 0;
            printSlash(q);

            index = i;
        }
        else
        {
            int currPos = findIndex(inorder, levelorder[i]) ;
            print(levelorder[i]->data, currPos - pos, q, (levelorder[i]->lchild!=NULL && levelorder[i]->lchild->data != -1), (levelorder[i]->rchild!=NULL && levelorder[i]->rchild->data != -1) );
            pos = (currPos+1);

        }
    }
}

void draw(bstptr T)
{
    int i=0, h = getHeight(T);
    completeTree(T, 1, h);
    vector<bstptr> inorder, levelorder;
    inorderIndex(T, inorder);
    levelOrder(T, levelorder);
    printAll(inorder, levelorder);
}

int main()
{
    bstptr T = NULL;
    takeInput(T);
    draw(T);
    return 0;
}
