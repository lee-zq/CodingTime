#include "header.hpp"

class Solution {
public:
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
    s.moveZeroes(src);
    for (auto i:src){
        std::cout << i << " ";
    }
    std::cout << std::endl;
    return 0;
}