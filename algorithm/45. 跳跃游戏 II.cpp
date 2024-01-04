#include "header.hpp"
#include <algorithm>
class Solution
{
public:
/*
解析：这个问题比较抽象。考虑如果能跳到board位置，那么一定可以跳到[0,board]的任何位置，
累计[0,board]能到达的最远位置，可以作为下一次跳跃的目标位置，这里记为max_pos
在遍历过程中，记录max_pose，z在遍历到达board时，step++,当前可到达最远位置更新为max_pos
*/
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