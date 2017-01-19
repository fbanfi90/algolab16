#include <iostream>
#include <vector>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

using namespace std;
using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel K;
typedef K::Ray_2 R;
typedef K::Segment_2 S;

int main()
{
    while (true)
    {
        int n;
        cin >> n;
        if (n == 0)
            break;
        
        // Read phileas ray.
        R r;
        cin >> r;
        
        // Read obstacles segments.
        vector<S> os(n);
        for (int i = 0; i < n; ++i)
            cin >> os[i];
        
        // Check whether ray hits a segment.
        bool hit = false;
        for (int i = 0; i < n && !hit; ++i)
            hit |= do_intersect(r, os[i]);
        
        cout << (hit ? "yes" : "no") << endl;
    }
}
