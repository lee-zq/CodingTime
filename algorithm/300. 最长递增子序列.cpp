#include "header.hpp"

class Solution
{
public:
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