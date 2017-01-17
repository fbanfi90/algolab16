#include <iostream>
#include <vector>

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>

using namespace std;
using namespace CGAL;

typedef Exact_predicates_exact_constructions_kernel K;
typedef Min_circle_2_traits_2<K> T;
typedef Min_circle_2<T> MC;
typedef K::Point_2 P;

double c2d(const K::FT& x)
{
    double a = floor(to_double(x));
    while (a - 1 >= x) --a;
    while (a < x) ++a;
    return a;
}

int main()
{
    int t;
    cin >> t;
    
    while (t--)
    {
        int n;
        cin >> n;
        
        // Read cities coordinates.
        vector<P> cs(n);
        for (int i = 0; i < n; ++i)
            cin >> cs[i];
        
        // Compute and sort distances from old transmitter to all other cities.
        vector<pair<K::FT, int>> ds(n);
        for (int i = 0; i < n; ++i)
            ds[i] = make_pair(squared_distance(cs[0], cs[i]), i);
        sort(ds.begin(), ds.end());
        
        // Perform binary search on distances.
        K::FT best = numeric_limits<long>::max();
        int l = 0, r = n - 1;
        while (l != r)
        {
            // Compute minimum enclosing circle on cities not covered by old transmitter.
            int m = (l + r) / 2;
            vector<P> os(n - m - 1);
            for (int i = m + 1; i < n; ++i)
                os[i - m - 1] = cs[ds[i].second];
            MC mc(&os[0], &os[n - m - 1], true);
            
            // Take best circle.
            best = min(best, max(mc.circle().squared_radius(), ds[m].first));
            if (mc.circle().squared_radius() > ds[m].first) l = m + 1;
            else r = m;
        }
        
        cout << (long)c2d(best) << endl;
    }
    
    return 0;
}
