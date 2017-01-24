#include <iostream>
#include <vector>
#include <map>

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
        int n;
        cin >> n;
        
        // Read chessboard and count missing cells.
        int m = 0;
        vector<vector<int>> xs(n, vector<int>(n));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (![&xs, i, j](){ cin >> xs[i][j]; return xs[i][j]; }())
                    ++m;
        
        // Build bipartite graph.
        G g(n * n);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (xs[i][j])
                    for (auto k : map<int, int>{ {i - 1, j - 2}, {i - 1, j + 2},
                            {i + 1, j - 2}, {i + 1, j + 2},
                            {i - 2, j - 1}, {i - 2, j + 1},
                            {i + 2, j - 1}, {i + 2, j + 1} })
                        if (k.first >= 0 && k.first < n && k.second >= 0 && k.second < n
                                && xs[k.first][k.second])
                            add_edge(n * i + j, n * k.first + k.second, g);
        
        // Compute |max. match.| = |min. vtx. cov.| = |G| - |max. ind. set|. 
        vector<int> mate(n * n);
        edmonds_maximum_cardinality_matching(g, &mate[0]);
        cout << n * n - m - matching_size(g, &mate[0]) << endl;
    }
}
