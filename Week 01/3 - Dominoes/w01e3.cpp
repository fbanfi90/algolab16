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
}
