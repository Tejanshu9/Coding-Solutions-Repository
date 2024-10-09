class Solution {
public:
    
       bool bfs(int source,int size,const vector<vector<int>>& graph,vector<int> &visited,vector<int> &side){
        queue<int> q;
        visited[source]=true;
        q.push(source);
        side[source]=0;
        while(!q.empty()){
            int curr=q.front();
            q.pop();
            
            for(auto x:graph[curr]){
                if(!visited[x]){
                    visited[x]=true;
                    if(side[curr]==0){
                     side[x]=1;
                    }
                    else{
                      side[x]=0;
                      }
                q.push(x);
                }
                else{
                 if(side[x]==side[curr])
                   return false;}
            }
           
        }
        return true;
    }

    bool isBipartite(vector<vector<int>>& graph){
       int n=graph.size();
       vector<int> visited(n,false);
       
       vector<int> side(n,-1);
       for(int i=0;i<n;i++){
        if(!visited[i]){
       bool a=bfs(i,n,graph,visited,side); 
       if(!a)
        return false;
        }
    } 
    return true;
    } 
};