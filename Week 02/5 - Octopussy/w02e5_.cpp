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
    
    return 0;
}

int main_no()
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
        
        // Lists of detonated bombs and bombs on the ground at any time.
        vector<bool> detonated(n);
        vector<bool> ground(n);
        for (int i = (n - 1) / 2; i < n; ++i)
            ground[i] = true;
        
        // Greedy simulation.
        bool success = true;
        for (int t = 0; t < n; ++t)
        {
            int twos = 0, two_i;
            int min_t = numeric_limits<int>::max(), min_i;
            for (int i = 0; i < n; ++i)
            {
                if (ground[i] && !detonated[i])
                {
                    if (ts[(i - 1) / 2] < min_t)
                        min_t = ts[(i - 1) / 2], min_i = i;
                    if (ts[i] - t == 1)
                    {
                        detonated[i] = true;
                        if (i != 0 && detonated[i + 2 * (i % 2) - 1])
                            ground[(i - 1) / 2] = true;
                        min_t = -1;
                        break;
                    }
                    else if (ts[i] - t == 2)
                        ++twos, two_i = i;
                    else if (ts[i] - t < 1)
                    {
                        success = false;
                        break;
                    }
                }
            }
            if (!success)
                break;
            else if (twos >= 2)
            {
                detonated[two_i] = true;
                if (two_i != 0 && detonated[two_i + 2 * (two_i % 2) - 1])
                    ground[(two_i - 1) / 2] = true;
            }
            else if (min_t != -1)
            {
                detonated[min_i] = true;
                if (min_i != 0 && detonated[min_i + 2 * (min_i % 2) - 1])
                    ground[(min_i - 1) / 2] = true;
            }
        }
        
        cout << (success ? "yes" : "no") << endl;
    }
    
    return 0;
}
