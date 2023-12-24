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
class Solution {
public:
    ListNode* sortList(ListNode* head) {
        ListNode* tmp = head;
        std::vector<int> arr;
        while (tmp!=nullptr){
            arr.push_back(tmp->val);
            tmp = tmp->next;
        }
        std::sort(arr.begin(), arr.end());
        tmp = head;
        for (auto& val : arr){
            tmp->val = val;
            tmp = tmp->next;
        }
        return head;
    }
};