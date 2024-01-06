#include "header.hpp"

class Solution
{
public:
/*
解析：同步遍历两个链表，在各自到达链表末尾时切换到另一个链表头部继续遍历，全过程同步操作
如果两个链表有交点，则会存在p1==p2
*/
    ListNode* getIntersectionNode(ListNode* headA, ListNode* headB)
    {
        ListNode* p1 = headA;
        ListNode* p2 = headB;

        while (p1 != p2)
        {
            p1 = p1 ? p1->next : headB;
            p2 = p2 ? p2->next : headA;
        }
        return p1;
    }
};