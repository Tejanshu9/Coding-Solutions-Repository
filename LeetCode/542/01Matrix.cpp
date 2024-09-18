class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
       vector<pair<int,int>> dir={{0,1},{0,-1},{1,0},{-1,0}};
       int m=mat.size();
       int n=mat[0].size();
       queue<pair<int,int>> q;
       for(int r=0;r<m;r++){
         for(int c=0;c<n;c++){
            if(mat[r][c]==0)
               q.emplace(r,c);
            else
               mat[r][c]=-1;
         }
       }
       while(!q.empty()){
        auto [r,c]=q.front();
        q.pop();
         for( auto [dr,dc]:dir){
            int nr=r+dr;
            int nc=c+dc;
            if(nr<0 || nc<0 || nr>=m || nc>=n || mat[nr][nc]!=-1)
               continue;
            mat[nr][nc]=mat[r][c]+1;
            q.emplace(nr,nc);

         }
        
       }
       return mat;
    }
    

};