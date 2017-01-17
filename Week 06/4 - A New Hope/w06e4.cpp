#include <iostream>
#include <vector>
#include <bitset>
#include <map>

using namespace std;

typedef bitset<14> mask;
typedef map<int, mask> subs;
typedef map<int, subs> center;

int solve(vector<center>& cs, int c, int e, int k, int s, vector<vector<int>>& mem)
{
    // Use memoization.
    if (mem[c][e] != -1)
        return mem[c][e];
    
    // Use recursion on allowed subsets.
    int max = 0;
    for (int i = 0; i < 1 << s; ++i)
    {
        bool ok = !(i & e);
        for (int j = 0; j < s && ok; ++j)
            if (i & 1 << j)
                ok &= !(cs[c][c][j] & mask(i)).count();
        if (ok)
        {
            int tot = mask(i).count();
            for (auto c_ : cs[c])
            {
                if (c_.first != c)
                {
                    mask e_;
                    for (int j = 0; j < s && ok; ++j)
                        if (i & 1 << j)
                            e_ |= cs[c][c_.first][j];
                    tot += solve(cs, c_.first, e_.to_ulong(), k, s, mem);
                }
            }
            if (tot > max)
                max = tot;
        }
    }
    
    return mem[c][e] = max;
}

int main()
{
    int t;
    cin >> t;
    
    while (t--)
    {
        int k, s, m;
        cin >> k >> s >> m;
        
        // Read supervision network.
        vector<center> cs(k);
        for (int i = 0; i < m; ++i)
        {
            int u, v, h;
            cin >> u >> v >> h;
            cs[u][v] = subs();
            for (int j = 0; j < h; ++j)
            {
                int x, y;
                cin >> x >> y;
                cs[u][v][x][y] = 1;
            }
        }
        
        // Solve recursion using dynamic programming.
        vector<vector<int>> mem(k, vector<int>(1 << s, -1));
        cout << solve(cs, 0, 0, k, s, mem) << endl;
    }
}
