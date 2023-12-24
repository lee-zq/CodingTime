#include "header.hpp"

class Solution
{
public:
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