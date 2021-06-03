#include<iostream>
using namespace std;
typedef struct hctnode *hctptr;
typedef struct lnode  *lptr;

void takeInput(hctptr &);           /// takes input till -1
void insert(hctptr &, int);         /// insert a integer value

string codeword[26];
struct lnode
{
    hctptr data;
    struct lnode *next;
    lnode()
    {
        next=NULL;
    }
};

struct hctnode
{
    struct hctnode *lchild;
    char data;
    int freq;
    struct hctnode *rchild;
    hctnode()
    {
        lchild = NULL;
        rchild = NULL;
    }
    hctnode(char data, int freq)
    {
        lchild = NULL;
        this->data = data;
        this->freq = freq;
        rchild = NULL;
    }
};


void insertList(lptr &P, hctptr x)
{
    lptr temp = new lnode;
    temp->data = x;

    if(P==NULL)
        P = temp;
    else
    {
        lptr T = P;
        while(T->next != NULL)
            T = T->next;
        T->next = temp;
    }

    return;
}


int getSize(lptr L)
{
    int count=0;
    while(L!=NULL)
    {
        count++;
        L = L->next;
    }
    return count;
}


hctptr getMin(lptr L)
{
    if(L==NULL)
    {
        cout<<"List is empty"<<endl;
        return NULL;
    }
    int mini = L->data->freq;
    lptr miniNode = L;
    while(L!=NULL)
    {
        if(mini > L->data->freq)
        {
            mini = L->data->freq;
            miniNode = L;
        }
        L = L->next;
    }
    return miniNode->data;
}


hctptr getMax(lptr L)
{
    if(L==NULL)
    {
        cout<<"List is empty"<<endl;
        return NULL;
    }
    int maxx = L->data->freq;
    hctptr maxxNode = L->data;
    while(L!=NULL)
    {
        if( maxx < L->data->freq)
        {
            maxx = L->data->freq;
            maxxNode = L->data;
        }
        L = L->next;
    }
    return maxxNode;
}

void Delete(lptr &L, hctptr k)
{
    lptr temp = L;
    if(L->data == k)
    {
        L = L->next;
        delete(temp);
    }
    else
    {
        while( (temp->next!=NULL) && (temp->next->data!=k) )
            temp = temp->next;
        if(temp->next!=NULL)
        {
            lptr T = temp->next;
            temp->next = temp->next->next;
            delete(T);
        }
    }
    return;
}

void deleteMin(lptr &L)
{
    hctptr mini = getMin(L);
    Delete(L, mini);
    return;
}

void deleteMax(lptr &L)
{
    hctptr maxx = getMax(L);
    Delete(L, maxx);
    return;
}




void takeInput(hctptr &T)
{
    lptr allNodes = NULL;
    while(true)
    {
        hctptr temp = new hctnode;
        cin>>temp->data;
        if(temp->data == '#')
            break;
        cin>>temp->freq;
        insertList(allNodes, temp);
    }

    while(getSize(allNodes)!=1)
    {
        hctptr t1 = getMin(allNodes);   deleteMin(allNodes);
        hctptr t2 = getMin(allNodes);   deleteMin(allNodes);

        hctptr temp = new hctnode('#', t1->freq + t2->freq);
        if(t1->freq >= t2->freq)
        {
            temp->rchild = t2;
            temp->lchild = t1;
        }
        else
        {
            temp->rchild = t1;
            temp->lchild = t2;
        }
        insertList(allNodes, temp);
    }
    T = allNodes->data;
    return;
}

void printHCT(hctptr T, string s="")
{
    if(T==NULL)
        return;
    if(T->lchild==NULL && T->rchild==NULL)
        cout<<"( "<<T->data<<", "<<T->freq<<" code = "<<s<<" ) "<<endl;
    printHCT(T->lchild, s+"0");
    printHCT(T->rchild, s+"1");
}

void getCodeWords(hctptr T, string s="")
{
    if(T==NULL)
        return;
    if(T->lchild==NULL && T->rchild==NULL)
        codeword[T->data-'a'] = s;
    getCodeWords(T->lchild, s+"0");
    getCodeWords(T->rchild, s+"1");
}

hctptr encode(string s)
{
    int freq[26] = {0};
    for(int i=0;i<s.size();i++)
        freq[s[i]-'a']++;

    lptr allNodes = NULL;
    for(int i=0;i<26; i++)
    {
        if(freq[i]==0)
            continue;
        hctptr temp = new hctnode;
        temp->data = char('a'+i);
        temp->freq = freq[i];
        insertList(allNodes, temp);
    }

    while(getSize(allNodes)!=1)
    {
        hctptr t1 = getMin(allNodes);   deleteMin(allNodes);
        hctptr t2 = getMin(allNodes);   deleteMin(allNodes);

        hctptr temp = new hctnode('#', t1->freq + t2->freq);
        if(t1->freq >= t2->freq)
        {
            temp->rchild = t2;
            temp->lchild = t1;
        }
        else
        {
            temp->rchild = t1;
            temp->lchild = t2;
        }
        insertList(allNodes, temp);
    }
    hctptr T = allNodes->data;
    getCodeWords(T);
    for(int i=0;i<s.size();i++)
        cout<<codeword[s[i]-'a'];
    cout<<endl;
    return T;
}

void decode(string s, hctptr T)
{
    for(int i=0;i<s.size();)
    {
        hctptr temp = T;
        while(temp->lchild != NULL && temp->rchild!=NULL)
        {
            if(s[i]=='0')
                temp = temp->lchild;
            else
                temp = temp->rchild;
            i++;
        }
        cout<<temp->data;
    }
}
int main()
{
    string s;
    cout<<"Enter string to encode"<<endl;
    cin>>s;
    hctptr T = encode(s);
    cout<<"Enter encoded string to decode"<<endl;
    cin>>s;
    decode(s, T);



    return 0;
}

/*

a 10
e 15
i 12
s 3
t 4
p 13
n 1
#

*/

/// eurekaihavecompletedtheassignment

/// 11001100010111011010000100110000000001111101010011111010001000111011000111010110001100011000001000100100101100101110101110110001
