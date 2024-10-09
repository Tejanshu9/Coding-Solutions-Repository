bool comp(vector<int> &a,vector<int> &b){
    return a[1]<b[1];
}
class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        sort(intervals.begin(),intervals.end(),comp);
        if(intervals.size()<=1) return 0;

        int prev=0;
        int eraseCount=0;

        for(int i=1;i<intervals.size();i++){
            if(intervals[prev][1]>intervals[i][0])
                           ++eraseCount;
            else
                prev=i;
        }
        return eraseCount;
    }
};