#include "header.hpp"


/*
题目：二维数组中1为岛屿，0为海洋。求岛屿数量等问题
*/

class Solution
{
public:
    /* 1
    解析：从某一个是陆地的地方开始遍历并标记这块陆地为已访问(2)，然后岛屿数量+1,
    然后再遍历其他位置，每找到一个是1的点，就基于这个点扩散标记，直到遍历完。得到岛屿总数
    */
    int numIslands(vector<vector<char>>& grid)
    {
        int ret = 0;
        for (int r = 0; r < grid.size(); r++)
        {
            for (int c = 0; c < grid[0].size(); c++)
            {
                if (grid[r][c] == '1')
                {
                    default_dfs(grid, r, c);
                    ret++;
                }
            }
        }
        return ret;
    }
    // 从一个点出发标记这个点所在陆地坐标都为2.
    // 越界或访问到海洋或已访问地点则直接返回，或者标记该点并访问点四周的位置。
    void default_dfs(vector<vector<char>>& grid, int r, int c)
    {
        // 岛屿越界
        if (!inArea(grid, r, c))
        {
            return;
        }
        // 已访问2 or 是海洋0
        if (grid[r][c] != '1')
        {
            return;
        }
        // 操作当前陆地

        // 标记为已访问
        grid[r][c] = '2';
        default_dfs(grid, r - 1, c);
        default_dfs(grid, r + 1, c);
        default_dfs(grid, r, c - 1);
        default_dfs(grid, r, c + 1);
    }

    // =================================================================================
    // 2. 求最大岛屿面积。假设有很多岛屿。
    int maxAreaOfIsland(vector<vector<char>>& grid)
    {
        int ret = 0;
        for (int r = 0; r < grid.size(); r++)
        {
            for (int c = 0; c < grid[0].size(); c++)
            {
                if (grid[r][c] == '1')
                {
                    int cur_area = area(grid, r, c);
                    ret = std::max(ret, cur_area);
                }
            }
        }
        return ret;
    }
    // 求当前点所在岛屿的面积，并标记已访问的点为2
    int area(vector<vector<char>>& grid, int r, int c)
    {
        // 地图越界
        if (!inArea(grid, r, c))
        {
            return 0;
        }
        // 已访问or是海洋
        if (grid[r][c] != '1')
        {
            return 0;
        }
        // 每次执行到这里标记一个地点，则面积+1
        grid[r][c] = '2';
        return 1 + area(grid, r - 1, c) + area(grid, r + 1, c) + area(grid, r, c - 1) + area(grid, r, c + 1);
    }

    // ===============================================================================
    // 求周长。假设只有一个岛屿。找到一个非0点，开始遍历这个点所在岛屿，得到周长。
    int islandPerimeter(vector<vector<char>>& grid)
    {
        int ret = 0;
        for (int r = 0; r < grid.size(); r++)
        {
            for (int c = 0; c < grid[0].size(); c++)
            {
                if (grid[r][c] == '1')
                {
                    int cur_area = dfs_Perimeter(grid, r, c);
                    return cur_area;
                }
            }
        }
        return ret;
    }
    // 求周长。扩散遍历过程中，遇到越界或海洋则是属于边界了，可以收获一个单位的边长，
    // 所有可求的的边之和为周长
    int dfs_Perimeter(vector<vector<char>>& grid, int r, int c)
    {
        // 地图越界
        if (!inArea(grid, r, c))
        {
            return 1;
        }
        // 是海洋
        if (grid[r][c] == '0')
        {
            return 1;
        }
        // 已访问
        if (grid[r][c] != '1')
        {
            return 0;
        }

        // 标记为已访问
        grid[r][c] = '2';
        return dfs_Perimeter(grid, r - 1, c) + dfs_Perimeter(grid, r + 1, c) + dfs_Perimeter(grid, r, c - 1) +
               dfs_Perimeter(grid, r, c + 1);
    }

    // 判断坐标是否在矩阵范围内
    bool inArea(vector<vector<char>>& grid, int r, int c)
    {
        int rows = grid.size();
        if (rows == 0)
        {
            return false;
        }
        int cols = grid[0].size();
        return r >= 0 & r < rows & c >= 0 && c < cols;
    }
};