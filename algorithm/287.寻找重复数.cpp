#include "header.hpp"

class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        std::set<int> s;
        for(auto& item : nums){
            if (s.find(item)!=s.end()){
                return item;
            }else{
                s.insert(item);
            }
        }
        return 0;
   }
    int findDuplicate(vector<int>& nums) {
        // 将数据视为一个链表,转化为求环形链表入口值
        int slow = nums[0];
        int fast = nums[nums[0]];
        while (slow!=fast)  
        {
            slow = nums[slow];
            fast = nums[nums[fast]];
        }
        fast = 0;
        while(slow!=fast){
            fast = nums[fast];
            slow = nums[slow];
        }
        return slow;
   }
};