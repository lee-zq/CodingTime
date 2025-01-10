#include "header.hpp"

class Solution
{
public:
/*
解析：回溯问题。关键在于如何实现dfs辅助函数，在dfs递归调用时分解为子问题，设置合适的终止条件。
dfs函数传参需要考虑带入选择项和用于结果保存的容器，终止条件会和递归过程中更新的量相关。
在这个问题中，候选数组中的元素可以重复使用，也可以不全都选择。dfs函数传参中：target表示目前还需要凑足的数值，
idx代表当前可选择的数字在candidates中的索引，status表示目前已选择的数字组合，res表示结果存储的容器
candidates是和idx一起确定选择项。
在选择某一个idx的数字时，有选择和不选择当前数字两种选择，分别递归。
1. 不选择则直接跳过：idx+1且其他参数不变
2. 在目标值比当前值大的时候，考虑选择当前值，则target变为target-candidates[idx],idx++,status添加当前选项
3. 结束递归后需要撤销当前选择
4. 终止条件是idx越界或target刚好衰减到0（表示组合的和刚好是target）
*/
    vector<vector<int>> combinationSum(vector<int>& candidates, int target)
    {
        vector<vector<int>> res;
        vector<int> status;
        dfs(target, 0, status, res, candidates);
        return res;
    }

    void dfs(int target, int idx, vector<int>& status, vector<vector<int>>& res, vector<int>& candidates){
        if (idx==candidates.size()){
            return; // 越界
        }
        if (target==0){ // 符合条件
            res.push_back(status);
            return;
        }
        // 跳过当前选择
        dfs(target, idx + 1, status, res, candidates);

        // 当前选择不大于target时，选择当前值并递归（当前值可以选多次，所以索引还是idx）
        if (target - candidates[idx] >= 0)
        {
            status.push_back(candidates[idx]);
            dfs(target - candidates[idx], idx, status, res, candidates);
            status.pop_back();
        }
    }
};

int main(){
    Solution s;
    vector<int> nums = {2, 3, 4, 7};
    auto ret = s.combinationSum(nums, 7);
    return 0;
}