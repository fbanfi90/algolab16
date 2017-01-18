#include <iostream>
#include <vector>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

using namespace std;
using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel K;
typedef Quadratic_program<K::FT> LP;
typedef K::Segment_2 S;
typedef K::Point_2 P;
typedef Gmpzf ET;

int main()
{
    int t;
    cin >> t;
    
    while (t--)
    {
        int l, s, w;
        cin >> l >> s >> w;
        
        // Read lamp positions.
        vector<P> ls(l);
        for (int i = 0; i < l; ++i)
            cin >> ls[i];
        
        // Read stamps positions and maximum lighting.
        vector<P> ss(s);
        vector<int> ms(s);
        for (int j = 0; j < s; ++j)
            cin >> ss[j] >> ms[j];
        
        // Read walls.
        vector<S> ws(w);
        for (int k = 0; k < w; ++k)
            cin >> ws[k];
        
        // Set up linear program.
        LP lp(SMALLER, true, 1, true, 1 << 12);
        for (int j = 0; j < s; ++j)
        {
            lp.set_b(j, ms[j]);
            lp.set_b(s + j, -1);
            for (int i = 0; i < l; ++i)
            {
                K::FT I = 1 / squared_distance(ls[i], ss[j]);
                lp.set_a(i, j, I);
                lp.set_a(i, s + j, -I);
            }
        }
        
        // If a wall is between a lamp and a stamp, then remove constraint.
        for (int i = 0; i < l; ++i)
            for (int j = 0, ok = 1; j < s; ++j, ok = 1)
                for (int k = 0; k < w && ok; ++k)
                    if (do_intersect(ws[k], S(ls[i], ss[j])))
                        lp.set_a(i, j, 0), lp.set_a(i, s + j, 0), ok = 0;
        
        // Solve linear program.
        cout << (solve_linear_program(lp, ET()).is_infeasible() ? "no" : "yes") << endl;
    }
    
    return 0;
}
