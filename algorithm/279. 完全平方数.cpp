#include "header.hpp"

class Solution
{
public:
/*
题意：目标整数最少可以由几个整数的平方和组成
解析：构造dp表，dp[i]表示组成i所需的最小数量。很明显dp[0]=0, dp[1]=1, dp[2]=2, dp[3]=3 ,dp[4]=1 dp[5]=2
dp[5]的求解不是去暴力穷举，而是找一个平方数最大但不大于5的数字j，然后用dp[5-j*j]+1作为结果，即dp[5-2*2]+1
容易归纳出递推公式： dp[i] = min[dp[i-j*j]+1 for j in range(1, j*j<=i)]
*/
    int numSquares(int n)
    {
        vector<int> dp_list(n + 1);
        dp_list[0] = 0;

        for (size_t i = 0; i < n+1; i++)
        {
            int min_value = INT32_MAX;
            for (size_t j = 1; j * j <= i; j++)
            {
                min_value = std::min(min_value, dp_list[i - j * j]);
            }
            dp_list[i] = min_value + 1;
        }
        return dp_list[n];
    }
};