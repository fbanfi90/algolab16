#include <iostream>
#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list_traits<vecS, vecS, directedS> T;
typedef adjacency_list<vecS, vecS, directedS, no_property, property<edge_capacity_t, long,
        property<edge_residual_capacity_t, long, property<edge_reverse_t, T::edge_descriptor>>>> G;
typedef property_map<G, edge_capacity_t>::type ECM;
typedef property_map<G, edge_reverse_t>::type REM;

void add(int u, int v, long w, G& g, ECM& ecm, REM& rem)
{
    auto e = add_edge(u, v, g);
    auto e_ = add_edge(v, u, g);
    ecm[e.first] = w;
    ecm[e_.first] = 0;
    rem[e.first] = e_.first;
    rem[e_.first] = e.first;
}

int main()
{
    int t;
    cin >> t;
    
    while (t--)
    {
        int n, m, s;
        cin >> n >> m >> s;
        
        // Read shops locations and streets and build graph.
        G g(n + 1);
        ECM ecm = get(edge_capacity, g);
        REM rem = get(edge_reverse, g);
        for (int i = 0; i < s; ++i)
        {
            int l;
            cin >> l;
            add(l, n, 1, g, ecm, rem);
        }
        for (int i = 0; i < m; ++i)
        {
            int u, v;
            cin >> u >> v;
            add(u, v, 1, g, ecm, rem);
            add(v, u, 1, g, ecm, rem);
        }
        
        // Check whether max-flow equals number of shops.
        cout << (push_relabel_max_flow(g, 0, n) == s ? "yes" : "no") << endl;
    }
}
