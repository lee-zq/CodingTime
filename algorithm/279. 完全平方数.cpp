#include "header.hpp"

class Solution
{
public:
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