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
        int p, a, b;
        cin >> p;
        if (p == 0)
            break;
        cin >> a >> b;
        
        // Solve quadratic program.
        if (p == 1)
        {
            QP qp(SMALLER, true, 0, false, 0);
            qp.set_d(0, 0, 2 * a);
            qp.set_c(1, -b);
            qp.set_a(0, 0, 1);
            qp.set_a(1, 0, 1);
            qp.set_a(0, 1, 4);
            qp.set_a(1, 1, 2);
            qp.set_a(0, 2, -1);
            qp.set_a(1, 2, 1);
            qp.set_b(0, 4);
            qp.set_b(1, a * b);
            qp.set_b(2, 1);
            S s = solve_nonnegative_quadratic_program(qp, ET());
            cout << (s.is_infeasible() ? "no" :
                    to_string((int)floor(-to_double(s.objective_value())))) << endl;
        }
        else
        {
            QP qp(LARGER, false, 0, false, 0);
            qp.set_d(0, 0, 2 * a);
            qp.set_d(2, 2, 2);
            qp.set_c(1, b);
            qp.set_a(0, 0, 1);
            qp.set_a(1, 0, 1);
            qp.set_a(0, 1, 4);
            qp.set_a(1, 1, 2);
            qp.set_a(2, 1, 1);
            qp.set_a(0, 2, -1);
            qp.set_a(1, 2, 1);
            qp.set_a(2, 2, 0);
            qp.set_a(0, 3, 1);
            qp.set_a(1, 4, 1);
            qp.set_b(0, -4);
            qp.set_b(1, -a * b);
            qp.set_b(2, -1);
            qp.set_b(3, 0);
            qp.set_b(4, 0);
            qp.set_r(3, SMALLER);
            qp.set_r(4, SMALLER);
            S s = solve_quadratic_program(qp, ET());
            cout << (s.is_infeasible() ? "no" :
                    to_string((int)ceil(to_double(s.objective_value())))) << endl;            
        }
    }
    
    return 0;
}
