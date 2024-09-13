class Solution {
public:
    int maxProduct(vector<int>& nums) {
        __int128 n=nums.size(),maxsub=nums[0],l=0,r=0;
        for(int i=0;i<n;i++){
            l=(l?l:1)*nums[i];
            r=(r?r:1)*nums[n-1-i];
            maxsub=max(maxsub,max(l,r));
        }
        return maxsub;
    }      
};