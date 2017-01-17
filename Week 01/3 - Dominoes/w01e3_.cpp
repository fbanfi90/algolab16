#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int t;
    cin >> t;
    
    while (t--)
    {
        int n;
        cin >> n;
        
        // Read heights.
        vector<int> hs(n);
        for (int i = 0; i < n; ++i)
            cin >> hs[i];
        
        // Perform a scanline.
        int c = 0, d = 1;
        for (int i = 0; i < n; ++i)
        {
            c = max(hs[i] - 1, c - 1);
            if (c == 0)
                break;
            ++d;
        }
        
        cout << (d < n ? d : n) << endl;
    }
    
    return 0;
}

int main_brute_force()
{
    int t;
    cin >> t;
    
    while (t--)
    {
        int n;
        cin >> n;
        
        // Read heights.
        vector<int> hs(n);
        for (int i = 0; i < n; ++i)
            cin >> hs[i];
        
        // Topple each piece one by one and see how far it gets.
        vector<bool> ds(n);
        ds[0] = true;
        int i;
        for (i = 0; i < n; ++i)
        {
            if (ds[i] == false)
                break;
            for (int j = 0; j - i < hs[i]; ++j)
            {
                if (j >= n)
                {
                    i = n - 1;
                    break;
                }
                ds[j] = true;
            }
        }
        
        cout << i << endl;
    }
    
    return 0;
}
