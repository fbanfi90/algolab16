#include <iostream>
#include <vector>
#include <cmath>
#include <map>

using namespace std;

int solve(vector<int>& ps, const vector<vector<int>>& cs, int n, const vector<int>& ms, map<vector<int>, int>& m)
{
    // Use memoization.
    if (m.count(ps))
        return m[ps];
    
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
    
    return m[ps] = max;
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
        map<vector<int>, int> m;
        cout << solve(ps, cs, n, ms, m) << endl;
    }
}
