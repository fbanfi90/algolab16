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
        
        // Read matrix.
        vector<vector<int>> M(n, vector<int>(n));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                cin >> M[i][j];
        
        // Apply even-sequences algorithm line-wise.
        int E = 0;
        vector<vector<int>> S(n, vector<int>(n));
        for (int k = 0; k < n; ++k)
        {
            // Consider sub-matrices of height k + 1.
            for (int i = 0; i < n - k; ++i)
                for (int j = 0; j < n; ++j)
                    S[i][j] ^= M[i + k][j];
            
            // Perform a scanline on each row of S.
            for (int i = 0; i < n - k; ++i)
            {
                int e = 0, o = 0;
                for (int j = 0; j < n; ++j)
                {
                    if (!S[i][j]) ++e;
                    else swap(e, o), ++o;
                    E += e;
                }
            }
        }
        
        cout << E << endl;
    }
    
    return 0;
}
