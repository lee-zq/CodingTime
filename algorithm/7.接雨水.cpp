#include "header.hpp"
/*
解析：题目要求需要等价转换一下，将每个位置能承接的数量转换为当前位置左边最高高度和右边最高高度中较低高度和当前高度的差值
差值大于0则累计，小于0则无收益。
1.先构建left[n]和rigth[n]两个边界最高数组，起始和终止位置的左边和右边分别为0.
2.累计最大数量；
*/
class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        std::vector<int> left(n, 0);
        std::vector<int> right(n, 0);
        for (int i = 1; i < n; i++)
        {
            left[i] = std::max(height[i - 1], left[i - 1]);
        }
        for (int i = n-2; i >= 0; i--)
        {
            right[i] = std::max(height[i + 1], right[i + 1]);
        }
        int ret = 0;
        for (int i = 0; i < n;i++){
            int h = std::min(left[i], right[i]) - height[i];
            if (h>0)
            {
                ret += h;
            }
        }
        return ret;
    }
};

