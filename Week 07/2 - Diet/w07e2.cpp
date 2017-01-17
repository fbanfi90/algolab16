#include <iostream>

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
        int n, m;
        cin >> n >> m;
        if (n == 0 && m == 0)
            break;
        
        // Read linear program.
        LP lp(SMALLER, true, 0, false, 0);
        for (int i = 0; i < n; ++i)
        {
            int min, max;
            cin >> min >> max;
            lp.set_b(2 * i, max);
            lp.set_b(2 * i + 1, -min);
        }
        for (int j = 0; j < m; ++j)
        {
            int p;
            cin >> p;
            lp.set_c(j, p);
            for (int i = 0; i < n; ++i)
            {
                int C;
                cin >> C;
                lp.set_a(j, 2 * i, C);
                lp.set_a(j, 2 * i + 1, -C);
            }
        }
        
        // Solve linear program.
        S s = solve_linear_program(lp, ET());
        cout << (s.is_infeasible() ? "No such diet." :
                to_string((int)to_double(s.objective_value()))) << endl;
    }
    
    return 0;
}
