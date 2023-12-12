#include "header.hpp"

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        if (nums.size()==0)
            return 0;
        else{
            std::sort(nums.begin(), nums.end());
            int max_len = 1;
            int cur_len = 1;
            for (int i=1;i<nums.size();i++){
                if (nums[i]-nums[i-1]==1){
                    cur_len++;
                    max_len = max_len<cur_len?cur_len:max_len;
                }else if(nums[i]==nums[i-1]){
                    continue;
                }else{
                    cur_len=1;
                }
            }
            return max_len;
        }
    }
};

int main(){
    Solution s;
    std::vector<int> src = {100, 4, 200, 1, 3, 2};
    std::cout << s.longestConsecutive(src) << std::endl;
    return 0;
}