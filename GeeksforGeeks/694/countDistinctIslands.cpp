//{ Driver Code Starts
// Initial Template for C++
#include <bits/stdc++.h>
using namespace std;


// } Driver Code Ends
// User function Template for C++

class Solution {
  public:
    void dfs(vector<vector<int>>& grid,int i,int j,int baserow,int basecol,vector<pair<int,int>>& shape){
        
        int m=grid.size();
        int n=grid[0].size();
        if(i<0 or j<0 or i>=m or j>=n or grid[i][j]!=1) return;
        
        grid[i][j]=0;
        shape.push_back({i-baserow,j-basecol});
        
        dfs(grid,i+1,j,baserow,basecol,shape);
        dfs(grid,i-1,j,baserow,basecol,shape);
        dfs(grid,i,j+1,baserow,basecol,shape);
        dfs(grid,i,j-1,baserow,basecol,shape);
    }
    
    int countDistinctIslands(vector<vector<int>>& grid) {
        // code here
        int m=grid.size();
        if(m==0)
          return 0;
        int n=grid[0].size();
        set<vector<pair<int,int>>> distinctIslands;
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(grid[i][j]==1){
                    vector<pair<int,int>> shape;
                    dfs(grid,i,j,i,j,shape);
                    distinctIslands.insert(shape);
                }
            }
        }
        return distinctIslands.size();
    }
};


//{ Driver Code Starts.

int main() {

    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> grid(n, vector<int>(m));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> grid[i][j];
            }
        }
        Solution obj;
        cout << obj.countDistinctIslands(grid) << endl;
    }
}
// } Driver Code Ends