#include <iostream>
#include <vector>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

using namespace std;
using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel K;
typedef Delaunay_triangulation_2<K> T;
typedef K::Point_2 P;

int main()
{
    ios_base::sync_with_stdio(false);
    cout << setiosflags(ios::fixed) << setprecision(0);
    
    while (true)
    {
        int n, m;
        cin >> n;
        if (n == 0)
            break;
        
        // Read restaurants locations.
        vector<P> rs(n);
        for (int i = 0; i < n; ++i)
            cin >> rs[i];
        
        // Triangulate restaurants.
        T t(rs.begin(), rs.end());
        
        // Find for each new restaurant the distance from the nearest existing.
        cin >> m;
        for (int j = 0; j < m; ++j)
        {
            P p;
            cin >> p;
            cout << squared_distance(p, t.nearest_vertex(p)->point()) << endl;
        }
    }
    
    return 0;
}
