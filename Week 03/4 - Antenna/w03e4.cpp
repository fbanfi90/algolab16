#include <iostream>
#include <vector>

#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>

using namespace std;
using namespace CGAL;

typedef Exact_predicates_exact_constructions_kernel_with_sqrt K;
typedef Min_circle_2_traits_2<K> T;
typedef Min_circle_2<T> MC;
typedef K::Point_2 P;

int main()
{
    while (true)
    {
        int n;
        cin >> n;
        if (n == 0)
            break;
        
        // Read citizens coordinates.
        vector<P> cs(n);
        for (int i = 0; i < n; ++i)
        {
            long x, y;
            cin >> x >> y;
            cs[i] = P(x, y);
        }
        
        // Compute minimum covering circle.
        MC mc(&cs[0], &cs[n], true);
        cout << ceil(sqrt(mc.circle().squared_radius())) << endl;
    }
}
