class Solution {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n =isConnected.size();
        queue<int> q;
        vector<int> visited(n,false);
        int curr=0;
        int count=0;
        for(int i=0;i<n;i++){
            if(!visited[i]){
                count++;
            visited[i]=true;
            q.push(i);
            while(!q.empty()){
                curr=q.front();
                q.pop();

                for(int x=0;x<n;x++){
                    if(isConnected[curr][x]==1 && !visited[x]){
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