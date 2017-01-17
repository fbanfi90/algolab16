#include <iostream>
#include <cmath>

#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

using namespace std;
using namespace CGAL;

typedef Gmpz ET;
typedef Quadratic_program<int> LP;
typedef Quadratic_program_solution<ET> S;

int main()
{
    while (true)
    {
        int n, d;
        cin >> n;
        if (n == 0)
            break;
        cin >> d;
        
        // Read linear program.
        LP lp(SMALLER, false, 0, false, 0);
        for (int i = 0; i < n; ++i)
        {
            int A = 0;
            for (int j = 0; j < d; ++j)
            {
                int a;
                cin >> a;
                lp.set_a(j, i, a);
                A += a * a;
            }
            lp.set_a(d, i, sqrt((double)A));
            int b;
            cin >> b;
            lp.set_b(i, b);
        }
        lp.set_a(d, n, -1);
        lp.set_b(n, 0);
        lp.set_c(d, -1);
        
        // Solve linear program.
        S s = solve_linear_program(lp, ET());
        cout << (s.is_infeasible() ? "none" : (s.is_unbounded() ? "inf" :
                to_string(-(int)to_double(s.objective_value())))) << endl;
    }
    
    return 0;
}
