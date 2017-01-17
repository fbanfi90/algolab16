#include <iostream>
#include <algorithm>
#include <set>
#include <vector>

using namespace std;

int main()
{
    int t;
    cin >> t;
    
    BEGIN:
    while (t--)
    {
        int n, m;
        cin >> n >> m;
        
        // Read and sort strengths.
        vector<int> ss(n);
        for (int i = 0; i < n; ++i)
            cin >> ss[i];
        sort(ss.begin(), ss.end());
        
        // Read and sort weights.
        vector<int> ws(m);
        for (int i = 0; i < m; ++i)
            cin >> ws[i];
        sort(ws.begin(), ws.end());
        
        // Reduce problem.
        int c = 0;
        vector<int> bs;
        vector<pair<int, int>> fs;
        for (int i = 0; i < n - 1; ++i)
        {
            if (ss[i] != ss[i + 1])
            {
                bs.push_back(0);
                fs.push_back(make_pair(c + 1, ss[i]));
                c = 0;
            }
            else c++;
        }
        bs.push_back(0);
        fs.push_back(make_pair(c + 1, ss[n - 1]));
        int d = bs.size();
        int j = 0;
        for (int i = 0; i < m; ++i)
        {
            while (ws[i] > fs[j].second && j < d)
                ++j;
            if (j < d)
                ++bs[j];
            else
            {
                cout << "impossible" << endl;
                goto BEGIN;
            }
        }
        
        // Simulate rounds.
        int r = 0, d_ = 0;
        while (d_ < d)
        {
            for (int i = d - 1; i > 0; --i)
            {
                if (bs[i] != -1 && bs[i] != -2)
                {
                    int f = fs[i].first, b = bs[i];
                    bs[i] = max(0, b - f);
                    if (bs[i] == 0)
                        ++d_, fs[i - 1].first += f - b, fs[i].first -= f - b, bs[i] = -1;
                }
                else
                    fs[i - 1].first += fs[i].first, fs[i].first = 0, bs[i] = -2;
            }
            if (bs[0] != -1)
            {
                bs[0] = max(0, bs[0] - fs[0].first);
                if (bs[0] == 0)
                    ++d_, bs[0] = -1;
            }
            ++r;
        }
        
        cout << 3 * r - 1 << endl;
    }
    
    return 0;
}

int main_multiset()
{
    int t;
    cin >> t;
    
    BEGIN:
    while (t--)
    {
        int n, m;
        cin >> n >> m;
        
        // Read strengths.
        int s_max = 0;
        vector<int> ss(n);
        for (int i = 0; i < n; ++i)
        {
            cin >> ss[i];
            if (ss[i] > s_max)
                s_max = ss[i];
        }
        
        // Read weights.
        multiset<int, greater<int>> ws;
        for (int i = 0; i < m; ++i)
        {
            int w;
            cin >> w;
            if (w > s_max)
            {
                cout << "impossible" << endl;
                goto BEGIN;
            }
            ws.insert(w);
        }
        
        // Sort strengths.
        sort(ss.begin(), ss.end(), greater<int>());
        
        // Greedy simulation.
        int r = 0;
        while (!ws.empty())
        {
            for (int i = 0; i < n; ++i)
            {
                auto b = ws.lower_bound(ss[i]);
                if (b != ws.end())
                    ws.erase(b);
                else
                    break;                
            }
            ++r;
        }       
        cout << 3 * r - 1 << endl;
    }
    
    return 0;
}

int main_naive()
{
    int t;
    cin >> t;
    
    while (t--)
    {
        int n, m;
        cin >> n >> m;
        
        // Read strengths.
        int s_max = 0;
        vector<int> ss(n);
        for (int i = 0; i < n; ++i)
        {
            cin >> ss[i];
            if (ss[i] > s_max)
                s_max = ss[i];
        }
        
        // Read weights.
        int w_max = 0;
        vector<int> ws(m);
        for (int i = 0; i < m; ++i)
        {
            cin >> ws[i];
            if (ws[i] > w_max)
                w_max = ws[i];
        }
        
        // Check whether a solution exists.
        if (s_max < w_max)
        {
            cout << "impossible" << endl;
            continue;
        }
        
        // Sort strengths and weights.
        sort(ss.begin(), ss.end(), greater<int>());
        sort(ws.begin(), ws.end(), greater<int>());
        
        // Greedy simulation.
        int r = 0, s = m;
        vector<bool> bs(m, true);
        while (s > 0)
        {
            int i = 0, j = 0;
            while (i < n && j < m)
            {
                if (bs[j] && ws[j] <= ss[i])
                    bs[j] = false, --s, ++i;
                ++j;
            }
            ++r;
        }
        
        cout << 3 * r - 1 << endl;
    }
    
    return 0;
}

/*

Hi

I found an alternative solution to the problem "Moving Books" of week two and I though it might be of interest.
The code is attached. My algorithm essentially reduces the problem to another problem, here an example to explain how:

Assume there are n=4 friends with strengths 
5 2 2 4
and m=13 boxes with weights
2 4 3 1 1 2 3 2 5 4 2 1 5.

First I sort both lists: O(max{n,m}log max{n,m}}.

Then the idea is to group boxes and assign each group to the last friend who can hold them.
In the above example, the friend with strength 5 will hold boxes with weights 4 and 5, friend with strength 3 holds boxes with weight 3, and the two friends with strength 2 hold boxes with weights 1 and 2.
Schematically:

 1
 1
 1
 2   3
 2   3
 2   4   5
 2   4   5
-----------
2x2 3x1 5x1

Then I noticed that after this step, one does not need to care about strengths and weights.
The scheme above can be rewritten as

7 4 2
-----
2 1 1

which means that there are 7 objects that in a round 2 people can move, 2 objects that in a round one person can move, and 4 obhects that in a round one person can move.
This datastructure can be created in time O(m+n)=O(N).

The important thing to notice is that if a group of people has no more objects left to move, it can help the group on its left.
Then it remains to solve this new problem, that is, to find in how many rounds we can subtract the numbers below from the numbers above to get all zeros above, keeping in mind that we must move the people from right to left whenever possible, that is, if the number above becomes a 0, the resp. number below must be added the the one on its left (and replaced with 0).
In this example the algorithm proceeds as follows:

7 4 2       5 3 1       3 2 0       1 0 0       0 0 0
-----  ==>  -----  ==>  -----  ==>  -----  ==>  -----
2 1 1       2 1 1       2 2 0       2 2 0       4 0 0

therefore we 4 rounds ==> 3*4-1 = 11.
This new problem (I think) can be solved in the worst case in time O(W*n), where W is the max weight, so it actually does not seem better than the proposed solution.
In fact, it is easy to generate a worst case instance:

echo 1 $n $n $(seq $n) $(for i in $(seq $n); do print $n; done)

(that is, all friends have different strengths, and all the boxes have weight equal to the strength of the strongest friend.)

Nevertheless, I got CORRECT on the judge with this algorithm, and it even seems faster for the testcases than the proposed solution.
Finally, I am not sure, but I think the reduced problem might be solved a bit faster, by ignoring the groups of friends with no boxes and who cannot help anyone.

Best,
Fabio

*/
