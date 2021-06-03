#include<bits/stdc++.h>
using namespace std;
typedef struct bknode *bkptr;

struct bknode{
    string word;
    bkptr ptr[15];

    bknode()
    {
        word = "";
        for(int i=0;i<15;i++)
            ptr[i]=NULL;
    }
    bknode(string s)
    {
        word = s;
        for(int i=0;i<15;i++)
            ptr[i]=NULL;
    }
};

int editDist(string s1, string s2)
{
     int m = s1.size();
        int n = s2.size();

        int dp[m+1][n+1];

        for(int i=0;i<=m;i++)
            dp[i][0] = i;
        for(int i=0;i<=n;i++)
            dp[0][i] = i;

        for(int i=1;i<=m;i++)
            for(int j=1;j<=n;j++)
                if( s1[i-1]==s2[j-1] )
                    dp[i][j] = dp[i-1][j-1];
                else
                    dp[i][j] = min( min(dp[i-1][j], dp[i][j-1]), dp[i-1][j-1] ) + (s1[i-1]!=s2[j-1]);

        return dp[m][n];
}

void insert(bkptr &T, string s)
{
    if(T==NULL)
    {
        T = new bknode(s);
        return;
    }
    int dist = editDist(T->word, s);
    insert(T->ptr[dist], s);
}

void findSuggestions(bkptr &T, string s, int n)
{
    if(T==NULL)
        return;
    int dist = editDist(s, T->word);
    if(dist <= n)
        cout<<dist<<" "<<T->word<<" ";
    int low = max (dist - n, 0);
    int high = min(dist + n, 14);

    for(int i=low;i<=high;i++)
        findSuggestions(T->ptr[i], s, n);
    return;
}

void takeInput(bkptr &T)
{
    while(true)
    {
        string s;   cin>>s;
        if(s== "#")
            break;
        insert(T, s);
    }
}

int main()
{
    bkptr T = NULL;
    takeInput(T);
    int n;
    string s;
    cin>>s>>n;

    findSuggestions(T, s, n);
    return 0;
}
