#include "header.hpp"   

class Solution
{
public:
    int coinChange(vector<int>& coins, int amount)
    {
        vector<int> dp(amount + 1, amount + 1);
        dp[0] = 0;
        for (int i = 1; i < amount + 1; i++)
        {
            for (auto& c : coins)
            {
                if (c <= i)
                {
                    dp[i] = std::min(dp[i - c] + 1, dp[i]);
                }
            }
        }
        return dp[i] > amount ? -1 : dp[i];
    }
};