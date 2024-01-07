#include "header.hpp"

class Solution {
public:
/*
解析：要求将所有0移动到末尾，双指针遍历，在遍历指针i遇到值不为0的元素时，将其值赋给遍历指针j所在位置，j++。i++
遍历完之后将指针j之后的位置都复位0；
*/
    void moveZeroes(vector<int>& nums) {
        int i = 0;
        int j = 0;
        while(i<nums.size()){
            if (nums[i]!=0){
                nums[j] = nums[i];
                j++;
            }
            i++;
        }

        while (j<nums.size()){
            nums[j++] = 0;
        }
    }
};

int main(){
    Solution s;
    std::vector<int> src = {0,1,0,3,12,0,11,22};
    auto f = [](int& _, int& b) { return !b; };
    std::sort(src.begin(), src.end(), f);
    
    // s.moveZeroes(src);
    for (auto i:src){
        std::cout << i << " ";
    }
    std::cout << std::endl;
    return 0;
}