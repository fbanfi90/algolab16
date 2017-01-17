#include <iostream>
#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

using namespace std;
using namespace boost;

typedef	adjacency_list_traits<vecS, vecS, directedS> T;
typedef adjacency_list<vecS, vecS, directedS, no_property, property<edge_capacity_t, long,
        property<edge_residual_capacity_t, long, property<edge_reverse_t, T::edge_descriptor>>>> G;
typedef	property_map<G, edge_capacity_t>::type ECM;
typedef	property_map<G, edge_reverse_t>::type REM;

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
        int l, p;
        cin >> l >> p;
        
        // Build graph.
        int tot = 0;
        G g(l + 2);
        ECM ecm = get(edge_capacity, g);
        REM rem = get(edge_reverse, g);
        for (int i = 0; i < l; ++i)
        {
            int s, d;
            cin >> s >> d;
            add(l, i, s, g, ecm, rem);
            add(i, l + 1, d, g, ecm, rem);
            tot += d;
        }
        for (int i = 0; i < p; ++i)
        {
            int f, t, c, C;
            cin >> f >> t >> c >> C;
            add(f, t, C - c, g, ecm, rem);
            add(l, t, c, g, ecm, rem);
            add(f, l + 1, c, g, ecm, rem);
            tot += c;
        }
        
        // Check whether max-flow equals total demand.
        cout << (push_relabel_max_flow(g, l, l + 1) == tot ? "yes" : "no") << endl;
    }
    
    return 0;
}
