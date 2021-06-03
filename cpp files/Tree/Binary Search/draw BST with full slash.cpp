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

void print(int k, int n, queue<char> &q, bstptr lef, bstptr righ)
{
    for(int i=0;i<n; i++)
    {
        cout<<setw(2)<<" ";
        q.push(' ');
        q.push(' ');
    }

        if(k==-1)
            cout<<"  ";
        else
            cout<<setw(2)<<k;
        if(lef)
        {
            if(lef->data == -1)
                q.push('f');
            else
                q.push('/');
        }
        if(righ)
        {
            if(righ->data == -1)
                q.push('b');
            else
                q.push('\\');
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


void printSlash(queue<char> &q, int currPos, int len)
{
    deque<char> q2;
    while(currPos<len-2)
    {
        q.push(' ');
        q.push(' ');
        currPos++;
    }
    while(!q.empty())
    {
        if(q.front() != 'f' && q.front()!='b')
            cout<<q.front();
        else
            cout<<" ";
        q2.push_back(q.front());
        q.pop();
    }
    cout<<endl;

    q2.push_back('#');
    while(!q2.empty())
    {
        char temp = q2.front();
        if(temp == '#')
        {
            cout<<endl;
            q2.pop_front();
            if(!q2.empty())
                q2.push_back('#');
            continue;
        }

        q2.pop_front();
        if(!q2.empty() && (q2.front() == '/' || q2.front()=='f') && temp == ' ')
            continue;

        if(temp == '\\' || temp=='b')
        {
            cout<<" ";
            cout << ( temp == 'b' ? ' ' : temp);

            q2.push_back(' ');
            q2.push_back(temp);
            if(q2.front() == ' ')
                q2.pop_front();
            else if(q2.empty() || q2.front() == '#')
            {
                cout<<endl;
                return;

            }
        }

        else if(temp == '/' || temp=='f')
        {
            cout << ( temp == 'f' ? ' ' : temp);
            cout<<' ';
            q2.push_back(temp);
            q2.push_back(' ');
        }
        else
        {
            cout<<temp;
            q2.push_back(temp);
        }


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
            int currPos;
            if(levelorder[i-1]->rchild != NULL)
            currPos = findIndex(inorder, levelorder[i-1]->rchild);
            else
                currPos = findIndex(inorder, levelorder[i-1]->lchild);
            printSlash(q, currPos, inorder.size());
            pos = 0;
            index = i;
        }
        else
        {
            int currPos = findIndex(inorder, levelorder[i]) ;
            print(levelorder[i]->data, currPos - pos, q, (levelorder[i]->lchild), (levelorder[i]->rchild) );
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

/// 50 30 80 10 40 60 90 20 70 -1
/// 50 30 80 10 40 90 20 -1

/// 8 3 10 1 6 9 14 0 2 4 7 13 15 -1
