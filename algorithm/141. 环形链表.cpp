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