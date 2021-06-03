#include <bits/stdc++.h>
using namespace std;

int G[100][100];
int N = 100;    /// No of vertices

void addEdge(int u, int v)
{
    G[u][v] = 1;
    G[v][u] = 1;
}

void initialize()
{
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            G[i][j] = 0;
}

void dfsUtils(int v, bool visited[], int low[], int num[], int parent[], int &time)
{
    if(visited[v])
        return;

    visited[v] = true;
    low[v] = num[v] = (time++);

    int child=0;
    for(int w=0;w<N;w++)
        if( G[v][w]==1 )
        {
            if(visited[w]==false)
            {
                child++;
                parent[w] = v;
                dfsUtils(w, visited, low, num, parent, time);
                low[v] = min(low[v], low[w]);

                if(parent[v]==-1 && child>1)
                    cout<<"cut vertex = "<<v<<endl;
                if(parent[v]!=-1 && low[w]>=num[v])
                    cout<<"cut vertex = "<<v<<endl;
            }
            else
                low[v] = min(low[v], num[w]);

        }

    return;
}

void dfs(int s)
{
    bool visited[N];
    int low[N], num[N], parent[N];
    int time = 0;
    parent[s]= -1;
    memset(visited, false, sizeof(visited));
    dfsUtils(s, visited, low, num, parent, time);
}



int main()
{

    int e, v;
    v = 5, e = 7;
    N = v+1;

    initialize();
    addEdge(1,0);
    addEdge(1,2);
    addEdge(1,3);
    addEdge(0,5);
    addEdge(2,4);
    addEdge(3,4);
    addEdge(2,3);

    dfs(0);
    return 0;
}
