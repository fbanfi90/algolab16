#include <iostream>
#include <vector>
#include <limits>
#include <queue>
#include <set>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list_traits<vecS, vecS, directedS> T;
typedef adjacency_list<vecS, vecS, directedS, no_property,
        property<edge_capacity_t, long, property<edge_residual_capacity_t, long,
        property<edge_reverse_t, T::edge_descriptor>>>> G;
typedef property_map<G, edge_capacity_t>::type ECM;
typedef property_map<G, edge_residual_capacity_t>::type RCM;
typedef property_map<G, edge_reverse_t>::type REM;

void add(int u, int v, long c, G& g, ECM& ecm, REM& rem)
{
    auto e = add_edge(u, v, g);
    auto e_ = add_edge(v, u, g);
    ecm[e.first] = c;
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
        
        // Read limbs-figures connections and build graph.
        G g(n);
        ECM ecm = get(edge_capacity, g);
        REM rem = get(edge_reverse, g);
        RCM rcm = get(edge_residual_capacity, g);
        for (int i = 0; i < m; ++i)
        {
            int a, b, c;
            cin >> a >> b >> c;
            add(a, b, c, g, ecm, rem);
        }
        
        // Find the minimum s-t-max-flow.
        int s = 0, t = 0, f, max = numeric_limits<int>::max();
        for (int i = 0; i < n; ++i)
            if ((f = push_relabel_max_flow(g, i, (i + 1) % n)) < max)
                max = f, s = i, t = (i + 1) % n;
        
        // Recompute optimal residual graph.
        cout << push_relabel_max_flow(g, s, t) << endl;
        
        // Perform BFS on residual graph.
        std::queue<int> q;
        set<int> vs;
        q.push(s);
        vs.insert(s);
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            for (auto e = out_edges(u, g); e.first != e.second; ++e.first)
            {
                int v = target(*e.first, g);
                if (rcm[*e.first] >= 1 && !vs.count(v))
                    q.push(v), vs.insert(v);
            }
        }
        
        // Find visited nodes.
        cout << vs.size() << " ";
        for (auto v : vs)
            cout << v << " ";
        cout << endl;
    }
}
