class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int lenNum=nums.size();
        int i=0;
        int j=0;
        vector<int>  result;
        if(lenNum>0){
        while(i<lenNum){ 
            j=i+1;
         while(j<=lenNum-1){
            if (i<j){
            if(nums[i]+nums[j]==target){
               result={i,j};
               return result;}}
               j++;
        
        }
        i++;
        }
        
        }
        return {};
    }
};      
    
