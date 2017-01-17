#include <iostream>
#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/biconnected_components.hpp>

using namespace std;
using namespace boost;

struct EC
{
    enum { num = 555 };
    typedef edge_property_tag kind;
}
edge_component;

typedef adjacency_list<vecS, vecS, undirectedS, no_property, property <EC, size_t>> G;
typedef graph_traits<G>::edge_descriptor E;
typedef graph_traits<G>::edge_iterator EI;
typedef property_map<G, EC>::type C;

int main()
{
    int t;
    cin >> t;
    
    while (t--)
    {
        int n, m;
        cin >> n >> m;
        
        // Read graph.
        G g(n);
        for (int i = 0; i < m; ++i)
        {
            int u, v;
            cin >> u >> v;
            add_edge(u, v, g);
        }
        
        // Compute connected components.
        C c = get(edge_component, g);
        size_t nc = biconnected_components(g, c);
        
        // Find size-2 connected components (edges) and sort them.
        vector<vector<E>> cnt(nc);
        for (auto e = edges(g); e.first != e.second; ++e.first)
            cnt[c[*e.first]].push_back(*e.first);
        vector<pair<int, int>> es;
        for (auto i : cnt)
            if (i.size() == 1)
                es.push_back(make_pair(
                        min(source(i[0], g), target(i[0], g)),
                        max(source(i[0], g), target(i[0], g))));
        sort(es.begin(), es.end());
        
        cout << es.size() << endl;
        for (auto e : es)
            cout << e.first << " " << e.second << endl;
    }
    
    return 0;
}
