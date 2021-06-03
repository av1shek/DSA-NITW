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
    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++)
            G[i][j] = 0;
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
bool detectCycle()
{
    vector<pair<int, int> > edges;
    for(int i=1;i<N;i++)
        for(int j=i+1;j<N;j++)
            if(G[i][j])
                edges.push_back({i, j});

    int s[N];
    memset(s, -1, sizeof(s));

    for(int i=0;i<edges.size();i++)
    {
        int x = find(s, edges[i].first);
        int y = find(s, edges[i].second);
        cout<<edges[i].first<<"-> "<<x<<endl;
        cout<<edges[i].second<<"-> "<<y<<endl<<endl;
        if(x == y)
            return true;
        else
            Union(edges[i].first, edges[i].second, s);
    }
    return false;
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
    cout<<detectCycle();
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
