int Solution::solve(vector<vector<int>>&A){
  // sort acc to start times
       vector<int> start;
       vector<int> end;
       int rooms=0;
       int max_rooms=0;
       for(auto e:A){
           start.push_back(e[0]);
           end.push_back(e[1]);
       }
       sort(start.begin(),start.end());
       sort(end.begin(),end.end());
       for(int i=0,j=0;i<A.size()&&j<A.size();){
           if(start[i]<end[j]){
               rooms++;
               i++;
           }
           else{
           rooms--;
             j++;}
             max_rooms = max(max_rooms, rooms);
       }
       return max_rooms;
       }
       
