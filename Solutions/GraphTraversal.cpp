//A Simple code to traverse graphs by using bfs and dfs. We are given a graph
//with 1 based indexing with given which vertex has edge to which one. We will
//first store the graph, than print that adjacency list, and lastly print both
//bfs and dfs traversal. For simplicity we keep the graph as undirected only
//but same methods can easily be applied on a directed or weighted graphs.

#include <bits/stdc++.h>
using namespace std;

void bfsh(int n, vector<int> &vis, const vector<vector<int>> &adj, vector<int> &ans)
{
    queue<int> q;
    q.push(n);
    vis[n] = 1;
    while(!q.empty())
    {
        int x = q.front();
        q.pop();
        ans.push_back(x);
        
        for(auto i : adj[x])
        {
            if(!vis[i])
            {
                vis[i] = 1;
                q.push(i);
            }
        }
    }
}

void dfsh(int n, vector<int> &vis, const vector<vector<int>> &adj, vector<int> &ans)
{
    vis[n] = 1;
    ans.push_back(n);
    for(auto i : adj[n])
    {
        if(!vis[i]) dfsh(i, vis, adj, ans);
    }
}

vector<int> BFSonGraph(int n, const vector<vector<int>> &adj)
{
    vector<int> ans;
    vector<int> vis(n+1, 0);
    for(int i=1; i<=n; i++)
    {
        if(!vis[i])
        {
            bfsh(i, vis, adj, ans);
        }
    }

    return ans;
}

vector<int> DFSonGraph(int n, const vector<vector<int>> &adj)
{
    
    vector<int> ans;
    vector<int> vis(n+1, 0);
    for(int i=1; i<=n; i++)
    {
        if(!vis[i])
        {
            dfsh(i, vis, adj, ans);
        }
    }

    return ans;
}

int main()
{
    int n; cout<<"Enter the number of vertices: ";cin>>n;
    
    vector<vector<int>> adj(n+1);
    
    int m; cout<<"Enter the number of edges: "; cin>>m;
    
    cout<<"Enter all the edge pairs: \n";
    for(int i=0; i<m; i++)
    {
        int a, b; cin>>a>>b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    //Adjacency list
    for(int i=1; i<=n; i++)
    {
        cout<<i<<": { ";
        for(const auto &x : adj[i])
        {
            cout<<x<<' ';
        }
        cout<<"}\n";
    }

    vector<int> bfsSol = BFSonGraph(n, adj);
    vector<int> dfsSol = DFSonGraph(n, adj);

    cout<<"BFS Traversal: {";
    for(const auto &i : bfsSol) cout<<i<<' ';
    cout<<"}\n";

    cout<<"DFS Traversal: {";
    for(const auto &i : dfsSol) cout<<i<<' ';
    cout<<"}\n";
}