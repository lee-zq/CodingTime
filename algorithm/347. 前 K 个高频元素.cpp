#include "header.hpp"

class Solution
{
public:
    vector<int> topKFrequent(vector<int>& nums, int k)
    {
        std::unordered_map<int, int> m;
        for (size_t i = 0; i < nums.size(); i++)
        {
            if (m.find(nums[i]) != m.end())
            {
                m[nums[i]]++;
            }
            else
            {
                m[nums[i]] = 1;
            }
        }
        auto compare_func = [](const std::pair<int, int>& a, const std::pair<int, int>& b) { return a.second < b.second; };
        std::vector<std::pair<int, int>> heap(m.begin(), m.end());
        make_heap(heap.begin(), heap.end(), compare_func);
        vector<int> ans;
        for (size_t i = 0; i < k; i++)
        {
            ans.push_back(heap.front().first);
            pop_heap(heap.begin(), heap.end(), compare_func);
            heap.pop_back();
        }
        return ans;
    }
};

int main(){
    vector<int> a = {1, 2, 3, 4, 5, 6, 73, 4, 5, 6, 77, 88, 99};
    Solution s;
    s.topKFrequent(a, 2);
    return 0;
}