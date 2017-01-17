#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int t;
    cin >> t;
    
    while (t--)
    {
        int n, i, k;
        cin >> n >> i >> k;
        
        // Read disks heights.
        vector<int> hs(n);
        for (int i = 0; i < n; ++i)
            cin >> hs[i];
        
        // All possible remainders.
        vector<bool> rs(k);
        
        // Try to add each disk.
        for (int l = 0; l < n; ++l)
        {
            // Find new possible remainders by adding this disk to the existing.
            vector<bool> ts(k);
            for (int m = 0; m < k; ++m)
                if (rs[m])
                    ts[(m + hs[l]) % k] = true;
            
            // Merge new remainders.
            for (int m = 0; m < k; ++m)
                rs[m] = rs[m] || ts[m];
            
            // Add this disk as a singleton set.
            rs[hs[l] % k] = true;
        }
        
        cout << (rs[i] ? "yes" : "no") << endl;
    }
    
    return 0;
}
