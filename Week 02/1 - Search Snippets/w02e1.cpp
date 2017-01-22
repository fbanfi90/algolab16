#include <iostream>
#include <algorithm>
#include <vector>
#include <limits>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    
    int t;
    cin >> t;
    
    while (t--)
    {
        int n;
        cin >> n;
        
        // Read number of occurrences of each word.
        vector<int> ms(n);
        for (int w = 0; w < n; ++w)
            cin >> ms[w];
        
        // Create ordered list of position/word pairs.
        vector<pair<int, int>> pws;
        for (int w = 0; w < n; ++w)
            for (int i = 0; i < ms[w]; ++i)
                pws.push_back(make_pair([](){ int p; cin >> p; return p; }(), w));
        sort(pws.begin(), pws.end());
        
        // Position of last occurrence of each word.
        vector<int> ls(n);
        for (int w = 0; w < n; ++w)
            ls[w] = -1;
        
        // Sliding window on positions-words sequence.
        int a = 0, b = 0, c = 1, l = numeric_limits<int>::max(), l_, N = pws.size();
        vector<int> cs(n);
        cs[pws[0].second] = 1;
        while (a < N)
        {
            // If this interval contains all the words, check whether optimal.
            if (c == n && (l_ = pws[b].first - pws[a].first + 1) < l)
                l = l_;
            
            // Increase  lower- or upper-bound depending of number of different words.
            if (c < n && b < N - 1)
            {
                if (cs[pws[++b].second]++ == 0)
                    ++c;
            }
            else
            {
                if (cs[pws[a++].second]-- == 1)
                    --c;
            }
        }
        
        cout << l << endl;
    }
}
