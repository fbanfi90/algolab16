#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int solve(vector<int>& ps, const vector<vector<int>>& cs, int n, const vector<int>& ms, vector<int>& m)
{
    // Get the hash of this state.
    int h = 0;
    for (int i = 0; i < n; ++i)
    {
        int t = 1;
        for (int j = 0; j < i; ++j)
            t *= ms[j] + 1;
        h += (ps[i] + 1) * t;
    }
    
    // Use memoization.
    if (m[h] != -1)
        return m[h];
    
    // Use recursion on monochromatic subsets.
    int max = 0;
    for (int s = 1; s < 1 << n; ++s)
    {
        bool ok = true;
        int k = 0, c = -1, g;
        vector<int> ps_ = ps;
        for (int i = 0; i < n && ok; ++i)
        {
            if (s & 1 << i)
            {
                ++k, --ps_[i];
                if (ps[i] == -1) ok = false;
                else if (c == -1) c = cs[i][ps[i]];
                else if (cs[i][ps[i]] != c) ok = false;
            }
        }
        if (ok && (g = solve(ps_, cs, n, ms, m) + pow(2, k - 2)) > max)
            max = g;
    }
    
    return m[h] = max;
}

int main()
{
    int t;
    cin >> t;
    
    while (t--)
    {
        int n;
        cin >> n;
        
        // Read stack sizes.
        vector<int> ms(n);
        for (int i = 0; i < n; ++i)
            cin >> ms[i];
        
        // Read stacks.
        vector<int> ps = ms;
        vector<vector<int>> cs(n);
        for (int i = 0; i < n; ++i)
        {
            --ps[i];
            cs[i] = vector<int>(ms[i]);
            for (int j = 0; j < ms[i]; ++j)
                cin >> cs[i][j];
        }
        
        // Solve recursion using dynamic programming.
        vector<int> m([=](){ int N = 1; for (int i = 0; i < n; ++i) N *= ms[i] + 1; return N; }(), -1);
        cout << solve(ps, cs, n, ms, m) << endl;
    }
}
