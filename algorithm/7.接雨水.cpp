#include "header.hpp"
/*

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

