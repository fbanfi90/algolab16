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
}
