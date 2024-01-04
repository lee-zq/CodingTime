#include "header.hpp"

class Solution
{
public:
/*
解析：要理解子集扩充的递推关系。在已经有子集集合的情况下，如果在添加一个不同的元素，那么
给子集集合每个子集都新增当前元素的结果，是新增的子集集合。
所以，遍历每个元素，然后在已存在子集集合的基础上扩充（已知空集是基准）
*/
    vector<vector<int>> subsets(vector<int>& nums)
    {
        vector<vector<int>> ret{{}};
        for (auto& i : nums)
        {
            int count = ret.size();
            for (int j = 0; j < count;j++)
            {
                auto s = ret[j];
                s.push_back(i);
                ret.push_back(s);
            }
        }
        return ret;
    }
};

int main(){
    vector<int> a = {1, 2, 3};
    Solution s;
    auto ret = s.subsets(a);
    return 0;
}