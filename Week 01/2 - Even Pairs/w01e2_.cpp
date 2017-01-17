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
        
        // Read sequence.
        vector<int> xs(n);
        for (int i = 0; i < n; ++i)
            cin >> xs[i];
        
        // Perform a scanline on the sequence.
        int e = 0, o = 0, E = 0;
        for (int i = 0; i < n; ++i)
        {
            if (!xs[i]) ++e;
            else swap(e, o), ++o;
            E += e;
        }
        
        cout << E << endl;
    }
    
    return 0;
}

int main_partial_sums()
{
    int t;
    cin >> t;
    
    while (t--)
    {
        int n;
        cin >> n;
        
        // Read sequence.
        vector<int> xs(n);
        for (int i = 0; i < n; ++i)
            cin >> xs[i];
        
        // Precompute partial sums.
        int cnt = 0;
        vector<int> S(n, 0);
        S[0] = xs[0];
        for (int i = 1; i < n; ++i)
            S[i] = S[i - 1] + xs[i];
        
        // Check all possible i,j pairs.
        for (int i = 0; i < n; ++i)
            for (int j = i; j < n; ++j)
                if ((S[j] - S[i - 1]) % 2 == 0)
                    ++cnt;
        
        cout << cnt << endl;
    }
    
    return 0;
}
