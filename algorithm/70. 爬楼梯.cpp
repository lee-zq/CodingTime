#include "header.hpp"

class Solution
{
public:
    int climbStairs(int n)
    {
        if(n==1){
            return 1;
        }
        vector<int> dp(n);
        dp[0] = 1;
        dp[1] = 2;
        // dp[i] = dp[i-1] + dp[i-2]
        for (size_t i = 2; i < n; i++)
        {
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        return dp[n-1];
    }

    int climbStairsV2(int n)
    {
        if (n<=2)
        {
            return n;
        }
        dp0 = 1;
        dp1 = 2;
        // dp[i] = dp[i-1] + dp[i-2]
        int tmp;
        for (size_t i = 2; i < n; i++)
        {
            tmp = dp0 + dp1;
            dp0 = dp1;
            dp1 = tmp;
        }
        return dp1;
    }
};