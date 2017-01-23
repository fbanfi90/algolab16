#include <iostream>
#include <vector>
#include <map>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list_traits<vecS, vecS, directedS> T;
typedef adjacency_list<vecS, vecS, directedS, no_property,
        property<edge_capacity_t, long, property<edge_residual_capacity_t, long,
        property<edge_reverse_t, T::edge_descriptor, property<edge_weight_t, long>>>>> G;
typedef property_map<G, edge_capacity_t>::type ECM;
typedef property_map<G, edge_weight_t>::type EWM;
typedef property_map<G, edge_reverse_t>::type REM;

void add(int u, int v, long c, long w, G& g, ECM& ecm, EWM& ewm, REM& rem)
{
    auto e = add_edge(u, v, g);
    auto e_ = add_edge(v, u, g);
    ecm[e.first] = c;
    ewm[e.first] = w;
    ecm[e_.first] = 0;
    ewm[e_.first] = -w;
    rem[e.first] = e_.first; 
    rem[e_.first] = e.first; 
}

int main()
{
    int t;
    cin >> t;
    
    while (t--)
    {
        int n, s, tmax = 100000, pmax = 100;
        cin >> n >> s;
        
        // Create graph.
        G g;
        ECM ecm = get(edge_capacity, g);
        EWM ewm = get(edge_weight, g);
        REM rem = get(edge_reverse, g);
        int src = add_vertex(g), snk = add_vertex(g);
        
        // Read initial number of cars at each station.
        int tot = 0;
        vector<int> ls(s);
        for (int i = 0; i < s; ++i)
            tot += [&ls, i](){ cin >> ls[i]; return ls[i]; }();
        
        // Add begin and end node for each station.
        vector<map<int, int>> ts(s);
        for (int i = 0; i < s; ++i)
            add(src, ts[i][0] = add_vertex(g), ls[i], 0, g, ecm, ewm, rem),
            add(ts[i][tmax] = add_vertex(g), snk, tot, 0, g, ecm, ewm, rem);
        
        // Read queries and add corresponding edges to the graph.
        for (int i = 0; i < n; ++i)
        {
            int s, t, d, a, p;
            cin >> s >> t >> d >> a >> p;
            --s, --t;
            
            // Add time vertices if not yet there and relative edge.
            if (!ts[s].count(d)) ts[s][d] = add_vertex(g);
            if (!ts[t].count(a)) ts[t][a] = add_vertex(g);
            add(ts[s][d], ts[t][a], 1, (a - d) * pmax - p, g, ecm, ewm, rem);
        }
        
        // Add parking edges between time nodes of each station.
        for (int i = 0; i < s; ++i)
            for (auto it = ts[i].begin(); it != prev(ts[i].end(), 1); ++it)
                add(it->second, next(it, 1)->second, tot,
                        (next(it, 1)->first - it->first) * pmax, g, ecm, ewm, rem);
        
        // Compute MinCost-MaxFlow.
        successive_shortest_path_nonnegative_weights(g, src, snk);
        cout << (long)tmax * pmax * tot - find_flow_cost(g) << endl;
    }
}
