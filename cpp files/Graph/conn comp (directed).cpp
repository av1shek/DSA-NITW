/// AT DT

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
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            G[i][j] = 0;
}


void postOrder(int currVertex , bool visited[], int &counter, stack<int> &s)
{
    if(visited[currVertex])
        return;
    visited[currVertex] = true;

    for(int i=1;i<N;i++)
    {
        if( (G[currVertex][i]==0) || visited[i] )
            continue;
        postOrder(i, visited, counter, s);
    }
    s.push(currVertex);
}

void reverseGraph()
{
    for(int i=1;i<N;i++)
        for(int j=i+1;j<N;j++)
            if(G[i][j]==1)
            {
                G[i][j] = G[j][i];
                G[j][i] = 1;
            }
            else if(G[j][i]==1)
            {
                G[j][i] = G[i][j];
                G[i][j] = 1;
            }

}

void dfs(int currVertex, bool visited[])
{
    if(visited[currVertex])
        return;

    visited[currVertex] = true;
    cout<<currVertex<<" ";
    for(int i=0;i<N;i++)
        if( (G[currVertex][i]==1) && (visited[i]==false) )
            dfs(i, visited);

    return;
}
void connectedComp()
{
    bool visited[N];
    stack<int> s;
    int counter=1;
    memset(visited, false, sizeof(visited));
    postOrder(2, visited, counter, s);
    postOrder(8, visited, counter, s);
    postOrder(7, visited, counter, s);
    memset(visited, false, sizeof(visited));

    reverseGraph();

    while(!s.empty())
    {
        int curr = s.top(); s.pop();
        if(!visited[curr])
        {
            dfs(curr, visited);
            cout<<endl;
        }
    }

}


int main()
{
    N = 11;
    initialize();

    addEdge(2,3);
    addEdge(2,6);

    addEdge(3,4);
    addEdge(3,5);
    addEdge(3,1);

    addEdge(1,2);
    addEdge(1,4);

    addEdge(4,5);
    addEdge(6,3);

    addEdge(7,6);
    addEdge(7,8);

    addEdge(8,6);
    addEdge(8,10);

    addEdge(9,8);
    addEdge(10,9);

    connectedComp();
    return 0;
}


