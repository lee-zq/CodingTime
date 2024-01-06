#include "header.hpp"

class Solution
{
public:
/*
解析：这个问题也是个典型的dp问题，子序列是不连续的
构建dp表，dp[i]表示以nums[i]结尾的最长递增子序列的长度。
那么 dp[i] = max[dp[j] for j in range(0,i-1)] + 1
同步更新dp表的最大值，得到结果
*/
    int lengthOfLIS(vector<int>& nums)
    {
        std::vector<int> dp(nums.size(), 1);
        int ans_max = dp[0];
        for (size_t i = 1; i < nums.size(); i++)
        {
            for (size_t j = 0; j < i; j++)
            {
                if (nums[j] < nums[i])
                {
                    dp[i] = std::max(dp[i], dp[j] + 1);
                }
            }
            ans_max = std::max(ans_max, dp[i]);
        }

        return ans_max;
    }
};

int main()
{
    std::vector<int> a = {0, 1, 0, 3, 2, 3};
    Solution s;
    int ret = s.lengthOfLIS(a);
    std::cout << ret << std::endl;
}