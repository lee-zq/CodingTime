#include "header.hpp"

class Solution
{
public:
/*
解析：一维区间数组合并问题。将数组先按照左边界升序排序。
然后每次取出一个区间it和已存入的区间最后一个back对比，
如果it的左边界大于back的右边界，则插入it到back后面。
如果it右边界小于已存入back的右边界，无需更新，如果大于back的右边界，则更新back的右边界为it的右边界
*/
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