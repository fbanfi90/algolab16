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
        
        int i = 0, j = 0, s = cs[0], i_ = 0, j_ = 0, v_ = std::abs(s - k);
        while (i < n)
        {
            s += s < k && j < n ? cs[++j] : -cs[i++];
            if (abs(s - k) < v_)
                i_ = i, j_ = j, v_ = abs(s - k);
        }
        cout << i_ << " " << j_ << endl;
    }
    
    return 0;
}

int main_partial_sums()
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
        
        vector<int> ps(n + 1);
        for (int i = 1; i <= n; ++i)
            ps[i] = ps[i - 1] + cs[i - 1];
        
        int i_, j_, v_ = std::numeric_limits<int>::max();
        for (int i = 0; i < n; ++i)
        {
            for (int j = i; j < n; ++j)
            {
                int s = ps[j + 1] - ps[i];
                int v = std::abs(k - s);
                if (v < v_)
                    v_ = v, i_ = i, j_ = j;
            }
        }
        cout << i_ << " " << j_ << endl;
    }
    
    return 0;
}

int main_brute_force()
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

        int i_, j_, v_ = std::numeric_limits<int>::max();
        for (int i = 0; i < n; ++i)
        {
            for (int j = i; j < n; ++j)
            {
                int s = 0;
                for (int c = i; c <= j; ++c)
                    s += cs[c];
                int v = std::abs(k - s);
                if (v < v_)
                    v_ = v, i_ = i, j_ = j;
            }
        }
        cout << i_ << " " << j_ << endl;
    }

    return 0;
}
