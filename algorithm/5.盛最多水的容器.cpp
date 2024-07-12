#include "header.hpp"

class Solution {
public:
/*
解析：直接双层遍历是最直观的方式，考虑所有组合，比大小得到答案。
但是复杂度过高，这种问题考虑如何将遍历过程剪枝，这是搜索遍历问题最基本的优化方式。

使用双指针分别从左边l和右边r相向而行，每次记录当前面积。因为遍历过程中，
当前面积由较低的竖线决定，所以移动较高的竖线并不会增加高度，反而会减少宽度，不值得尝试，
所以每次只移动高度较低的那个位置，结束条件是左指针小于右指针
*/
    int maxArea_v0(vector<int>& height) {// 暴力双层遍历，超时
        int max_area = 0;
        for (int i = 0; i < height.size();i++){
            for (int j = i + 1; j < height.size();j++){
                int cur_area = min(height[i], height[j]) * (j - i);
                if (cur_area > max_area)
                {
                    max_area = cur_area;
                }
            }
        }
        return max_area;
    }

    int maxArea(vector<int>& height) {// 双指针相向搜索
        int max_area = 0;
        int l = 0;
        int r = height.size() - 1;
        while (l<r){
            int area = std::min(height[l], height[r]) * (r -l);
            if (max_area < area){
                max_area = area;
            }
            if (height[l] < height[r]){
                l++;
            }else{
                r--;
            }
        }
        return max_area;
    }
}; 

int main(){
    Solution s;
    std::vector<int> src = {1,8,6,2,5,4,8,3,7};
    std::cout << s.maxArea(src) << std::endl;
    return 0;
}

