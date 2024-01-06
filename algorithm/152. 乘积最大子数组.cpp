#include "header.hpp"

class Solution {
public:
    /*
解析：最大积问题要考虑到负负得正，所以在求最大乘积子数组时，分别建立最大值dp表dp_max[]
和最小值dp表dp_min[],然后在更新dp表的时候：
dp_max[i] = max(max(nums[i]*dp_max[i-1], nums[i]*dp_min[i-1]),nums[i])
dp_min[i] = min(min(nums[i]*dp_max[i-1], nums[i]*dp_min[i-1]),nums[i])

分别表示以nums[i]结尾的最大子数组积和最小子数组积
然后更新answer， answer = max(answer, dp_max[i])
*/
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