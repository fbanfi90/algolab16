#include <iostream>
#include <vector>
#include <limits>
#include <bitset>
#include <map>

using namespace std;

int main()
{
    int t;
    cin >> t;
    
    while (t--)
    {
        int n, m;
        cin >> n >> m;
        
        // Read target brightnesses.
        vector<int> bs(m);
        for (int j = 0; j < m; ++j)
            cin >> bs[j];
        
        // Read light-switch connections.
        vector<vector<int>> on(n, vector<int>(m));
        vector<vector<int>> off(n, vector<int>(m));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                cin >> on[i][j] >> off[i][j];
        
        // Bruteforce all combinations on half of the switches.
        map<vector<int>, int> list;
        for (int s = 0; s < 1 << n / 2; ++s)
        {
            vector<int> ss(m);
            for (int j = 0; j < m; ++j)
                for (int i = 0; i < n / 2; ++i)
                    ss[j] += s & 1 << i ? off[i][j] : on[i][j];
            int c = bitset<30>(s).count();
            if (!list.count(ss) || (list.count(ss) && c < list[ss]))
                list[ss] = c;
        }
        
        // Bruteforce on other half.
        int best = 31;
        for (int s = 0; s < 1 << (n / 2 + n % 2); ++s)
        {
            vector<int> ss(bs);
            for (int j = 0; j < m; ++j)
                for (int i = 0; i < n / 2 + n % 2; ++i)
                    ss[j] -= s & 1 << i ? off[n / 2 + i][j] : on[n / 2 + i][j];
            int c = bitset<30>(s).count();
            if (list.count(ss) && list[ss] + c < best)
                best = list[ss] + c;
        }
        
        cout << (best != 31 ? to_string(best) : "impossible") << endl;
    }
}
