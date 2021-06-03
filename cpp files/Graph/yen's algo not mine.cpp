#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> iPair;
typedef pair<int, vector<int>> vPair;

int inf = 1000000;

class Graph
{
public:
    int V;
    list< pair<int, int> > *adj;
    vector<int> dist;

    Graph(int V) {
        this->V = V;
        adj = new list<iPair> [V];
    }
    Graph(const Graph &rhs) {
        V = rhs.V;
        adj = rhs.adj;
        dist = rhs.dist;
    }

    void addEdge(int u, int v, int w) {
        adj[u].push_back(make_pair(v, w));
        adj[v].push_back(make_pair(u, w));
    }

    void delEdge(int u, int v){

        for ( auto it = adj[u].begin(); it != adj[u].end(); it++) {
            if (it->first == v) {
                it = adj[u].erase(it);
                break;
            }
        }

        for ( auto it = adj[v].begin(); it != adj[v].end(); it++) {
            if (it->first == u) {
                it = adj[v].erase(it);
                break;
            }
        }
    }

    vector<int> findPath(int parent[], int s, int d){
        vector<int> path;
        path.push_back(d);
        int u = parent[d];
        path.insert(path.begin(), u);
        while (u != s){
            int temp = parent[u];
            u = temp;
            path.insert(path.begin(), temp);
        }
        return path;
    }

    vector<int> dijkstra(int src, int des){

        priority_queue< iPair, vector <iPair> , greater<iPair> > pq;

        dist.reserve(V);
        for (int i=0; i<V; i++){
            dist[i] = inf;
        }

        pq.push(make_pair(0, src));
        dist[src] = 0;

        int parent[V];
        parent[0] = -1;


        while (!pq.empty())
        {
            int u = pq.top().second;
            pq.pop();

            list< pair<int, int> >::iterator i;
            for (i = adj[u].begin(); i != adj[u].end(); ++i)
            {
                int v = (*i).first;
                int weight = (*i).second;

                if (dist[v] > dist[u] + weight)
                {
                    parent[v] = u;
                    dist[v] = dist[u] + weight;
                    pq.push(make_pair(dist[v], v));
                }
            }
        }
        vector<int> path = findPath(parent, src, des);
        return path;
    }
};

void showlist(vector<int> g) {
    for(auto it = g.begin(); it != g.end(); ++it)
        cout << *it << ' ';
}

vector<int> slicing(vector<int>& arr, int X, int Y) {

    auto start = arr.begin() + X;
    auto end = arr.begin() + Y + 1;
    vector<int> result(Y - X + 1);
    copy(start, end, result.begin());
    return result;
}

vector<vector<int>> yen(Graph g, int s, int d, int K) {
    vector<vector<int> > A;
    vector<int> path = g.dijkstra(s, d);

    A.push_back(path);
    priority_queue<vPair, vector<vPair>, greater<vPair> > B;

    for (int k=1; k<K; k++){
        for (int i=0; i<=A[k-1].size()-2; i++){
            Graph g_copy = g;
            int spurNode = A[k-1][i];
            int root_dis = g.dist[spurNode];
            vector<int> rootPath = slicing(A[k-1], 0, i);
            for (int j = 0; j < A.size(); j++) {
                vector<int> p = A[j];
                if (rootPath == slicing(p, 0, i)) {
                    g_copy.delEdge(p[i], p[i+1]);
                }
            }

            vector<int> spurPath = g_copy.dijkstra(spurNode, d);
            int spur_dis = g_copy.dist[d];

            vector<int> totalPath = rootPath;
            totalPath.insert(totalPath.end(), spurPath.begin()+1, spurPath.end());

            int total_dis = root_dis + spur_dis;
            if (B.empty() && total_dis<inf)
                B.push(make_pair(total_dis, totalPath));

            priority_queue<vPair, vector<vPair>, greater<vPair> > temp;
            bool found = false;
            while (!B.empty()) {
                vPair dis_path = B.top();
                temp.push(dis_path);
                B.pop();
                if (dis_path.second == totalPath & !found)
                    found = true;

            }
            if (!found && total_dis<inf)
                temp.push(make_pair(total_dis, totalPath));

            B = temp;
        }
        if (B.empty())
            break;


        A.push_back(B.top().second);

        B.pop();
    }
    cout << "The size of shortest path list: " << A.size() << endl;
    return A;
}

int main()
{
    // create the graph
    int V = 9;
    Graph g(V);

    g.addEdge(0, 1, 4);
    g.addEdge(0, 7, 8);
    g.addEdge(1, 2, 8);
    g.addEdge(1, 7, 11);
    g.addEdge(2, 3, 7);
    g.addEdge(2, 8, 2);
    g.addEdge(2, 5, 4);
    g.addEdge(3, 4, 9);
    g.addEdge(3, 5, 14);
    g.addEdge(4, 5, 10);
    g.addEdge(5, 6, 2);
    g.addEdge(6, 7, 1);
    g.addEdge(6, 8, 6);
    g.addEdge(7, 8, 7);

    vector<vector<int> > A;
    // shortest path from node 0 to 4, K = 8
    A = yen(g, 0, 4, 10);
    for(auto it = A.begin(); it != A.end(); ++it) {
        showlist(*it);
        cout << "\n";
    }
    return 0;
}
