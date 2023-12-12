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
    bool isPalindrome(ListNode* head)
    {
        std::vector<int> tmp;
        while (head != nullptr)
        {
            tmp.push_back(head->val);
            head = head->next;
        }

        int left = 0, right = tmp.size() - 1;
        while (left <= right)
        {
            if (tmp[left] != tmp[right])
                return false;
            left++;
            right--;
        }
        return true;
    }
};