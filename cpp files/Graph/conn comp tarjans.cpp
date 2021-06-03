#include <bits/stdc++.h>
using namespace std;

int G[100][100];
int N = 100;    /// No of vertices

void addEdge(int u, int v)
{
    G[u][v] = 1;
    //G[v][u] = 1;
}

void initialize()
{
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            G[i][j] = 0;
}

void dfsUtils(int v, bool visited[], int low[], int num[],  stack<int> &s, int &time)
{
    if(num[v]!=-1)
        return;

    visited[v] = true;
    low[v] = num[v] = (time++);

    s.push(v);
    for(int w=1;w<N;w++)
        if( G[v][w]==1 )
        {
            if(num[w]==-1)
            {
                dfsUtils(w, visited, low, num, s, time);
                low[v] = min(low[v], low[w]);
            }
            else if(visited[w]==true)
                low[v] = min(low[v], num[w]);

        }

    if(low[v]==num[v])
    {
        while(true)
        {
            visited[s.top()] = false;
            cout<<s.top()<<" ";
            if(s.top()==v)
            {
                s.pop();
                cout<<endl;
                break;
            }
            s.pop();
        }
    }

    return;
}

void dfs(int s)
{
    bool visited[N];
    int low[N], num[N];
    stack<int> stk;
    int time = 0;
    memset(num, -1, sizeof(num));
    memset(visited, false, sizeof(visited));
    for(int i=1;i<N;i++)
        if(num[i]==-1)
            dfsUtils(i, visited, low, num, stk, time);
}



int main()
{
    int v,e;
    v = 10;
    e = 15;
    N = v+1;
    initialize();

    int src[] = {1, 1, 2, 2, 3, 3, 3, 4, 6, 7, 7, 8, 8, 9, 10};
    int dest[] = {2, 4, 3, 6, 1, 4, 5, 5, 3, 6, 8, 6, 10, 8, 9};
    for(int i=0;i<e;i++)
        addEdge(src[i], dest[i]);

    dfs(1);
    return 0;
}
