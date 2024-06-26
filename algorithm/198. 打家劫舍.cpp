#include "header.hpp"

class Solution
{
public:
/*
解析：打家劫舍。相邻的元素不能取。构建dp表，每个位置表示当前位置在条件限制下能获取的最大收益
dp[i] = max(dp[i-1], dp[i-2]+nums[i])
*/
    int rob(vector<int>& nums)
    {
        if (nums.size()=1)
        {
            return nums[0];
        }
        
        vector<int> dp(nums.size());
        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);
        for (size_t i = 2; i < nums.size(); i++)
        {
            dp[i] = std::max(dp[i - 1], dp[i - 2] + nums[i]);
        }
        return dp.back();
    }
};