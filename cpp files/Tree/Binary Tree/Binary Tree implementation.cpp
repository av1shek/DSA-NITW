#include<bits/stdc++.h>
using namespace std;
typedef struct btnode *btptr;

struct btnode
{
    btptr lchild;
    char data;
    btptr rchild;

    btnode()
    {
        lchild = NULL;
        rchild = NULL;
    }
    btnode(char k)
    {
        lchild = NULL;
        data = k;
        rchild = NULL;
    }
};

void insertChilds(btptr &T)
{
    btptr temp = new btnode;
    cin>>temp->data;

    if(temp->data != '.')
    {
        insertChilds(temp);
        T->lchild = temp;
    }

    btptr temp2 = new btnode;
    cin>>temp2->data;

    if(temp2->data != '.')
    {
        insertChilds(temp2);
        T->rchild = temp2;
    }
    return;
}

void takeInput(btptr &T)
{
    btptr temp = new btnode;
    cin>>temp->data;
    T = temp;
    insertChilds(T);
    return;
}

void printInorder(btptr T)
{
    if(T == NULL)
        return;
    printInorder(T->lchild);
    cout<<T->data<<" ";
    printInorder(T->rchild);
    return;
}

void printPreorder(btptr T)
{
    if(T==NULL)
        return;
    cout<<T->data<<" ";
    printPreorder(T->lchild);
    printPreorder(T->rchild);
    return;
}

void printPostorder(btptr T)
{
    if(T==NULL)
        return;
    printPostorder(T->lchild);
    printPostorder(T->rchild);
    cout<<T->data<<" ";
    return;
}

int getTotalNodes(btptr T)
{
    if(T==NULL)
        return 0;
    return (getTotalNodes(T->lchild) + 1 + getTotalNodes(T->rchild));
}

int getLeafNodes(btptr T)
{
    if(T==NULL)
        return 0;
    if(T->lchild ==NULL && T->rchild==NULL)
        return 1;
    return (getLeafNodes(T->lchild) + getLeafNodes(T->rchild));
}

int getNonLeafNodes(btptr T)
{
    return getTotalNodes(T)-getLeafNodes(T);
}

void iterativeInorder(btptr T)
{
    stack<btptr> s;
    btptr temp = T;
    while(!s.empty() || temp!=NULL)
    {
        while(temp)
        {
            s.push(temp);
            temp = temp->lchild;
        }
        temp = s.top(); s.pop();
        cout<<temp->data<<" ";
        temp = temp->rchild;
    }
    return;
}

void iterativePreorder(btptr T)
{
    stack<btptr> s;
    s.push(T);
    btptr temp;
    while(!s.empty())
    {
        temp = s.top(); s.pop();
        cout<<temp->data<<" ";
        if(temp->rchild)
            s.push(temp->rchild);
        if(temp->lchild)
            s.push(temp->lchild);
    }
    return;
}

void iterativePostorder(btptr T)
{
    stack<btptr> s;
    btptr temp = T;
    btptr prev = NULL;
    s.push(T);
    temp = T->lchild;
    while(!s.empty())
    {
        if(temp!=prev)
        while(temp)
        {
            s.push(temp);
            temp = temp->lchild;
        }

        btptr temp2 = s.top();

        if( (prev!=temp2->rchild) && (temp2->rchild != NULL) )
        {
            temp = temp2->rchild;
            continue;
        }

        temp  = s.top(); s.pop();
        prev = temp;
        cout<<temp->data<<" ";
    }
}

void printLevelOrder(btptr T)
{
    queue<btptr> q;
    q.push(T);
    btptr temp = new btnode;
    temp->data = -1;
    q.push(temp);
    while(!q.empty())
    {
        temp = q.front(); q.pop();
        cout<<temp->data<<" ";
        if(temp->lchild)
            q.push(temp->lchild);
        if(temp->rchild)
            q.push(temp->rchild);
        if( q.front()->data==-1)
        {
            btptr temp2 = q.front(); q.pop();
            if(!q.empty())
            {
                cout<<endl;
                q.push(temp2);
            }
        }
    }
}

int find(string s, char c, int low, int high)
{
    for(int i=low;i<=high;i++)
    {
        if(s[i]==c)
            return i;
    }
    return -1;
}

btptr buildTreeInPos(string inorder, string postorder, int low, int high, int &pos)
{
    if(low>high)
        return NULL;
    btptr T = new btnode(postorder[pos--]);
    if(low==high)
        return T;
    int i = find(inorder, T->data, low, high);
    T->rchild = buildTreeInPos(inorder, postorder, i+1, high, pos);
    T->lchild = buildTreeInPos(inorder, postorder, low, i-1, pos);
    return T;

}
btptr buildTreeInPos(string inorder, string postorder)
{
    int pos = inorder.size()-1, low = 0, high = inorder.size()-1;
    return buildTreeInPos(inorder, postorder, low, high, pos);
}
btptr buildTreeInPre(string inorder, string preorder, int low, int high, int &pos)
{
    if(low>high)
        return NULL;
    btptr T = new btnode(preorder[pos++]);
    if(low==high)
        return T;
    int i = find(inorder, T->data, low, high);
    T->lchild = buildTreeInPre(inorder, preorder, low, i-1, pos);
    T->rchild = buildTreeInPre(inorder, preorder, i+1, high, pos);
    return T;
}
btptr buildTreeInPre(string inorder, string preorder)
{
    int pos = 0, low = 0, high = inorder.size()-1;

    return buildTreeInPre(inorder, preorder, low, high, pos);
}

string serialize(btptr T)
{
    string s = "";
    if(T==NULL)
    {
        s += '.';
        return s;
    }

    s += T->data;
    s += serialize(T->lchild);
    s += serialize(T->rchild);
    return s;
}
int main()
{
    string inorder = "123456789";
    string preorder = "531248679";
    string postorder = "214376985";
    btptr T = NULL;
    takeInput(T);
    cout<<"Inorder :"<<endl;
    printInorder(T); cout<<endl;
    iterativeInorder(T); cout<<endl;
    cout<<"Preorder :"<<endl;
    printPreorder(T); cout<<endl;
    iterativePreorder(T); cout<<endl;
    cout<<"Postorder :"<<endl;
    printPostorder(T); cout<<endl;
    iterativePostorder(T);  cout<<endl;
    cout<<"Level Order"<<endl;
    printLevelOrder(T); cout<<endl;
    cout<<"total nodes = "<<getTotalNodes(T)<<endl;
    cout<<"total leafs = "<<getLeafNodes(T)<<endl;
    cout<<"Serialized tree"<<endl;
    cout<<serialize(T)<<endl;

cout<<"-----------------------------------------------------------------------"<<endl;

    btptr T1 = buildTreeInPre(inorder, preorder);

    cout<<"Inorder :"<<endl;
    printInorder(T1); cout<<endl;
    iterativeInorder(T1); cout<<endl;
    cout<<"Preorder :"<<endl;
    printPreorder(T1); cout<<endl;
    iterativePreorder(T1); cout<<endl;
    cout<<"Postorder :"<<endl;
    printPostorder(T1); cout<<endl;
    iterativePostorder(T1);  cout<<endl;
    cout<<"Level Order"<<endl;
    printLevelOrder(T1); cout<<endl;
    cout<<"total nodes = "<<getTotalNodes(T1)<<endl;
    cout<<"total leafs = "<<getLeafNodes(T1)<<endl;
    cout<<"Serialized tree"<<endl;
    cout<<serialize(T1)<<endl;

cout<<"-----------------------------------------------------------------------"<<endl;

    btptr T2 = buildTreeInPos(inorder, postorder);

    cout<<"Inorder :"<<endl;
    printInorder(T2); cout<<endl;
    iterativeInorder(T2); cout<<endl;
    cout<<"Preorder :"<<endl;
    printPreorder(T2); cout<<endl;
    iterativePreorder(T2); cout<<endl;
    cout<<"Postorder :"<<endl;
    printPostorder(T2); cout<<endl;
    iterativePostorder(T2);  cout<<endl;
    cout<<"Level Order"<<endl;
    printLevelOrder(T2); cout<<endl;
    cout<<"total nodes = "<<getTotalNodes(T2)<<endl;
    cout<<"total leafs = "<<getLeafNodes(T2)<<endl;
    cout<<"Serialized tree"<<endl;
    cout<<serialize(T2)<<endl;
    return 0;
}

/// 531.2..4..86.7..9..

/// Inorder 123456789
/// Preorder 531248679
/// Postorder 214376985
