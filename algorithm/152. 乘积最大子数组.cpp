#include "header.hpp"

class Solution {
public:
    int maxProduct(vector<int>& nums) {
        vector<int> max_dp(nums.size());
        vector<int> min_dp(nums.size());
        max_dp[0] = nums[0];
        min_dp[0] = nums[0];
        int ans = max_dp[0];
        for (size_t i = 1; i < nums.size(); i++)
        {
            max_dp[i] = std::max(std::max(nums[i] * max_dp[i - 1], nums[i] * min_dp[i - 1]), nums[i]);
            min_dp[i] = std::min(std::min(nums[i] * min_dp[i - 1], nums[i] * max_dp[i - 1]), nums[i]);
            ans = std::max(ans, max_dp[i]);
        }
        return ans;
    }
};