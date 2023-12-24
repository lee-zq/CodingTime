#include "header.hpp"

class Solution
{
public:
    vector<vector<int>> permute(vector<int>& nums)
    {
        vector<int> state;
        vector<bool> select(nums.size(), false);
        std::vector<vector<int>> result;
        backtrack(state, nums, select, result);
        return result;
    }

    void backtrack(vector<int>& state, vector<int>& nums, vector<bool>& select, std::vector<vector<int>>& result)
    {
        if (state.size() == nums.size()){
            result.push_back(state);
            return;
        }
        
        for (int i = 0; i < select.size(); i++)
        {
            if (select[i]==false){
                state.push_back(nums[i]);
                select[i] = true;
                backtrack(state, nums, select, result);
                select[i] = false;
                state.pop_back();
            }
        }
    }
};