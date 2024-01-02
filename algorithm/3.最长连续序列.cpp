#include "header.hpp"
/*
题目描述：在随机数组中找到一个连续递增(前后项之差为1)的序列，返回最大长度
*/

class Solution {
public:
/*
解析：先将数组排序，再遍历数组：遍历时分三种情况：
1.当前值比前一个值大1：+1；2.当前值==前一个值：+0；3.其他情况：累计值重置为1；
*/
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