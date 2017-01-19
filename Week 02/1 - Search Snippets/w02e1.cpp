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
        {
            for (int i = 0; i < ms[w]; ++i)
            {
                int p;
                cin >> p;
                pws.push_back(make_pair(p, w));
            }
        }
        sort(pws.begin(), pws.end());
        
        // Position of last occurrence of each word.
        vector<int> ls(n);
        for (int w = 0; w < n; ++w)
            ls[w] = -1;
        
        // Scan the list and update a, b, and length l.
        int a, b, lw = pws[0].second, l = numeric_limits<int>::max();
        for (auto pw : pws)
        {
            // Update last position of this word.
            ls[pw.second] = pw.first;
            
            // Update minimum index if necessary.
            if (pw.second == lw)
            {
                auto idx = min_element(ls.begin(), ls.end());
                lw = distance(ls.begin(), idx);
                a = *idx;
            }
            
            // Current word is always at maximum position.
            b = pw.first;
            
            // Update interval length if better.
            int l_ = b - a + 1;
            if (a != -1 && l_ < l)
                l = l_;
        }
        
        cout << l << endl;
    }
}
