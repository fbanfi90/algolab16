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
        int m, n, k, c;
        cin >> m >> n >> k >> c;
        
        // Create graph.
        G g(2 * m * n + 2);
        ECM ecm = get(edge_capacity, g);
        REM rem = get(edge_reverse, g);
        int src = 2 * m * n, snk = src + 1;
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                int in = 2 * (m * i + j), out = in + 1;
                add(in, out, c, g, ecm, rem);
                add(out, i == 0 ? snk : out - 2 * m - 1, 1, g, ecm, rem);
                add(out, i == n - 1 ? snk : out + 2 * m - 1, 1, g, ecm, rem);
                add(out, j == 0 ? snk : out - 3, 1, g, ecm, rem);
                add(out, j == m - 1 ? snk : out + 1, 1, g, ecm, rem);
            }
        }
        
        // Read knights initial positions.
        for (int i = 0; i < k; ++i)
        {
            int x, y;
            cin >> x >> y;
            add(src, 2 * (m * y + x), 1, g, ecm, rem);
        }
        
        // Compute max-flow.
        cout << push_relabel_max_flow(g, src, snk) << endl;
    }
}
