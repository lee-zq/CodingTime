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
解析：如何判断一个链表有环。作快慢两个指针，快指针步长为2，慢指针步长为1.
如果存在环，则必定存在快慢指针相等的时刻。否则快指针会先遍历到结尾，跳出循环返回false
*/
    bool hasCycle(ListNode* head)
    {
        if (head == nullptr || head->next == nullptr)
        {
            return false;
        }

        ListNode* pTwo = head->next;
        ListNode* pOne = head;
        while (pTwo != pOne)
        {
            if (pTwo != nullptr && pTwo->next != nullptr)
            {
                pTwo = pTwo->next->next;
                pOne = pOne->next;
            }
            else
            {
                return false;
            }
        }
        return true;
    }
};