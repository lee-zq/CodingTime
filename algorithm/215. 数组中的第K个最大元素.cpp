#include "header.hpp"

// class Solution
// {
// public:
//     int findKthLargest(vector<int>& nums, int k)
//     {
//         if (nums.size()<k){
//             return -1;
//         }
//         vector<int> window(nums.begin(), nums.begin() + k);
//         int min_idx = std::min_element(window.begin(), window.end()) - window.begin();
//         for (size_t i = k; i < nums.size(); i++)
//         {
//             if (nums[i] > window[min_idx])
//             {
//                 window[min_idx] = nums[i];
//                 min_idx = std::min_element(window.begin(), window.end()) - window.begin();
//             }
//         }
//         return window[min_idx];
//     }

    
// };

class Solution
{
public:
    int findKthLargest(vector<int>& nums, int k)
    {
        make_heap(nums.begin(), nums.end());
        for (int i = 0; i < k - 1; i++)
        {
            pop_heap(nums.begin(), nums.end());
            nums.pop_back();
        }
        return nums[0];
    }
};

int main(){
    vector<int> a = {0, 1, 2, 5, 6, 4, 9, 7};
    Solution s;
    s.findKthLargest(a, 4);
}