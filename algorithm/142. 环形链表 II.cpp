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