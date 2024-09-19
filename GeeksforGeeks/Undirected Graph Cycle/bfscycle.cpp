/ } Driver Code Ends
class Solution {
  public:
    // Function to detect cycle in an undirected graph.
    bool bfscycle(int s,int V,const vector<int> adj[], vector<bool>& visited){
           queue<int> q;
               q.push(s);
        
        while(!q.empty()){
            int curr=q.front();
             q.pop();
            
            if(visited[curr]){
                    return 1;
                }
                visited[curr]=true;
            
            for(int x:adj[curr]){
                
                if(!visited[x])
                    q.push(x);
            }
        }
        return 0;
        
    }
        
    bool isCycle(int V, vector<int> adj[]) {
        // Code here
        vector<bool> visited(V,false);
        bool a;
       
        for(int i=0;i<V;i++){
            if(!visited[i]){
             a=bfscycle(i,V,adj,visited,bfs);
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
