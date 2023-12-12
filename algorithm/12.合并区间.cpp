#include "header.hpp"

class Solution
{
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals)
    {
        if (intervals.size() == 0)
        {
            return {{}};
        }
        std::sort(intervals.begin(), intervals.end(), [](const vector<int>& x, const vector<int>& y) {
            return x.front() < y.front();
        });
        vector<vector<int>> res = {{intervals.front()}};
        for (int i = 1; i < intervals.size(); i++)
        {
            auto& item = intervals[i];
            if (item[0] > res.back()[1])
            {
                res.push_back(item);
            }
            else
            {
                res.back()[1] = std::max(item[1], res.back()[1]);
            }
        }
        return res;
    }
};