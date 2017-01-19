#include <iostream>
#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/edmonds_karp_max_flow.hpp>

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
        int n, m;
        cin >> n >> m;
        
        // Read rounds results and build supply part of the graph.
        G g(m + n + 2);
        ECM ecm = get(edge_capacity, g);
        REM rem = get(edge_reverse, g);
        vector<int> ps(n, 0);
        int miss = 0;
        for (int i = 0; i < m; ++i)
        {
            int a, b, c;
            cin >> a >> b >> c;
            if (c == 0)
            {
                add(i, m + a, 1, g, ecm, rem);
                add(i, m + b, 1, g, ecm, rem);
                add(m + n, i, 1, g, ecm, rem);
                ++miss;
            }
            else ++ps[c == 1 ? a : b];
        }
        
        // Build demand part of the graph.
        int diff = 0;
        bool sol = true;
        for (int i = 0; i < n; ++i)
        {
            int s;
            cin >> s;
            if (s - ps[i] >= 0)
            {
                add(m + i, m + n + 1, s - ps[i], g, ecm, rem);
                diff += s - ps[i];
            }
            else sol = false;
        }
        
        // Compute maximum-flow iff data is consistent.
        if (sol &= diff == miss)
            sol = miss == push_relabel_max_flow(g, m + n, m + n + 1);
        
        cout << (sol ? "yes" : "no") << endl;
    }
}
