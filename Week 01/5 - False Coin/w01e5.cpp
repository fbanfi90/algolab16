#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int t;
    cin >> t;
    
    while (t--)
    {
        int n, k;
        cin >> n >> k;
        
        vector<bool> candidate(n + 1, true), heavier(n + 1), lighter(n + 1);
        
        for (int i = 0; i < k; ++i)
        {
            int Pi;
            cin >> Pi;
            
            vector<int> left(Pi), right(Pi);
            for (int j = 0; j < Pi; ++j)
                cin >> left[j];
            for (int j = 0; j < Pi; ++j)
                cin >> right[j];
            
            char outcome;
            cin >> outcome;
            
            if (outcome == '=')
                for (int j = 0; j < Pi; ++j)
                    candidate[left[j]] = false, candidate[right[j]] = false;
            
            else
            {
                vector<bool> bad(n + 1);
                
                for (int j = 0; j < Pi; ++j)
                {
                    bad[left[j]] = true, bad[right[j]] = true;
                    
                    if (outcome == '<')
                        lighter[left[j]] = true, heavier[right[j]] = true;
                    else // outcome == '>'
                        heavier[left[j]] = true, lighter[right[j]] = true;
                    
                    if (lighter[left[j]] && heavier[left[j]])
                        candidate[left[j]] = false;
                    if (lighter[right[j]] && heavier[right[j]])
                        candidate[right[j]] = false;
                }
                
                for (int k = 1; k <= n; ++k)
                    if (!bad[k])
                        candidate[k] = false;
            }
        }
        
        int cnt = 0, sol;
        for (int k = 1; k <= n; ++k)
            if (candidate[k])
                ++cnt, sol = k;
        cout << (cnt == 1 ? sol : 0) << endl;
    }
    
    return 0;
}
