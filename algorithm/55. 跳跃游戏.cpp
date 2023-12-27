#include "header.hpp"

class Solution
{
public:
    bool canJump(vector<int>& nums)
    {
        int n = nums.size();
        int max_access_idx = 0;
        for (size_t i = 0; i < n; i++)
        {
            if (i <= max_access_idx) // 判断i位置是否可以到达
            {
                // 可以到达的话，就基于当前位置的nums[i]值更新可到达的最远位置
                max_access_idx = std::max(max_access_idx, i + nums[i]);
                if (max_access_idx >= n - 1) // 可到达的最远位置大于等于最后一个元素索引则可达
                {
                    return true;
                }
            }
        }
        return false; // 不可达
    }
};