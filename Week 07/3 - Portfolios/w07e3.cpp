#include <iostream>

#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

using namespace std;
using namespace CGAL;

typedef Gmpz ET;
typedef Quadratic_program<int> QP;
typedef Quadratic_program_solution<ET> S;

int main()
{
    while (true)
    {
        int n, m;
        cin >> n >> m;
        if (n == 0 && m == 0)
            break;
        
        // Read quadratic program.
        QP qp(SMALLER, true, 0, false, 0);
        for (int i = 0; i < n; ++i)
        {
            int c, r;
            cin >> c >> r;
            qp.set_a(i, 0, c);
            qp.set_a(i, 1, -r);
        }
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                int v;
                cin >> v;
                if (j <= i)
                    qp.set_d(i, j, 2 * v);
            }
        }
        
        // Solve quadratic program for each person.
        for (int j = 0; j < m; ++j)
        {
            int C, R, V;
            cin >> C >> R >> V;
            qp.set_b(0, C);
            qp.set_b(1, -R);
            S s = solve_nonnegative_quadratic_program(qp, ET());
            cout << (s.is_infeasible() || s.objective_value() > V ? "No." : "Yes.") << endl;
        }
    }
    
    return 0;
}
