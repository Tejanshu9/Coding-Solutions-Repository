class Solution {
public:
  vector<vector<int>>  adjacencyList (int n, vector<vector<int>> edges){
            vector<vector<int>> adja(n);
              for(const auto& edge:edges){
                   adja[edge[0]].push_back(edge[1]);
                   adja[edge[1]].push_back(edge[0]);
                }
                return adja;
  }

    int countComponents(int n, vector<vector<int>>& edges) {
            vector<vector<int>> adja(n);
            adja=adjacencyList (n, edges); 
            queue<int> q;
            vector<bool> visited(n,false);
            
            int count=0;
            for(int i=0;i<n;i++){
              if(!visited[i]){
                count++;
              
              visited[i]=true;
              q.push(i);
            while(!q.empty()){
                int curr=q.front();
                q.pop();
                

                for(int x:adja[curr]){
                    if(!visited[x]){
                        visited[x]=true;
                        q.push(x);
                    }
                }
               
            }
         
        }
     }
      return count;
    }
      
};