#include <bits/stdc++.h>
using namespace std;
typedef pair<int, pair<int, int> > pii;
int G[100][100];
int N = 100;    /// No of vertices

void addEdge(int u, int v, int w)
{
    G[u][v] = w;
    G[v][u] = w;
}

void initialize()
{
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            G[i][j] = INT_MAX;
}

void printPath(int dist[], int parent[])
{
    int child[N];
    for(int i=2;i<N;i++)
        cout<<parent[i]<<" -> "<<i<<" => "<<dist[i]<<endl;
}



void primsPath()
{
    int dist[N];
    int parent[N];
    bool visited[N];
    int sum = 0;
    for(int i=0;i<N;i++)
        dist[i] = INT_MAX, visited[i] = false;

    dist[1] = 0;
    parent[1] = -1;

    priority_queue<pii, vector<pii>, greater<pii> > pq;

    for(int i=1;i<N;i++)
        if(G[1][i]!=INT_MAX)
            pq.push(make_pair(G[1][i], make_pair(i, 1)));

    visited[1] = true;
    while(!pq.empty())
    {
        pii curr = pq.top();
        pq.pop();

        int currVertex = curr.second.first;
        if(dist[currVertex] > curr.first)
        {
            dist[currVertex] = curr.first;
            parent[curr.second.first] = curr.second.second;
            cout<<curr.second.second<<" "<<curr.second.first<<endl;
            sum += curr.first;
        }

        visited[currVertex] = true;
        for(int i=1;i<N;i++)
        {
            if( (G[currVertex][i]!=INT_MAX) && (visited[i]==false))
                pq.push(make_pair(G[currVertex][i], make_pair(i, currVertex)));

        }
    }
    cout<<sum<<endl;
    // printPath();
    return;
}
int main()
{
    N=8;
    initialize();

    addEdge(1,2,2);
    addEdge(1,4,1);
    addEdge(1,3,4);

    addEdge(2,4,3);
    addEdge(2,5,10);

    addEdge(6,4,8);
    addEdge(6,3,5);
    addEdge(6,7,1);

    addEdge(7,4,4);
    addEdge(7,5,6);

    addEdge(3,4,2);
    addEdge(4,5,7);

    primsPath();
    return 0;
}
