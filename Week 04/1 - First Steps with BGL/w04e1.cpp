#include <iostream>
#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/prim_minimum_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS, no_property, property<edge_weight_t, int>> G;
typedef property_map<G, edge_weight_t>::type WM;

int main()
{
    int t;
    cin >> t;
    
    while (t--)
    {
        int n, m;
        cin >> n >> m;
        
        // Read graph.
        G g(n);
        WM wm = get(edge_weight, g);
        for (int i = 0; i < m; ++i)
        {
            int u, v;
            cin >> u >> v;
            cin >> wm[add_edge(u, v, g).first];
        }
        
        // Compute weight of minimum spanning tree.
        int w = 0;
        vector<int> pred(n);
        prim_minimum_spanning_tree(g, &pred[0]);
        for (int v = 0; v < n; ++v)
        {
            auto e = edge(v, pred[v], g);
            if (e.second)
                w += wm[e.first];
        }
        
        // Compute distance from 0 to furthest vertex.
        int d = 0;
        vector<int> dist(n);
        dijkstra_shortest_paths(g, 0, distance_map(&dist[0]));
        for (int v = 0; v < n; ++v)
            d = max(d, dist[v]);
        
        cout << w << " " << d << endl;
    }
    
    return 0;
}
