#include "header.hpp"   

class Solution
{
public:
    /*
题意：典型的背包问题，不限物品数量
构建dp表，dp[i]表示凑足i元所需的最小硬币数量；
那么可以总结处递推式： dp[i] = min([dp[i-c] for c in coins]+1
同时要保证i-coins[j] >= 0
*/
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