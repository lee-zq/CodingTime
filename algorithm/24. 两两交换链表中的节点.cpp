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
#include "header.hpp"

class Solution
{
public:
/*
解析：先构建一个伪头节点，以此节点为起始，在next和next->next都存在的条件下，交换这两个节点
最后返回伪头节点的next
*/
    ListNode* swapPairs(ListNode* head)
    {
        ListNode* fake_node = new ListNode(-1, head);
        ListNode* tmp = fake_node;

        while (tmp->next && tmp->next->next)
        {
            ListNode* node1 = tmp->next;
            ListNode* node2 = tmp->next->next;
            tmp->next = node2;
            node1->next = node2->next;
            node2->next = node1;
            tmp = node1;
        }
        ListNode* result = fake_node->next;
        delete fake_node;
        return result;
    }
};