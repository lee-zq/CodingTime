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
/*
解析：类似于竖式求和一样，从低位向高位递推，注意每次计算的value值为模，进位为商，当
两个链表都遍历完后终止，但需要再次判断进位是否非0以确定是否再追加节点
*/
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
    {
        if (l1 == nullptr && l2 == nullptr)
        {
            return nullptr;
        }
        int factor = 0;
        ListNode* pre_head = new ListNode(-1);
        ListNode* cache_pre_head = pre_head;
        while (l1 || l2)
        {
            int sum = (l1 ? l1->val : 0) + (l2 ? l2->val : 0);
            int value = (sum + factor) % 10;
            factor = (sum + factor) / 10;
            ListNode* new_node = new ListNode(value);
            pre_head->next = new_node;
            pre_head = pre_head->next;
            l1 = l1 ? l1->next : nullptr;
            l2 = l2 ? l2->next : nullptr;
        }
        if (factor > 0)
        {
            ListNode* new_node = new ListNode(factor);
            pre_head->next = new_node;
            pre_head = pre_head->next;
        }

        return cache_pre_head->next;
    }
};