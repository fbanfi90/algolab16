#include <iostream>
#include <queue>

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
        int g, s, l;
        cin >> g >> s >> l;
        
        // Build graph and connect source to stations and satellites to sink.
        G gr(g + s + 2);
        ECM ecm = get(edge_capacity, gr);
        REM rem = get(edge_reverse, gr);
        RCM rcm = get(edge_residual_capacity, gr);
        int src = g + s, snk = src + 1;
        for (int i = 0; i < g; ++i)
            add(src, i, 1, gr, ecm, rem);
        for (int i = 0; i < s; ++i)
            add(g + i, snk, 1, gr, ecm, rem);
        
        // Read station-satellites connections.
        for (int i = 0; i < l; ++i)
        {
            int u, v;
            cin >> u >> v;
            add(u, g + v, 1, gr, ecm, rem);
        }
        
        // Compute maxflow.
        push_relabel_max_flow(gr, src, snk);
        
        // Perform BFS on residual graph.
        vector<int> vs(g + s + 2);
        std::queue<int> q;
        vs[src] = true;
        q.push(src);
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            for (auto e = out_edges(u, gr); e.first != e.second; ++e.first)
            {
                int v = target(*e.first, gr);
                if (rcm[*e.first] == 1 && !vs[v])
                    q.push(v), vs[v] = true;
            }
        }
        
        // Find vertex cover.
        int g_ = 0, s_ = 0;
        for (int i = 0; i < g; ++i) if (!vs[i]) ++g_;
        for (int i = g; i < g + s; ++i) if (vs[i]) ++s_;
        cout << g_ << ' ' << s_ << endl;
        for (int i = 0; i < g; ++i) if (!vs[i]) cout << i << ' ';
        for (int i = g; i < g + s; ++i) if (vs[i]) cout << i - g << ' ';
        if (!(g_ == 0 && s_ == 0)) cout << endl;
    }
}
