#include "header.hpp"

class Solution
{
public:
/*
解析：经典合并两个链表。构建一个伪头节点，然后在两个链表都不为空的条件下循环遍历，将值较小的节点串联在当前节点后，
在条件判断失效后，将不为空的剩余链表串接在当前节点后，返回伪头节点的next；
*/
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2)
    {
        ListNode preNode(-1);
        ListNode* pre = &preNode;
        while (list1 != nullptr && list2 != nullptr)
        {
            if (list1->val < list2->val)
            {
                pre->next = list1;
                list1 = list1->next;
            }
            else
            {
                pre->next = list2;
                list2 = list2->next;
            }
            pre = pre->next;
        }
        if (list1 == nullptr)
        {
            pre->next = list2;
        }
        else
        {
            pre->next = list1;
        }

        return preNode.next;
    }
};