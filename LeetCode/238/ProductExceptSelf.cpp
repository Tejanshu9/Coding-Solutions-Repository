class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> answer(static_cast<std::size_t>(nums.size()));
        std::fill(answer.begin(),answer.end(),1);
        int curr=1;
        for(int i=0;i<nums.size();i++){
            answer[i]*=curr;
            curr*=nums[i];
        }
        curr=1;
        for(int i=(nums.size()-1);i>=0;i--){
            answer[i]*=curr;
            curr*=nums[i];
        }
        return answer;
    }
};