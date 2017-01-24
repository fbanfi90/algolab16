#include <iostream>
#include <vector>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/QP_functions.h>

using namespace std;
using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel K;
typedef Delaunay_triangulation_2<K> T;
typedef Quadratic_program<double> LP;
typedef K::Point_2 P;
typedef Gmpzf ET;

int main()
{
    int t;
    cin >> t;
    
    while (t--)
    {
        int a, s, b, e;
        cin >> a >> s >> b >> e;
        
        // Read asteroids positions and densities.
        vector<P> as(a);
        vector<int> ds(a);
        for (int i = 0; i < a; ++i)
            cin >> as[i] >> ds[i];
        
        // Read shooting points positions.
        vector<P> ss(s);
        for (int j = 0; j < s; ++j)
            cin >> ss[j];
        
        // Read and triangulate bounty hunters positions.
        vector<P> bs(b);
        for (int k = 0; k < b; ++k)
            cin >> bs[k];
        T dt(bs.begin(), bs.end());
        
        // Get maximal radius of each shooting point.
        vector<double> rs(s, numeric_limits<double>::max());
        if (b > 0)
            for (int j = 0; j < s; ++j)
                rs[j] = squared_distance(ss[j], dt.nearest_vertex(ss[j])->point());
        
        // Set up LP.
        LP lp(LARGER, true, 0, false, 0);
        for (int i = 0; i < a; ++i)
        {
            lp.set_b(i, ds[i]);
            for (int j = 0; j < s; ++j)
                if (squared_distance(as[i], ss[j]) <= rs[j])
                    lp.set_a(j, i, 1 / std::max(1., to_double(squared_distance(as[i], ss[j]))));
        }
        for (int j = 0; j < s; ++j)
            lp.set_c(j, 1);
        
        // Solve LP.
        auto sol = solve_linear_program(lp, ET());
        cout << (!sol.is_infeasible() && sol.objective_value() <= e ? 'y' : 'n') << endl;
    }
}
