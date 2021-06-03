#include <bits/stdc++.h>
using namespace std;

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

int minVertex(int dist[], bool visited[])
{
    int mini = INT_MAX, index = 0;

    for(int i=1;i<N;i++)
        if( (!visited[i]) && (dist[i]<mini))
    {
        mini = dist[i];
        index = i;
    }
    return index;
}

void primsPath()
{
    int dist[N];
    int parent[N];
    bool visited[N];
    for(int i=0;i<N;i++)
        dist[i] = INT_MAX, visited[i] = false;

    dist[1] = 0;
    parent[1] = -1;


    for(int i=1;i<N-1;i++)
    {

        int node = minVertex(dist, visited);
        visited[node] = true;

        for(int dest=1;dest<N;dest++)
        {
            /// no edge
            if( (G[node][dest]==INT_MAX) || visited[dest] )
                continue;

            if( G[node][dest] < dist[dest])
            {
                dist[dest] = G[node][dest];
                parent[dest] = node;
            }
        }
    }

    printPath(dist, parent);
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
