class Solution {
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
        queue<pair<int,int>> q;
        int originalColor=image[sr][sc];
        if(image[sr][sc] !=color){
           image[sr][sc]=color;
           q.push({sr,sc});
           while(!q.empty()){
              int qsize=q.size();
              for(int j=0;j<qsize;j++){
                 vector<pair<int,int>> dir={{1,0},{-1,0},{0,1},{0,-1}};
                  int row=q.front().first;
                  int col=q.front().second;
                  q.pop();
                  for(auto& [dx,dy]:dir){
                    int i=row+dx;
                    int j=col+dy;
                    if(i>=0 && i<image.size() && j>=0 && j<image[i].size() && image[i][j]==originalColor){
                       image[i][j]=color;
                       q.push({i,j});}

                  }
              }
           }
           return image;
        
    }
    else
     return image;
    }
};