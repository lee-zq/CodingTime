#include "header.hpp"

/*
题目：寻找数组中3个数的和为0的所有可能情况
*/
class Solution {
public:
    /*
解析：简单粗暴三层循环，但这不能叫算法了；
考虑固定一个值，然后在其他位置寻找和为当前固定值的相反数。
先将数组升序排序，可以将遍历过程进行剪枝。
1. 最外层i遍历所有值，其实只要遍历到值大于0的数后就可以终止了，因为i后面大于0的数不可能和为负数。
2. L = i+1,R=n-1;在L<R的条件下遍历[i+1,n-1]范围，记录和为固定值负数的项。遍历过程和太大则R--，太小则L++；
ps:遇到相同值则continue,包括i，L，R
*/
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> res;
        if (nums.size()<3){
            return res;
        }
        std::sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size();i++){
            if (nums[i]>0){
                break;
            }
            if (i>0 && nums[i]==nums[i-1]){
                continue;
            }
            int L = i + 1;
            int R = nums.size() - 1;
            while (L<R){
                if (nums[i]+nums[L]+nums[R]==0){
                    res.push_back({nums[i], nums[L], nums[R]});
                    while (L<R && nums[L]==nums[L+1]){
                        L++;
                    }
                    while (L<R && nums[R]==nums[R-1]){
                        R--;
                    }
                    L++;
                    R--;
                }
                else if (nums[i]+nums[L]+nums[R]>0){
                    R--;
                }else{
                    L++;
                }
            }
        }
        return res;
    }
};

int main(){
    return 0;
}