#include "header.hpp"

class Solution
{
public:
    int rob(vector<int>& nums)
    {
        if (nums.size()=1)
        {
            return nums[0];
        }
        if (nums.size()==2) 
        {
            return max(nums[0], nums[1]);
            /* code */
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