#include <iostream>
#include <vector>
#include <limits>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS> G;

int main()
{
    int t;
    cin >> t;
    
    while (t--)
    {
        int n, c, f;
        cin >> n >> c >> f;
        
        // Read and sort characteristics of each student.
        vector<vector<string>> cs(n, vector<string>(c));
        for (int i = 0; i < n; ++i)
        {
            for (int k = 0; k < c; ++k)
                cin >> cs[i][k];
            sort(cs[i].begin(), cs[i].end());
        }
        
        // Create graph connecting students who share >f characteristics.
        G g(n);
        for (int i = 0; i < n; ++i)
        {
            for (int j = i; j < n; ++j)
            {
                // Search common characteristics in linear time.
                int cnt = 0, l = 0;
                for (int k = 0; k < c; ++k)
                {
                    while (l < c && cs[i][k] > cs[j][l]) ++l;
                    if (l < c && cs[i][k] == cs[j][l]) ++cnt;
                }
                
                if (cnt > f)
                    add_edge(i, j, g);
            }
        }
        
        // If the matching is perfect, the solution was not optimal.
        vector<int> mate(n);
        edmonds_maximum_cardinality_matching(g, &mate[0]);
        cout << (matching_size(g, &mate[0]) == (size_t)n / 2 ? "not optimal" : "optimal") << endl;
    }
}
