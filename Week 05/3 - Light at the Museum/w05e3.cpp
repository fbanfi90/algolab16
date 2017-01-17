#include <iostream>
#include <vector>
#include <limits>
#include <bitset>

using namespace std;

int main()
{return 0;//TL
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
        
        // Try all switch combinations using brute force.
        bool one = false;
        int best = numeric_limits<int>::max();
        
        vector<vector<int>> ss();
        for (int s = 0; s < (1 << n) / 2; ++s)
        {
            bool ok = true;
            for (int j = 0; j < m; ++j)
            {
                int sum = 0;
                for (int i = 0; i < n; ++i)
                    sum += s & 1 << i ? off[i][j] : on[i][j];
                ok &= sum == bs[j];
            }
            if (ok)
                best = min(best, (int)bitset<30>(s).count());
            one |= ok;
        }
        
        cout << (one ? to_string(best) : "impossible") << endl;
    }
    
    return 0;
}

int main_naive_bruteforce()
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
        
        // Try all switch combinations using brute force.
        bool one = false;
        int best = numeric_limits<int>::max();
        for (int s = 0; s < 1 << n; ++s)
        {
            bool ok = true;
            for (int j = 0; j < m; ++j)
            {
                int sum = 0;
                for (int i = 0; i < n; ++i)
                    sum += s & 1 << i ? off[i][j] : on[i][j];
                ok &= sum == bs[j];
            }
            if (ok)
                best = min(best, (int)bitset<30>(s).count());
            one |= ok;
        }
        
        cout << (one ? to_string(best) : "impossible") << endl;
    }
    
    return 0;
}
