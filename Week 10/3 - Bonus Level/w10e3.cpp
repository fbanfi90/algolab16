#include <iostream>
#include <vector>

using namespace std;

int solve(int i1, int j1, int i2, int j2, int n, vector<vector<int>>& as, vector<vector<vector<int>>>& m)
{
    // Base cases.
    if (i1 < 0 || i1 >= n || j1 < 0 || j1 >= n || i2 < 0 || i2 >= n || j2 < 0 || j2 >= n)
        return 0;
    
    // Paths cannot intersect.
    if (i1 == i2 && j1 == j2)
        return 0;
    
    // Use memoization.
    if (m[i1][j1][i2] != -1)
        return m[i1][j1][i2];
    
    // Use recursion.
    return m[i1][j1][i2] = max(
            max(solve(i1 + 1, j1, i2 + 1, j2, n, as, m), solve(i1, j1 + 1, i2, j2 + 1, n, as, m)),
            max(solve(i1 + 1, j1, i2, j2 + 1, n, as, m), solve(i1, j1 + 1, i2 + 1, j2, n, as, m)))
            + as[i1][j1] + as[i2][j2];
}

int main()
{
    int t;
    cin >> t;
    
    while (t--)
    {
        int n;
        cin >> n;
        
        // Read map.
        vector<vector<int>> as(n, vector<int>(n));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                cin >> as[i][j];
        
        // Solve recursion using dynamic programming.
        vector<vector<vector<int>>> m(n, vector<vector<int>>(n, vector<int>(n, -1)));
        cout << solve(0, 1, 1, 0, n, as, m) + as[0][0] + as[n - 1][n - 1] << endl;
    }
}
