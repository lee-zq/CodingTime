#include "header.hpp"

class Solution
{
public:
/*
解析：基本思路是找到一个卖出时机前的最小值位置作为买入时间，然后求所有卖出时间的收益最大值
这是一个典型dp问题，以每个时间节点作为卖出时间求和此前最小值的差作为dp表元素
*/
    int maxProfit(vector<int>& prices)
    {
        int min_value = prices[0];
        int ans = 0;
        for (size_t i = 1; i < prices.size(); i++)
        {
            ans = std::max(ans, prices[i] - min_value);
            min_value = std::min(min_value, prices[i]);
        }
        return ans;
    }
};