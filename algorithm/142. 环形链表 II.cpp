#include "header.hpp"
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution
{
public:
/*
解析：典型快慢指针题目
1. 设置步长为1的slow指针和步长为2的fast指针
2. 遍历到fast和slow相遇
3. fast置为head地址，快慢以相同的步长1前进，相遇位置为环的入口
PS：数学推导：假设环之前长度为a,环长度为b
在相遇时，快指针走了f步，slow指针走了s步.则有f=2s
而且f指针在相遇时，相比于s指针多走了n圈环。即：f=s+nb
推导出：s=nb，即满指针在相遇时走的步数刚好是环的整数倍，
同时可以知道慢指针在到达环入口需要走的总步数是n*b+a，那么满指针再走a步刚好就到环入口了
同时再构建一个指针从head处同时出发，那么这两个指针将会在环入口处相遇。
*/
    ListNode* detectCycle(ListNode* head)
    {
        if (head == nullptr || head->next == nullptr)
        {
            return nullptr;
        }

        ListNode* fast = head;
        ListNode* slow = head;
        while (1)
        {
            if (fast != nullptr && fast->next != nullptr)
            {
                fast = fast->next->next;
                slow = slow->next;
            }
            else
            {
                return nullptr;
            }
            if (slow == fast)
            {
                break;
            }
        }
        fast = head;
        while (fast != slow)
        {
            fast = fast->next;
            slow = slow->next;
        }

        return fast;
    }
};