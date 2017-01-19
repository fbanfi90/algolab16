#include <iostream>
#include <vector>

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
typedef graph_traits<G>::edge_descriptor E;

E add(int u, int v, long c, long w, G& g, ECM& ecm, EWM& ewm, REM& rem)
{
    auto e = add_edge(u, v, g);
    auto e_ = add_edge(v, u, g);
    ecm[e.first] = c;
    ewm[e.first] = w;
    ecm[e_.first] = 0;
    ewm[e_.first] = -w;
    rem[e.first] = e_.first;
    rem[e_.first] = e.first;
    return e.first;
}

int main()
{
    int t;
    cin >> t;
    
    while (t--)
    {
        int n, m, l, Q = 1 << 7;
        cin >> n >> m >> l;
        
        // Build graph.
        G g(n + 1);
        ECM ecm = get(edge_capacity, g);
        EWM ewm = get(edge_weight, g);
        REM rem = get(edge_reverse, g);
        RCM rcm = get(edge_residual_capacity, g);
        add(n, 0, l, 0, g, ecm, ewm, rem);
        for (int i = 0; i < n - 1; ++i)
            add(i, i + 1, l, Q, g, ecm, ewm, rem);
        
        // Read missions.
        vector<E> ms(m);
        for (int i = 0; i < m; ++i)
        {
            int x, y, q;
            cin >> x >> y >> q;
            ms[i] = add(x, y, 1, (y - x) * Q - q, g, ecm, ewm, rem);
        }
        
        // Compute MinCost-MaxFlow.
        successive_shortest_path_nonnegative_weights(g, n, n - 1);
        int p = 0;
        for (int i = 0; i < m; ++i)
        {
            int s = source(ms[i], g), t = target(ms[i], g);
            if (rcm[ms[i]] == 0)
                p += Q * (t - s) - ewm[ms[i]];
        }
        
        cout << p << endl;
    }
}
