#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <chrono>
#include <random>
#include <queue>
#include <stack>

#include <iostream>

#include <algorithm>
#include <numeric>

using namespace std;


// Definition for singly-linked list.
struct ListNode
{
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(NULL)
    {
    }
};

class Node
{
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val)
    {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

class TreeNode
{
public:
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr)
    {
    }
    TreeNode(int x) : val(x), left(nullptr), right(nullptr)
    {
    }

    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right)
    {
    }
};
