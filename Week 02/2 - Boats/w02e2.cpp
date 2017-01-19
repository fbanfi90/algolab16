#include <iostream>
#include <algorithm>
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
        
        // Read and sort lengths and positions.
        vector<pair<int, int>> bs(n);
        for (int i = 0; i < n; ++i)
            cin >> bs[i].second >> bs[i].first;
        sort(bs.begin(), bs.end());
        
        // Choose greedily whether to take each boat.
        int c = 0, pos = -1, pos_;
        for (auto b : bs)
        {
            // First boat.
            if (pos == -1)
                ++c, pos_ = b.first - b.second, pos = b.first;
            
            else
            {
                // If there is place, take this boat.
                if (b.first >= pos)
                    ++c, pos_ = pos, pos = max(pos_ + b.second, b.first);
                
                // If taking this boat instead of the last decreases pos, take it.
                else if (b.second < pos - pos_ && max(pos_ + b.second, b.first) < pos)
                    pos = max(pos_ + b.second, b.first);
            }
        }
        
        cout << c << endl;
    }
}
