#include <iostream>
#include <vector>
#include <bitset>
#include <cmath>

using namespace std;

int solve(int i, int k, bitset<16> p, bitset<16> r, const vector<bitset<16>>& bs, vector<vector<int>>& m)
{
    // Base case.
    if (i == -1)
        return 0;
    
    // Use memoization.
    if (m[r[0]][i] != -1)
        return m[r[0]][i];
    
    // Use recursion.
    int d = ((bs[i] ^ r ^ p) & bitset<16>(pow(2, k) - 1)).count();
    return m[r[0]][i] = min(d + solve(i - 1, k, p, r, bs, m), k - d + 1 + solve(i - 1, k, p, ~r, bs, m));
}

int main()
{
    int t;
    cin >> t;
    
    while (t--)
    {
        int n, k, x;
        cin >> n >> k >> x;
        
        // Read bulbs initial states.
        vector<bitset<16>> bs(n / k);
        for (int i = 0; i < n / k; ++i)
            for (int j = 0; j < k; ++j)
                bs[i][k - j - 1] = [=](){ bool b; cin >> b; return b; }();
        
        // Solve recursion using dynamic programming.
        vector<vector<int>> m(2, vector<int>(n / k, -1));
        cout << solve(n / k - 1, k, bitset<16>(x), bitset<16>(), bs, m) << endl;
    }
    
    return 0;
}
