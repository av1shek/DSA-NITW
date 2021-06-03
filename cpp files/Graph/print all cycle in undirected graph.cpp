#include <bits/stdc++.h>
using namespace std;

int G[100][100];
int N = 100;    /// No of vertices

void addEdge(int u, int v)
{
    G[u][v] = 1;

}

void initialize()
{
    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++)
            G[i][j] = 0;
}

void printCycle(int start, int node, bool visited[],  vector<int>& path, int &count)
{
    if(visited[node])
    {
        if(start != node)
            return;

        for(int i=0;i<path.size();i++)
            cout<<path[i]<<" ";
        cout <<path[0]<< endl;
        count++;
        return;
    }

    visited[node] = true;
    path.push_back(node);
    for(int i=1;i<N;i++)
        if(G[node][i] &&(i!=node))
            printCycle(start, i, visited, path, count);
    visited[node] = false;
    path.pop_back();
}

int printCycle()
{
    bool visited[N];
    int count=0;
    vector<int> temp;

    memset(visited, false, sizeof(visited));

    for(int i = 1; i < N; i++)
    {
        printCycle(i,i, visited, temp, count);
        visited[i] = true;
    }
    return count;
}

int main()
{
    int V, e;
    cin>>V>>e;
    N = V+1;
    initialize();

    int u, v;
    for(int i=0; i<e; i++)
    {
        cin>>u>>v;
        addEdge(u, v);
    }
    cout<<printCycle();
    return 0;
}

/*
5
8
1 2
2 5
5 4
1 4
2 3
4 3
3 1
3 5
*/

/*
7
9
1 2
2 3
3 4
4 1
5 6
6 7
7 5
1 3
3 1
*/
