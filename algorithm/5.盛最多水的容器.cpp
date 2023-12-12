#include "header.hpp"

class Solution {
public:
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

