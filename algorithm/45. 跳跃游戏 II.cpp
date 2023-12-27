#include "header.hpp"
#include <algorithm>
class Solution
{
public:
    int jump(vector<int>& nums)
    {
        int board = 0;   // 当前能跳跃到的边界下标
        int max_pos = 0; // 下次跳跃能到达的最远距离
        int step = 0;    // 跳跃次数
        for (size_t i = 0; i < nums.size() - 1; i++)
        {
            max_pos = std::max(max_pos, nums[i] + i);
            if (i == board)
            {
                board = max_pos;
                step++;
            }
        }
        return step;
    }
};