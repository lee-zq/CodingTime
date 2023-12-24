#include "header.hpp"
class Solution
{
public:
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
            ++ret;
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