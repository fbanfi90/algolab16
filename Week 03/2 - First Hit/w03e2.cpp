#include <iostream>
#include <vector>

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

using namespace std;
using namespace boost;
using namespace CGAL;

typedef Exact_predicates_exact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Ray_2 R;
typedef K::Segment_2 S;

double f2d(const K::FT& x)
{
    double a = floor(to_double(x));
    while (a > x) a -= 1;
    while (a + 1 <= x) a += 1;
    return a;
}

int main()
{
    ios_base::sync_with_stdio(false);
    
    while (true)
    {
        int n;
        cin >> n;
        if (n == 0)
            break;
        
        // Read phileas ray.
        R r;
        cin >> r;
        
        // Read obstacle segments and randomize their order.
        vector<S> os(n);
        for (int j = 0; j < n; ++j)
        {
            long r, s, t, u;
            cin >> r >> s >> t >> u;
            os[j] = S(P(r, s), P(t, u));
        }
        random_shuffle(os.begin(), os.end());
        
        // Find closest intersection point p with an obstacle segment on-line.
        P p;
        S s;
        bool hit = false;
        for (auto o : os)
        {
            // Consider a ray.
            if (!hit && do_intersect(r, o))
            {
                P p_;
                auto i = intersection(r, o);
                
                // Ray and obstacle nonparallel, intersection is a point.
                if (const P* q = get<P>(&*i))
                    p = *q;
                
                // Ray and obstacle parallel, intersection is a segment;
                // Find which endpoint is closer to the ray's source.
                else if (const S* s = get<S>(&*i))
                    p = squared_distance(r.source(), s->source()) <
                            squared_distance(r.source(), s->target()) ?
                            s->source() : s->target();
                
                // Reduce the ray to a segment.
                s = S(r.source(), p);
                hit = true;
            }
            
            // Consider a segment.
            else if (hit && do_intersect(s, o))
            {
                P p_;
                auto i = intersection(r, o);
                
                // Ray and obstacle nonparallel, intersection is a point.
                if (const P* q = get<P>(&*i))
                    p_ = *q;
                
                // Ray and obstacle parallel, intersection is a segment;
                // Find which endpoint is closer to the ray's source.
                else if (const S* s = get<S>(&*i))
                    p_ = squared_distance(r.source(), s->source()) <
                            squared_distance(r.source(), s->target()) ?
                            s->source() : s->target();
                
                // Update closest intersection.
                if (squared_distance(r.source(), p_) < squared_distance(r.source(), p))
                    p = p_;
            }
        }
        
        if (hit) cout << (long)f2d(p.x()) << " " << (long)f2d(p.y()) << endl;
        else cout << "no" << endl;
    }
    
    return 0;
}
