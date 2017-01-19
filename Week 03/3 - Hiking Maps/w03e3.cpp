#include <iostream>
#include <vector>
#include <limits>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

using namespace std;
using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;

int main()
{
    int t;
    cin >> t;
    
    while (t--)
    {
        int m, n;
        cin >> m >> n;
        
        // Read path points.
        vector<P> ps(m);
        for (int i = 0; i < m; ++i)
            cin >> ps[i];
        
        // Read triangles points and adjust directions of edge points.
        vector<vector<P>> ts(n);
        for (int i = 0; i < n; ++i)
        {
            ts[i] = vector<P>(6);
            for (int j = 0; j < 6; ++j)
                cin >> ts[i][j];
            
            // Make sure points on edges are clock-wise oriented.
            for (int j = 0; j < 3; ++j)
                for (int k = 2; k <= 5; ++k)
                    if (right_turn(ts[i][2 * j], ts[i][2 * j + 1], ts[i][(2 * j + k) % 6]))
                        swap(ts[i][2 * j], ts[i][2 * j + 1]);
        }
        
        // Find all segments covered by each triangle.
        vector<vector<int>> cs(n, vector<int>());
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m - 1; ++j)
            {
                bool c = true;            
                for (int k = 0; k < 3; ++k)
                    c &= !right_turn(ts[i][2 * k], ts[i][2 * k + 1], ps[j]) &&
                         !right_turn(ts[i][2 * k], ts[i][2 * k + 1], ps[j + 1]);
                if (c)
                    cs[i].push_back(j);
            }
        }
        
        // Scanline to find the cheapest covering interval.
        int b, e, min = -1, d = numeric_limits<int>::max();
        vector<int> ls(m - 1, -1);
        for (int i = 0; i < n; ++i)
        {
            for (auto s : cs[i])
            {
                // Update last triangle covering this segment.
                ls[s] = i;
                
                // Update interval.
                if (s == min || min == -1)
                {
                    auto idx = min_element(ls.begin(), ls.end());
                    min = distance(ls.begin(), idx);
                    b = *idx;
                }
                e = i;
                
                // Update interval length if better.
                int d_ = e - b + 1;
                if (b != -1 && d_ < d)
                    d = d_;
            }
        }
        
        cout << d << endl;
    }
}
