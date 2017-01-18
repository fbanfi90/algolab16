#include <iostream>
#include <vector>
#include <algorithm>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

using namespace std;
using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel K;
typedef Delaunay_triangulation_2<K> T;
typedef T::Vertex_handle VH;
typedef K::Point_2 P;

inline int irho(K::FT x) { return ceil(sqrt(x - 0.5)); }

int main()
{
    while (true)
    {
        int n;
        cin >> n;
        if (n == 0)
            break;
        
        // Read dish boundaries.
        int l, b, r, t;
        cin >> l >> b >> r >> t;
        
        // Read germs positions and triangulate them.
        vector<P> gs(n);
        for (int i = 0; i < n; ++i)
            cin >> gs[i];
        T dt(gs.begin(), gs.end());
        
        // Compute time to first collision for all germs.
        int i = 0;
        vector<int> ts(n);
        for (auto v = dt.finite_vertices_begin(); v != dt.finite_vertices_end(); ++v)
        {
            // Compute minimum time from boundary.
            int m = std::min(
                    std::min(irho(v->point().x() - l), irho(r - v->point().x())),
                    std::min(irho(v->point().y() - b), irho(t - v->point().y()))), m_;
            
            // Compute minimum distance from other germs.
            if (n > 1)
            {
                auto e = dt.incident_edges(v);
                do
                    if (!dt.is_infinite(e) && (m_ = irho(sqrt(dt.segment(e).squared_length()) / 2)) < m)
                        m = m_;
                while (++e != dt.incident_edges(v));
            }
            ts[i++] = m;
        }
        
        // Sort times and take first, middle, and last.
        sort(ts.begin(), ts.end());
        cout << ts.front() << ' ' << ts[n / 2] << ' ' << ts.back() << endl;
    }
    
    return 0;
}
