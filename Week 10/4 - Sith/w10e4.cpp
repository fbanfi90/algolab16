#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Delaunay_triangulation_2.h>

using namespace std;
using namespace boost;
using namespace CGAL;

typedef adjacency_list<vecS, vecS, undirectedS> G;

typedef Exact_predicates_inexact_constructions_kernel K;
typedef Triangulation_face_base_2<K> FB;
typedef Triangulation_vertex_base_with_info_2<int, K> VB;
typedef Triangulation_data_structure_2<VB, FB> TDS;
typedef Delaunay_triangulation_2<K, TDS> T;
typedef K::Point_2 P;

int main()
{
    int t;
    cin >> t;
    
    while (t--)
    {
        int n, r;
        cin >> n >> r;
        long r2 = pow(r, 2);
        
        // Read planets positions.
        vector<P> ps(n);
        for (int i = 0; i < n; ++i)
            cin >> ps[i];
        
        // Find optimal k using binary search.
        int lk = 0, rk = n - 1, mk;
        while (lk != rk)
        {
            // Triangulate remaining planets and label them.
            int i = 0;
            mk = (lk + rk) / 2;
            T t(ps.begin() + mk, ps.end());
            for (auto v = t.finite_vertices_begin(); v != t.finite_vertices_end(); ++v)
                v->info() = i++;
            
            // Build distance-induced graph.
            G g(n - mk);
            for (auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e)
                if (t.segment(e).squared_length() <= r2)
                    add_edge(e->first->vertex((e->second + 1) % 3)->info(),
                            e->first->vertex((e->second + 2) % 3)->info(), g);
            
            // Find largest connected component.
            vector<int> cs(n - mk);
            int c = connected_components(g, &cs[0]);
            vector<int> ss(c);
            for (size_t i = 0; i < cs.size(); ++i)
                ++ss[cs[i]];
            
            // Update search interval.
            if (mk <= *max_element(ss.begin(), ss.end())) lk = mk + 1;
            else rk = mk;
        }
        
        cout << lk - 1 << endl;
    }
    
    return 0;
}
