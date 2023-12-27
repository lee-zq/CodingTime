#include "header.hpp"

class Solution
{
public:
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