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

void bfsTraversal(int s)
{
    bool visited[N];
    memset(visited, false, sizeof(visited));

    queue<int> q;
    q.push(s);
    visited[s] = true;
    while(!q.empty())
    {
        int currVer = q.front(); q.pop();

        cout<<currVer<<" ";
        for(int i=0;i<N;i++)
        {
            if( (G[currVer][i]==0) || visited[i])
                continue;
            q.push(i);
            visited[i] = true;
        }
    }
    return;
}

void dfsUtils(int currVertex, bool visited[])
{
    if(visited[currVertex])
        return;

    visited[currVertex] = true;
    cout<<currVertex<<" ";
    for(int i=0;i<N;i++)
        if( (G[currVertex][i]==1) && (visited[i]==false) )
            dfsUtils(i, visited);
    return;
}

void dfsTraversal(int s)
{
    bool visited[N];
    memset(visited, false, sizeof(visited));
    dfsUtils(s, visited);
}

void topologicalSort()
{
    int *inD = inDegree();
    bool visited[N];
    memset(visited, false, sizeof(visited));

    queue<int> q;
    for(int i=0;i<N;i++)
        if(inD[i]==0)
            q.push(i);

    while(!q.empty())
    {
        int currVertex = q.front(); q.pop();
        visited[currVertex] = true;
        cout<<currVertex<<" ";
        for(int i=0;i<N;i++)
        {
            if( (G[currVertex][i]==0) || (visited[currVertex]) )
                continue;
            inD[i]--;
            if(inD[i]==0)
                q.push(i);
        }
    }
}

bool cycleUtilsDirected(int v, bool visited[], bool tempVisited[])
{
    if(visited[v] == false)
    {
        visited[v] = true;
        tempVisited[v] = true;

        for(int i =1; i<N;i++)
        {
            if(G[i][v]==0)
                continue;

            if ( (!visited[i]) && tempVisited[i])
                return true;

            if (cycleUtilsDirected(i, visited, tempVisited) )
                return true;
        }

    }
    tempVisited[v] = false;
    return false;
}

bool isCyclicDirected()
{
    bool visited[N], tempVisited[N];

    memset(visited, false, sizeof(visited));
    memset(tempVisited, false, sizeof(tempVisited));

    for(int i = 1; i < N; i++)
        if (cycleUtilsDirected(i, visited, tempVisited))
            return true;
    return false;
}

int main()
{
    initialize();
    addEdge(1,2);
    addEdge(1,3);
    addEdge(2,3);
    addEdge(3,4);
    addEdge(1,4);
    dfsTraversal(1); cout<<endl;
    bfsTraversal(1); cout<<endl;
    return 0;
}
