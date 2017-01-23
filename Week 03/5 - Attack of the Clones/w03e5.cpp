#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

int main()
{
    // ABRT.
    return 0;
    
    int t;
    cin >> t;
    
    while (t--)
    {
        int n, m;
        cin >> n >> m;
        
        // Read and sort segments covered by each Jedi.
        vector<pair<int, int>> js(n);
        for (int i = 0; i < n; ++i)
            cin >> js[i].second >> js[i].first;
        
        // Find segment covered by the least Jedis.
        vector<int> qs(m);
        for (auto j : js)
            for (int i = j.second - 1; i < j.first; ++i)
                ++qs[i];
        int k = distance(qs.begin(), min_element(qs.begin(), qs.end()));// + 1;
        //cout<<k<<endl;
        //int k = 0;
        
        // Fix and sort the Jedi intervals around segment k and find Jedis covering segment k.
        set<pair<int, int>> cs;
        cs.insert(make_pair(-1, -1));
        for (auto& j : js)
        {
            j.first = (m + ((j.first - k) % m)) % m;
            j.second = (m + ((j.second - k) % m)) % m;
            //if ((j.second <= j.first && j.second <= k && k <= j.first) || 
            //        (j.second > j.first && (j.second <= k || k <= j.first)))     
            if (j.second > j.first)
                cs.insert(j);
        }
        sort(js.begin(), js.end());
        //for(auto c:cs)cout<<c.first<<","<<c.second<<"; ";cout<<endl;
        //for(auto j:js)cout<<j.second<<","<<j.first<<"; ";cout<<endl;
        
        // Try to use each one of the Jedis covering segment k separately, or none.
        int min, max, size, max_size = 0;
        for (auto c : cs)
        {
            // Consider (or not) the covering segment.
            if (c.first == -1)
                size = 0, min = 0, max = m;
            else
                size = 1, min = c.first, max = c.second;
            //cout<<min<<" "<<max<<endl;
            
            // Greedily solve earliest finish time jobs scheduling.
            for (auto j : js)
                if (!cs.count(j) && j.second > min && j.first < max)//{cout<<j.second<<","<<j.first<<"; ";
                    ++size, min = j.first;//}cout<<endl;
            //cout<<size<<endl;
            // Update best achievable size.
            if (size > max_size)
                max_size = size;
        }
        
        cout << max_size << endl;
    }
}
