#include <bits/stdc++.h>
using namespace std;

int G[100][100];
int N = 100;    /// No of vertices

void addEdge(int u, int v, int w)
{
    G[u][v] = w;

}

void initialize()
{
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            G[i][j] = INT_MAX;
}

void printPath(int node, int parent[])
{
    if(parent[node] == -1)
    {
        cout<<node;
        return;
    }

    printPath(parent[node], parent);
    cout<<"->"<<node;
}


void shortestPath(int src)
{
    int dist[N];
    for(int i=0;i<N;i++)
        dist[i] = INT_MAX;

    dist[src] = 0;
    set<pair<int, int> > s;

    s.insert(make_pair(0,src));
    while(!s.empty())
    {
        auto p =   *(s.begin());
        int node = p.second;

        int nodeDist = p.first;
        s.erase(s.begin());

        for(int i=0;i<N;i++)
        {
            /// no edge
            if( (i==node) || (G[node][i]==INT_MAX) )
                continue;

            if(nodeDist + G[node][i] < dist[i]){
                int dest = i;
                auto f = s.find( make_pair(dist[dest],dest));
                if(f!=s.end())
                    s.erase(f);

                dist[dest] = nodeDist + G[node][i];
                s.insert(make_pair(dist[dest],dest));
            }
        }
    }

    for(int i=1;i<N;i++)
        cout<<i<<" is located at distance of  "<<dist[i]<<endl;
    return;
}

void shortestPath(int src, int end)
{
    int dist[N];
    int parent[N];
    for(int i=0;i<N;i++)
        dist[i] = INT_MAX;

    dist[src] = 0;
    parent[src] = -1;
    set<pair<int, int> > s;

    s.insert(make_pair(0,src));
    while(!s.empty())
    {
        auto p =   *(s.begin());
        int node = p.second;
        if(node == end)
            break;
        int nodeDist = p.first;
        s.erase(s.begin());

        for(int i=0;i<N;i++)
        {
            /// no edge
            if( (i==node) || (G[node][i]==INT_MAX) )
                continue;

            if(nodeDist + G[node][i] < dist[i])
            {
                int dest = i;
                auto f = s.find( make_pair(dist[dest],dest));
                if(f!=s.end())
                    s.erase(f);

                dist[dest] = nodeDist + G[node][i];
                parent[i] = node;
                s.insert(make_pair(dist[dest],dest));
            }
        }
    }

    cout<<"Shortest distance between "<<src<<" and "<<end<<" is "<<dist[end]<<endl;
    printPath(end, parent);
    return;
}


int main(){
    initialize();
    N = 5;
    addEdge(1,2,1);
    addEdge(1,3,4);
    addEdge(2,3,1);
    addEdge(3,4,2);
    addEdge(1,4,7);

    shortestPath(1, 3);
 return 0;
}
