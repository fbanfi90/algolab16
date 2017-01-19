#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

int main()
{
    int t;
    cin >> t;
    
    while (t--)
    {
        int n;
        cin >> n;
        
        // Read times.
        vector<int> ts(n);
        for (int i = 0; i < n; ++i)
            cin >> ts[i];
        
        // Compute maximum deactivation time of each bomb greedily.
        for (int i = 1; i < n; ++i)
        {
            int d = !(i % 2) && ts[(i - 1) / 2] - ts[i - 1] == 1 ? 2 : 1;
            ts[i] = min(ts[i], ts[(i - 1) / 2] - d);
        }
        
        // Sort maximum deactivation times.
        sort(ts.begin(), ts.end());
        
        // Check that the sequence of maximum deactivation times is <= i.
        bool success = true;
        for (int i = 0; i < n && success; ++i)
            if (ts[i] <= i)
                success = false;
        
        cout << (success ? "yes" : "no") << endl;
    }
}
