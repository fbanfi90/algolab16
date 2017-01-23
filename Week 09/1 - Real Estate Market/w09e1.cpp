#include <iostream>

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
typedef property_map<G, edge_residual_capacity_t>::type RCM;
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
        int n, m, s, B = 100;
        cin >> n >> m >> s;
        
        // Create graph.
        G g(n + m + s + 2);
        ECM ecm = get(edge_capacity, g);
        EWM ewm = get(edge_weight, g);
        REM rem = get(edge_reverse, g);
        RCM rcm = get(edge_residual_capacity, g);
        int src = n + m + s, snk = src + 1;
        
        // Read limits on number of sites.
        for (int i = 0; i < s; ++i)
            add(n + m + i, snk, [](){ int l; cin >> l; return l; }(), 0, g, ecm, ewm, rem);
        
        // Read states-sites relationships.
        for (int j = 0; j < m; ++j)
            add(n + j, n + m + [](){ int s; cin >> s; return s; }() - 1, 1, 0, g, ecm, ewm, rem);
        
        // Read bids.
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
                add(i, n + j, 1, B - [](){ int b; cin >> b; return b; }(), g, ecm, ewm, rem);
            add(src, i, 1, 0, g, ecm, ewm, rem);
        }
        
        // Compute MinCost-MaxFlow.
        successive_shortest_path_nonnegative_weights(g, src, snk);
        int c = find_flow_cost(g), f = 0;
        for (auto e = out_edges(vertex(src, g), g); e.first != e.second; ++e.first)
            f += ecm[*e.first] - rcm[*e.first];
        cout << f << ' ' << f * B - c << endl;
    }
}
