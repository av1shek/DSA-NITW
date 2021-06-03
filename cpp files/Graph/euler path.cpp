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

/// in undirected graph both indegree and outdegree
int* outDegree()
{
    int *ans = new int[N]{0};
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            if(G[i][j])
                ans[i]++;
    return ans;
}

int* inDegree()
{
    int *ans = new int[N]{0};
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            if(G[i][j])
                ans[j]++;
    return ans;
}


void dfs(int src, int start, int index, vector<int> &path, int inD[], bool flag=false)
{
    if( !(src==start && flag) )
        path.insert(path.begin()+index, src);
    inD[src]--;
    for(int i=1;i<N;i++)
    {
        if(G[src][i])
        {
            G[src][i] = 0;
            G[i][src] = 0;
            inD[i]--;
            dfs(i, start,  index+1, path, inD, true);

            break;
        }
    }
}

void completeTheGraph(vector<int> path)
{
    int n = path.size();
    for(int i=0;i<n-1;i++)
    {
        G[path[i]][path[i+1]] = 1;
        G[path[i+1]][path[i]] = 1;
    }
}
int findIndex(vector<int> path, int ind[])
{
    for(int i=0;i<path.size();i++)
    {
        if(ind[path[i]]>0)
            return i;
    }
    return -1;
}

void euler()
{
    int *inD = inDegree();
    bool visited[N];
    memset(visited, false, sizeof(visited));

    vector<int> path;
    path.push_back(1);

    while(true)
    {
        int index = findIndex(path, inD);

        if(index == -1) break;
        dfs(path[index], path[index], index, path, inD);
    }

    completeTheGraph(path);
    for(auto c:path)
        cout<<c<<" ";
}

int main()
{
    initialize();
    N = 13;
    addEdge(1, 3);
    addEdge(1, 4);
    addEdge(2, 3);
    addEdge(2, 8);
    addEdge(3, 4);
    addEdge(3, 6);
    addEdge(3, 7);
    addEdge(3, 9);
    addEdge(4, 5);
    addEdge(4, 7);
    addEdge(4, 10);
    addEdge(4, 11);
    addEdge(5, 10);
    addEdge(6, 9);
    addEdge(7, 9);
    addEdge(7, 10);
    addEdge(8, 9);
    addEdge(9, 10);
    addEdge(9, 12);
    addEdge(10, 11);
    addEdge(10, 12);

    euler();
    return 0;
}
