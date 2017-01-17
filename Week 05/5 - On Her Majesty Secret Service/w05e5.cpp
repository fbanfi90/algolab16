#include <iostream>
#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, directedS, no_property, property<edge_weight_t, int>> G;
typedef property_map<G, edge_weight_t>::type WM;

int main()
{
    int t;
    cin >> t;
    
    while (t--)
    {
        int n, m, a, s, c, d;
        cin >> n >> m >> a >> s >> c >> d;
        
        // Read graph G.
        G g(n);
        WM wm = get(edge_weight, g);
        for (int i = 0; i < m; ++i)
        {
            char w;
            int x, y, z;
            cin >> w >> x >> y >> z;
            wm[add_edge(x, y, g).first] = z;
            if (w == 'L')
                wm[add_edge(y, x, g).first] = z;
        }
        
        // Read agents positions.
        vector<int> as(a);
        for (int i = 0; i < a; ++i)
            cin >> as[i];
        
        // Read shelters positions.
        vector<int> ss(s);
        for (int i = 0; i < s; ++i)
            cin >> ss[i];
        
        // Compute shortest paths to shelters from each agent.
        vector<vector<int>> dist(a, vector<int>(n));
        for (int i = 0; i < a; ++i)
            dijkstra_shortest_paths(g, as[i], distance_map(&dist[i][0]));
        
        // Perform binary search on graphs G'_t.
        int l = 0, r = INT_MAX;
        while (l != r)
        {
            // Construct bipartite graph G'_t of distances <= t - d.
            G g_(a + c * s);
            int t = (l + r) / 2;
            for (int i = 0; i < a; ++i)
                for (int j = 0; j < s; ++j)
                    if (dist[i][ss[j]] != INT_MAX)
                        for (int k = 0; k < c; ++k)
                            if (dist[i][ss[j]] <= t - (k + 1) * d)
                                add_edge(i, a + k * s + j, g_);
            
            // Compute maximum matching on G'_t.
            vector<int> mate(a + c * s);
            edmonds_maximum_cardinality_matching(g_, &mate[0]);
            
            // Update search interval.
            if (matching_size(g_, &mate[0]) != (size_t)a) l = t + 1;
            else r = t;
        }
        
        cout << l << endl;
    }
    
    return 0;
}
