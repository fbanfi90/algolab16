#include <iostream>
#include <vector>
#include <queue>
#include <set>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

using namespace std;
using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel K;
typedef Delaunay_triangulation_2<K> T;
typedef T::Face_handle FH;
typedef K::Point_2 P;

int main()
{
    ios_base::sync_with_stdio(false);
    
    while (true)
    {
        int n, m;
        cin >> n;
        if (n == 0)
            break;
        
        // Read infected people locations and triangulate them.
        vector<P> is(n);
        for (int i = 0; i < n; ++i)
            cin >> is[i];
        T t(is.begin(), is.end());
        
        // Find whether each healthy person can escape.
        cin >> m;
        for (int j = 0; j < m; ++j)
        {
            P p;
            long d;
            cin >> p >> d;
            
            // Perform BFS on triangulation faces.
            set<FH> v;
            queue<FH> q;
            bool e = false;
            v.insert(t.locate(p));
            if (squared_distance(t.nearest_vertex(p)->point(), p) >= d)
                q.push(t.locate(p));
            while (!q.empty() && !e)
            {
                FH f = q.front();
                q.pop();
                if (t.is_infinite(f))
                    e = true;
                for (int i = 0; i < 3; ++i)
                    if (!v.count(f->neighbor(i)) &&
                            squared_distance(f->vertex((i + 1) % 3)->point(),
                            f->vertex((i + 2) % 3)->point()) >= 4 * d)
                        q.push(f->neighbor(i)), v.insert(f->neighbor(i));
            }
            
            cout << (e ? 'y' : 'n');
        }
        
        cout << endl;
    }
}
