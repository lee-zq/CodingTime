#include "header.hpp"


class Solution
{
public:
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

    // 求最大面积
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

    // 求周长
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

    void default_dfs(vector<vector<char>>& grid, int r, int c)
    {
        // 地图越界
        if (!inArea(grid, r, c))
        {
            return;
        }
        // 已访问or是海洋
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
        grid[r][c] = '2';
        return 1 + area(grid, r - 1, c) + area(grid, r + 1, c) + area(grid, r, c - 1) + area(grid, r, c + 1);
    }

    // 求周长
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