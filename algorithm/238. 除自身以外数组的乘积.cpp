#include "header.hpp"

/*
两侧遍历分别求左边积和右边积，然后在新的数组中汇总即可
状态可压缩到额外O（N）空间复杂度
*/

int mul_exclude_cur_elem(std::vector<int>& nums){
    int len = nums.size();
    std::vector<int> ret(len, 1);
    for (int i = 1; i < len; i++)
    {
        ret[i] = nums[i-1]*ret[i-1];
    }
    int pre = 1;
    for (int i = len-1; i >=0 ; i--)
    {
        ret[i] *= pre;
        pre *= nums[i];
    }
    return ret;
}