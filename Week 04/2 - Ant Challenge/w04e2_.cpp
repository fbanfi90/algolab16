#include <iostream>
#include <vector>
#include <limits>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/prim_minimum_spanning_tree.hpp>

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
        int n, m, s, a, b;
        cin >> n >> m >> s >> a >> b;
        
        // Read each species graph.
        vector<G> pns(s, G(n));
        vector<WM> wm(s);
        for (int i = 0; i < s; ++i)
            wm[i] = get(edge_weight, pns[i]);
        for (int j = 0; j < m; ++j)
        {
            int t1, t2;
            cin >> t1 >> t2;
            for (int i = 0; i < s; ++i)
                cin >> wm[i][add_edge(t1, t2, pns[i]).first];
        }
        
        // Read hives (useless, MSTs unique).
        vector<int> hs(n);
        for (int i = 0; i < s; ++i)
            cin >> hs[i];
        
        // Find each species private network.
        vector<vector<int>> pred(s, vector<int>(n));
        for (int i = 0; i < s; ++i)
            prim_minimum_spanning_tree(pns[i], &pred[i][0]);
        
        // Create joint minimum weight private networks graph.
        G g(n);
        WM wm2 = get(edge_weight, g);
        for (int i = 0; i < s; ++i)
        {
            for (int j = 0; j < n; ++j) 
            {
                auto e = edge(j, pred[i][j], pns[i]);
                if (e.second)
                {
                    auto e2 = edge(j, pred[i][j], g);
                    if (!e2.second)
                        wm2[add_edge(j, pred[i][j], g).first] = wm[i][e.first];
                    else if (wm[i][e.first] < wm2[e2.first])
                        wm2[e2.first] = wm[i][e.first];
                }
            }
        }
        
        // Find shortest a-b path on super-graph.
        vector<int> dist(n);
        dijkstra_shortest_paths(g, a, distance_map(&dist[0]));
        
        cout << dist[b] << endl;
    }
    
    return 0;
}

int main_supergraph()
{
    int t;
    cin >> t;
    
    while (t--)
    {
        int n, m, s, a, b;
        cin >> n >> m >> s >> a >> b;
        
        // Read each species graph.
        vector<G> pns(s, G(n));
        vector<WM> wm(s);
        for (int i = 0; i < s; ++i)
            wm[i] = get(edge_weight, pns[i]);
        for (int j = 0; j < m; ++j)
        {
            int t1, t2;
            cin >> t1 >> t2;
            for (int i = 0; i < s; ++i)
                cin >> wm[i][add_edge(t1, t2, pns[i]).first];
        }
        
        // Read hives (useless, MSTs unique).
        vector<int> hs(n);
        for (int i = 0; i < s; ++i)
            cin >> hs[i];
        
        // Find each species private network.
        vector<vector<int>> pred(s, vector<int>(n));
        for (int i = 0; i < s; ++i)
            prim_minimum_spanning_tree(pns[i], &pred[i][0]);
        
        // Create super-graph connecting private networks.
        G sg(s * n + 2);
        WM wm2 = get(edge_weight, sg);
        for (int i = 0; i < s; ++i)
        {
            for (int j = 0; j < n; ++j) 
            {
                auto e = edge(j, pred[i][j], pns[i]);
                if (e.second)
                    wm2[add_edge(n * i + j, n * i + pred[i][j], sg).first] = wm[i][e.first];
            }
        }
        for (int i = 0; i < s - 1; ++i)
            for (int j = 0; j < n; ++j)
                add_edge(n * i + j, n * (i + 1) + j, sg);
        for (int i = 0; i < s; ++i)
        {
            add_edge(s * n, n * i + a, sg);
            add_edge(s * n + 1, n * i + b, sg);
        }
        
        // Find shortest a-b path on super-graph.
        vector<int> dist(s * n + 2);
        dijkstra_shortest_paths(sg, s * n, distance_map(&dist[0]));
        
        cout << dist[s * n + 1] << endl;
    }
    
    return 0;
}
