#include "header.hpp"

class Solution
{
public:
/*
解析：典型回溯问题。全排列。构造辅助递归函数backtrack,用select表示nums中已选择和未选择的数据状态
在state长度和nums长度相等时，表示所有数据都已被选择了一遍，保存一个结果。
*/
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