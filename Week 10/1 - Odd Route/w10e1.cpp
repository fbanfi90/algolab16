#include <iostream>
#include <vector>
#include <limits>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, directedS, no_property, property<edge_weight_t, int>> G;
typedef property_map<G, edge_weight_t>::type WM;

int main()
{
    int T;
    cin >> T;
    
    while (T--)
    {
        int n, m, s, t;
        cin >> n >> m >> s >> t;
        
        // Create graph.
        G g(4 * n);
        WM wm = get(edge_weight, g);
        for (int i = 0; i < m; ++i)
        {
            int u, v, w;
            cin >> u >> v >> w;
            wm[add_edge(u, (2 + (w % 2)) * n + v, g).first] = w;
            wm[add_edge(n + u, (2 + !(w % 2)) * n + v, g).first] = w;
            wm[add_edge(2 * n + u, (w % 2) * n + v, g).first] = w;
            wm[add_edge(3 * n + u, !(w % 2) * n + v, g).first] = w;
        }
        
        // Compute shortest s'-t'-path.
        vector<int> dist(4 * n);
        dijkstra_shortest_paths(g, s, distance_map(&dist[0]));
        cout << (dist[3 * n + t] != numeric_limits<int>::max() ?
                to_string(dist[3 * n + t]) : "no") << endl;
    }
}
