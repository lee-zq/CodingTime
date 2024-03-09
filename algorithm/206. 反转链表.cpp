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
解析：经典简洁、好问的问题。
遍历解法：构建两个指针pre和cur，都初始化为nullptr。
在遍历过程在，先缓存cur的next节点为next_node，
然后将cur的next置为pre的值。
然后将pre置为cur的值，cur置为缓存的next_node. 遍历到结束后返回pre
*/
    ListNode* reverseList(ListNode* head)
    {
        ListNode* cur = head;
        ListNode* pre = nullptr;
        while (cur != nullptr)
        {
            ListNode* next_node = cur->next;
            cur->next = pre;
            
            pre = cur;
            cur = next_node;
        }
        return pre;
    }
};