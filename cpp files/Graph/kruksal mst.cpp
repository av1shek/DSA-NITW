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
    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++)
            G[i][j] = INT_MAX;
}

/// -----------------------------------------------------------------------
int find(int sets[], int i)
{
    if (sets[i] == -1)
        return i;
    return find(sets, sets[i]);
}

void Union(int x, int y, int s[])
{
    if(s[x]==-1)
        s[x] = y;
    else if(s[y]==-1)
        s[y] = x;
}
/// -----------------------------------------------------------------------

/// for undirected only
void kruskal()
{
    vector<pii> edges;
    for(int i=1;i<N;i++)
        for(int j=i+1;j<N;j++)
            if(G[i][j]!=INT_MAX)
                edges.push_back({ G[i][j], {i, j}});

    sort(edges.begin(), edges.end());
    int s[N];
    memset(s, -1, sizeof(s));

    int sum=0;
    for(int i=0;i<edges.size();i++)
    {
        int u = find(s, edges[i].second.first);
        int v = find(s, edges[i].second.second);

        if(u != v)
        {
            sum += edges[i].first;
            cout<<edges[i].second.first<<" "<<edges[i].second.second<<endl;
            Union(edges[i].second.first, edges[i].second.second, s);
        }

    }
    cout<<sum<<endl;
    return;
}

int main()
{
    int V, e;
    cin>>V>>e;
    N = V+1;
    initialize();

    int u, v, w;
    for(int i=0; i<e; i++)
    {
        cin>>u>>v>>w;
        addEdge(u, v, w);
    }
    kruskal();
    return 0;
}

/*
7 12
1 2 2
1 3 4
1 4 1
2 4 3
2 5 10
3 4 2
4 5 7
3 6 5
4 6 8
4 7 4
5 7 6
6 7 1
*/

