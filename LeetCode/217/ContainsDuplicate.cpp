class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        return nums.size() > std:: unordered_set<int>(nums.begin(),nums.end()).size();
        
    }
};