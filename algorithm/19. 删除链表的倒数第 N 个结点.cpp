#include "header.hpp"
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution
{
public:
    ListNode* removeNthFromEnd(ListNode* head, int n)
    {
        std::stack<ListNode*> stack;
        ListNode* fake_node = new ListNode(-1, head);
        ListNode* cur = fake_node;
        while (cur)
        {
            stack.push(cur);
            cur = cur->next;
        }
        for (int i = 0; i < n; i++)
        {
            stack.pop();
        }
        ListNode* pre_node = stack.top();
        pre_node->next = pre_node->next->next;
        return fake_node->next;
    }
};