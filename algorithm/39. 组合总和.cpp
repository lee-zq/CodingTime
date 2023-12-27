#include "header.hpp"

class Solution
{
public:
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