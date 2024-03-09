#include "header.hpp"
class Solution
{
public:
/*
解析：注意太偏门的问题不要死磕，比如这个问题可以跳过，直到大概思路即可。多准备简历项目。
思路：先找到所有新鲜橘子的个数，所有腐烂橘子的坐标存入队列，每次弹出一个腐烂橘子并对附近四个地址内新鲜橘子坐标腐蚀，
每腐蚀一个则新鲜橘子-1，腐蚀后的坐标push到队列中，坐标值改为2防止重复走，
最后查看新鲜橘子的个数
*/
    int dir[4][2] = {-1, 0, 0, 1, 1, 0, 0, -1};
    int orangesRotting(vector<vector<int>>& grid)
    {
        // 记录坏橘子的位置和新鲜橘子的个数
        int m = grid.size();
        int n = grid[0].size();
        int ret = -1;
        int countNew = 0;
        queue<pair<int, int>> q;
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (grid[i][j] == 2)
                {
                    q.push({i, j});
                }
                else if (grid[i][j] == 1)
                    ++countNew;
            }
        }
        // 边界判断：没有坏橘子的情况
        if (q.empty())
            return countNew ? -1 : 0;

        // bfs腐蚀过程
        while (!q.empty())
        {
            ++s;
            int size = q.size();
            while (size--)
            {
                auto frontPair = q.front();
                q.pop();
                int row = frontPair.first, col = frontPair.second;
                for (int k = 0; k < 4; ++k)
                {
                    int curx = row + dir[k][0], cury = col + dir[k][1];
                    if (curx < 0 || curx >= m || cury < 0 || cury >= n)
                        continue;
                    if (grid[curx][cury] == 1)
                    {
                        grid[curx][cury] = 2;
                        q.push({curx, cury});
                        --countNew;
                    }
                }
            }
        }

        return countNew ? -1 : ret;
    }
};