//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;

// } Driver Code Ends
class Solution {
  public:
    // Function to detect cycle in an undirected graph.
    bool dfscycle(int s,int V,const vector<int> adj[], vector<bool>& visited, vector<int>& dfs,int p){
           
    
        visited[s]=true;
            
            for(int x:adj[s]){
                
                if(!visited[x]){
                  if(dfscycle(x,V,adj,visited,dfs,s))
                     return 1;
                
                 }
                 else if(x!=p)
                   return 1;
            }
        return 0;
        
    }
        
    bool isCycle(int V, vector<int> adj[]) {
        // Code here
        vector<bool> visited(V,false);
        vector<int> dfs;
        bool a;
       
        for(int i=0;i<V;i++){
            if(!visited[i]){
             a=dfscycle(i,V,adj,visited,dfs,-1);
             if(a)
              return 1;
        }
        }
        return 0;
        
    }
};

//{ Driver Code Starts.
int main() {
    int tc;
    cin >> tc;
    while (tc--) {
        int V, E;
        cin >> V >> E;
        vector<int> adj[V];
        for (int i = 0; i < E; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        Solution obj;
        bool ans = obj.isCycle(V, adj);
        if (ans)
            cout << "1\n";
        else
            cout << "0\n";
    }
    return 0;
}
// } 