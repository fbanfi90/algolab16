#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <stack>

using namespace std;

int main()
{
    int t;
    cin >> t;
    
    while (t--)
    {
        int n, q;
        cin >> n >> q;
        
        // Read species and ages.
        unordered_map<string, int> idx;
        vector<string> species(n);
        vector<int> ages(n);
        for (int i = 0; i < n; ++i)
        {
            cin >> species[i] >> ages[i];
            idx[species[i]] = i;
        }
        
        // Read offsprings and build graph.
        int root = max_element(ages.begin(), ages.end()) - ages.begin();
        vector<vector<int>> adj(n);
        for (int i = 0; i < n - 1; ++i)
        {
            string s, p;
            cin >> s >> p;
            adj[idx[p]].push_back(idx[s]);
        }
        
        // Read queries.
        vector<vector<pair<int, int>>> queries(n);
        for (int i = 0; i < q; ++i)
        {
            string s;
            int b;
            cin >> s >> b;
            queries[idx[s]].push_back(make_pair(b, i));
        }
        
        // Perform modified DFS iteratively on tree.
        vector<int> path;
        vector<int> result(q);
        vector<bool> pushed(n);
        stack<int> s;
        s.push(root);
        pushed[root] = 1;
        while (!s.empty())
        {
            int v = s.top();
            s.pop();
            path.push_back(v);
            
            // Perform binary search on children.
            for (auto& query : queries[v])
            {
                int l = 0, r = path.size() - 1;
    
                while (l != r)
                {
                    int m = (l + r) / 2;
                    if (ages[path[m]] > query.first) l = m + 1;
                    else r = m;
                }
                
                result[query.second] = path[l];
            }
            
            for (int u : adj[v])
                if (!pushed[u])
                    s.push(u), pushed[u] = true;
            
            if (adj[v].size() == 0)
                path.pop_back();
        }
        
        for (int i = 0; i < q; ++i)
            cout << species[result[i]] << " ";
        cout << endl;
    }
    
    return 0;
}

void dfs(int v, vector<vector<int>>& adj, vector<int>& path, vector<vector<pair<int,int>>>& queries, vector<int>& result, vector<int>& ages)
{
    // Perform binary search on children.
    for (auto& query : queries[v])
    {
        int l = 0, r = path.size() - 1;
        
        while (l != r)
        {
            int m = (l + r) / 2;
            if (ages[path[m]] > query.first) l = m + 1;
            else r = m;
        }
    
        result[query.second] = path[l];
    }
    
    for (int u : adj[v])
    {
        path.push_back(u);
        dfs(u, adj, path, queries, result, ages);
    }
    
    path.pop_back();
}

int main_rec()
{
    int t;
    cin >> t;
    
    while (t--)
    {
        int n, q;
        cin >> n >> q;
        
        // Read species and ages.
        unordered_map<string, int> idx;
        vector<string> species(n);
        vector<int> ages(n);
        for (int i = 0; i < n; ++i)
        {
            cin >> species[i] >> ages[i];
            idx[species[i]] = i;
        }
        
        // Read offsprings and build graph.
        int root = max_element(ages.begin(), ages.end()) - ages.begin();
        vector<vector<int>> adj(n);
        for (int i = 0; i < n - 1; ++i)
        {
            string s, p;
            cin >> s >> p;
            adj[idx[p]].push_back(idx[s]);
        }
        
        // Read queries.
        vector<vector<pair<int, int>>> queries(n);
        for (int i = 0; i < q; ++i)
        {
            string s;
            int b;
            cin >> s >> b;
            queries[idx[s]].push_back(make_pair(b, i));
        }
        
        // Perform modified DFS recursively on tree.
        vector<int> path;
        path.push_back(root);
        vector<int> result(q);
        dfs(root, adj, path, queries, result, ages);
        
        for (int i = 0; i < q; ++i)
            cout << species[result[i]] << " ";
        cout << endl;
    }
    
    return 0;
}

int main_naive()
{
    int t;
    cin >> t;
    
    while (t--)
    {
        int n, q;
        cin >> n >> q;
        
        // Read species and ages.
        unordered_map<string, int> age;
        for (int i = 0; i < n; ++i)
        {
            string s;
            int a;
            cin >> s >> a;
            age[s] = a;
        }
        
        // Read offsprings.
        unordered_map<string, string> pred;
        for (int i = 0; i < n - 1; ++i)
        {
            string s, p;
            cin >> s >> p;
            pred[s] = p;
        }
        
        // Process queries.
        for (int i = 0; i < q; ++i)
        {
            string s;
            int b;
            cin >> s >> b;
            
            int a;
            string q = s;
            do
            {
                s = q;
                q = pred[s];
                a = age[q];
                if (!q.compare(""))
                    break;
            }
            while (a <= b);
            
            cout << s << " ";
        }
        cout << endl;
    }
    
    return 0;
}
