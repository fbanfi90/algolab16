#include <iostream>

using namespace std;

int main()
{
    int t;
    cin >> t;
    
    while (t--)
    {
        int m;
        cin >> m;
        
        // Read sequence and build sum.
        double s = 0;
        for (int i = 0; i < m; ++i)
        {
            double f;
            cin >> f;
            s += f;
        }
        
        cout << s << endl;
    }
}
