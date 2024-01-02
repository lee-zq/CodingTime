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
解析：1.双指针，快指针先走N步，然后同步和慢指针前进，当快指针到达尾部时，慢指针到达倒数第N个节点位置；
2. 栈操作。将链表节点压入栈中，然后向外弹出N个节点，然后将栈顶节点的next更新为next->next即可。
PS：伪头节点技巧可以统一操作，让代码更简洁，防止删除头节点时无法保存正确的结果。
*/
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