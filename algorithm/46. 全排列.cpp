#include "header.hpp"

class Solution
{
public:
/*
解析：典型回溯问题。全排列。构造辅助递归函数backtrack,用selected表示nums中已选择和未选择的数据状态
在state长度和nums长度相等时，表示所有数据都已被选择了一遍，保存一个结果。
*/
    vector<vector<int>> permute(vector<int>& nums)
    {
        vector<int> state;
        vector<bool> selected(nums.size(), false);
        std::vector<vector<int>> result;
        backtrack(state, nums, selected, result);
        return result;
    }

    void backtrack(vector<int>& state, vector<int>& nums, vector<bool>& selected, std::vector<vector<int>>& result)
    {
        if (state.size() == nums.size()){
            result.push_back(state);
            return;
        }
        
        for (int i = 0; i < selected.size(); i++)
        {
            if (selected[i]==false){
                state.push_back(nums[i]);
                selected[i] = true;
                backtrack(state, nums, selected, result);
                selected[i] = false;
                state.pop_back();
            }
        }
    }
};