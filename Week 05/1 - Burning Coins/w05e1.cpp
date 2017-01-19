#include <iostream>
#include <vector>

using namespace std;

int solve(int i, int j, bool t, const vector<int>& vs, vector<vector<int>>& m)
{
    // Base case.
    if (i == j)
        return t ? vs[i] : 0;
    
    // Use memoization.
    if (m[i][j] != -1)
        return m[i][j];
    
    // Use recursion.
    return m[i][j] = t ? max(vs[i] + solve(i + 1, j, !t, vs, m), vs[j] + solve(i, j - 1, !t, vs, m))
                       : min(solve(i + 1, j, !t, vs, m), solve(i, j - 1, !t, vs, m));
}

int main()
{
    int t;
    cin >> t;
    
    while (t--)
    {
        int n;
        cin >> n;
        
        // Read coins values.
        vector<int> vs(n);
        for (int i = 0; i < n; ++i)
            cin >> vs[i];
        
        // Solve recursion using dynamic programming.
        vector<vector<int>> m(n, vector<int>(n, -1));
        cout << solve(0, n - 1, true, vs, m) << endl;
    }
}
