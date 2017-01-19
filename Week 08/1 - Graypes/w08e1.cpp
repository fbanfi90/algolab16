#include <iostream>
#include <vector>
#include <limits>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

using namespace std;
using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel K;
typedef Delaunay_triangulation_2<K> T;
typedef K::Point_2 P;

int main()
{
    while (true)
    {
        int n;
        cin >> n;
        if (n == 0)
            break;
        
        // Read Graypes coordinates.
        vector<P> gs(n);
        for (int i = 0; i < n; ++i)
            cin >> gs[i];
        
        // Compute Delaunay triangulation and find shortest edge.
        T t(gs.begin(), gs.end());
        K::FT min = numeric_limits<int>::max(), d;
        for (auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e)
            if ((d = t.segment(e).squared_length()) < min)
                min = d;
        
        cout << (int)ceil(to_double(50 * sqrt(min))) << endl;
    }
}
