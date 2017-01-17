#include <iostream>
#include <vector>
#include <limits>

using namespace std;

int solve(int c, int i, int p, int n, const vector<vector<int>>& ns, vector<vector<int>>& m)
{
    // Base case.
    if (i == n)
        return 0;
    
    // Use memoization.
    if (m[p][i] != -1)
        return m[p][i];
    
    // Use recursion.
    int min = numeric_limits<int>::max();
    int max = numeric_limits<int>::min();
    for (auto j : ns[i])
    {
        int s = solve(c, j, !p, n, ns, m);
        min = s < min ? s : min;
        max = s > max ? s : max;
    }
    
    return m[p][i] = (c == p ? min : max) + 1;
}

int main()
{
    int t;
    cin >> t;
    
    while (t--)
    {
        int n, m, r, b;
        cin >> n >> m >> r >> b;
        
        // Read transitions.
        vector<vector<int>> ns(n);
        for (int k = 0; k < m; ++k)
        {
            int i, j;
            cin >> i >> j;
            ns[i].push_back(j);
        }
        
        // Find optimal number of steps for both meeples.
        vector<vector<int>> m0(2, vector<int>(n, -1));
        vector<vector<int>> m1(2, vector<int>(n, -1));
        int s0 = solve(0, r, 0, n, ns, m0);
        int s1 = solve(1, b, 1, n, ns, m1);
        
        // If same # of steps, 0 wins iff # of steps even.
        cout << (s0 != s1 ? s0 > s1 : s0 % 2 == 0) << endl;
    }
    
    return 0;
}
