#include <iostream>
#include <vector>
#include <limits>

using namespace std;

int main()
{
    int t;
    cin >> t;
    
    while (t--)
    {
        int n, k;
        cin >> n >> k;
        
        vector<int> cs(n);
        for (int i = 0; i < n; ++i)
            cin >> cs[i];
        
        int i = 0, j = 0, s = cs[0], i_ = 0, j_ = 0, v_ = abs(s - k);
        while (i < n)
        {
            s += s < k && j < n ? cs[++j] : -cs[i++];
            if (abs(s - k) < v_)
                i_ = i, j_ = j, v_ = abs(s - k);
        }
        cout << i_ << " " << j_ << endl;
    }
}
