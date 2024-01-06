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
    /*
解析：随机链表的节点包含两个指针：next和random。
先利用链表特性，将源节点和新节点作为键值对存储到map，然后
重新依次遍历源节点：
map[源节点]->next = map[源节点->next];
map[源节点]->random = map[源节点->random];
*/
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