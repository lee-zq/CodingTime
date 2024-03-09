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
/*
    对make_heap(), pop_heap(),push_heap() 的用法做个总结： 
    1. make_heap()
    生成堆，他有两个参数，也可以有三个参数，前两个参数是指向开始元素的迭代器和指向结束元素的下一个元素的迭代器。
    第三个参数是可选的，可以用伪函数less()和greater() 来生成大顶堆和小顶堆，其中type为元素类型。如果只传入前两个参数，默认是生成大顶堆。 
    2. push_heap()
    是在堆的基础上进行数据的插入操作，参数与make_heap()相同，需要注意的是，只有make_heap（）和push_heap（）同为大顶堆或小顶堆，
    才能插入,它只会把最后一个元素（堆底）加入堆结构中进行堆化。
    3. pop_heap() 
    是在堆的基础上，弹出堆顶元素, 并重新堆化。这里需要注意的是，pop_heap()
    并没有删除元素，而是将堆顶元素和数组最后一个元素进行了替换，如果要删除这个元素，还需要对数组进行pop_back() 操作。
*/
class Solution
{
public:
/*
解析：这个题目、还有求topk的是一类问题，可以使用堆结构来求解
直接将输入数组堆化，c++中，堆表现为重新排序后的数组，make_heap默认构造的是大顶堆
然后进行堆的pop_heap，这个操作会将堆顶元素移动到堆的末尾（也是数组的末尾），并重新调整为大顶堆
pop_heap并数组pop_back() k-1次之后，数组的第一个元素即为第k大的元素，同样也可以求出topk

*/
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