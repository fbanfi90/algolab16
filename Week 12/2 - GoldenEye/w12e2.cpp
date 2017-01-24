#include <iostream>
#include <vector>
#include <map>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

using namespace std;
using namespace boost;
using namespace CGAL;

typedef adjacency_list<vecS, vecS, undirectedS> G;

typedef Exact_predicates_inexact_constructions_kernel K;
typedef Delaunay_triangulation_2<K> T;
typedef K::Point_2 P;

// Passing only first test set.
int main()
{
    int t;
    cin >> t;
    
    while (t--)
    {
        int n, m;
        long p;
        cin >> n >> m >> p;
        
        // Read and triangulate jammers.
        vector<P> js(n);
        map<P, int> p2i;
        for (int i = 0; i < n; ++i)
            p2i[([&js, i](){ cin >> js[i]; return js[i]; }())] = i;
        T dt(js.begin(), js.end());
        
        // Build intersection graph and find its components.
        G g(n);
        for (int i = 0; i < n; ++i)
            for (int j = i; j < n; ++j)
                if (squared_distance(js[i], js[j]) <= p)
                    add_edge(i, j, g);
        vector<int> comp(n);
        connected_components(g, &comp[0]);
        
        // Process missions.
        for (int j = 0; j < m; ++j)
        {
            P s, t, s_, t_;
            cin >> s >> t;
            s_ = dt.nearest_vertex(s)->point(), t_ = dt.nearest_vertex(t)->point();
            cout << (squared_distance(s, s_) <= p / 4 && squared_distance(t, t_) <= p / 4
                    && comp[p2i[s_]] == comp[p2i[t_]] ? 'y' : 'n');
        }
        
        cout << endl << 4 * p << endl << p << endl;
    }
}
