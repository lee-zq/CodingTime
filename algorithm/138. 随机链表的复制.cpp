/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/
#include "header.hpp"

class Solution
{
public:
    Node* copyRandomList(Node* head)
    {
        if (head == nullptr)
            return head;
        std::unordered_map<Node*, Node*> node_map;
        node_map.insert(std::pair<Node*, Node*>(nullptr, nullptr));
        Node* p = head;
        while (p)
        {
            node_map.insert(std::pair<Node*, Node*>(p, new Node(p->val)));
            p = p->next;
        }
        p = head;
        while (p)
        {
            node_map.at(p)->next = node_map.at(p->next);
            node_map.at(p)->random = node_map.at(p->random);
            p = p->next;
        }
        return node_map.at(head);
    }
};