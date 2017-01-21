#include <iostream>
#include <vector>
#include <map>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

using namespace std;
using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel K;
typedef Delaunay_triangulation_2<K> T;
typedef K::Point_2 P;

int main()
{
    int t;
    cin >> t;
    
    while (t--)
    {
        int m, n, h;
        cin >> m >> n;
        
        // Read participants and lamps postions.
        vector<P> ps(m), ls(n);
        vector<int> rs(m);
        map<P, int> imap;
        for (int j = 0; j < m; ++j)
            cin >> ps[j] >> rs[j];
        cin >> h;
        for (int i = 0; i < n; ++i)
        {
            cin >> ls[i];
            imap[ls[i]] = i;
        }
        
        // Triangulate lamps.
        T t(ls.begin(), ls.end());
        
        // Find for each partecipant which (if any) lamp hits him first.
        int last = -1;
        bool nw = true;
        vector<int> ws;
        vector<bool> hs(m);
        for (int j = 0; j < m; ++j)
        {
            P l = t.nearest_vertex(ps[j])->point();
            if (sqrt(to_double(squared_distance(ps[j], l))) >= double(h + rs[j]))
            {
                cout << j << ' ';
                nw = false;
            }
            
            // Find the first lamp to hit this participant, if there are still no winners.
            else if (nw)
            {
                for (int i = 0; imap[l] >= last && i <= imap[l]; ++i)
                {
                    if (sqrt(to_double(squared_distance(ps[j], ls[i]))) < double(h + rs[j]))
                    {
                        if (i > last) last = i, ws.clear();
                        if (i == last) ws.push_back(j);
                        break;
                    }
                }
            }
        }
        
        if (nw)
            for (int w : ws)
                cout << w << ' ';
        cout << endl;
    }
}
