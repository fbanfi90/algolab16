#include <iostream>
#include <algorithm>
#include <set>
#include <vector>

using namespace std;

int main()
{
    int t;
    cin >> t;
    
    BEGIN:
    while (t--)
    {
        int n, m;
        cin >> n >> m;
        
        // Read strengths.
        int s_max = 0;
        vector<int> ss(n);
        for (int i = 0; i < n; ++i)
        {
            cin >> ss[i];
            if (ss[i] > s_max)
                s_max = ss[i];
        }
        
        // Read weights.
        multiset<int, greater<int>> ws;
        for (int i = 0; i < m; ++i)
        {
            int w;
            cin >> w;
            if (w > s_max)
            {
                cout << "impossible" << endl;
                goto BEGIN;
            }
            ws.insert(w);
        }
        
        // Sort strengths.
        sort(ss.begin(), ss.end(), greater<int>());
        
        // Greedy simulation.
        int r = 0;
        while (!ws.empty())
        {
            for (int i = 0; i < n; ++i)
            {
                auto b = ws.lower_bound(ss[i]);
                if (b != ws.end()) ws.erase(b);
                else break;                
            }
            ++r;
        }       
        cout << 3 * r - 1 << endl;
    }
}
