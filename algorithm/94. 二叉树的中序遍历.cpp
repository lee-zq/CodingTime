#include "header.hpp"
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution
{
public:
    /*
解析：这种问题比较好问，主要考察递归函数的实现。
同样的前序中序后序遍历也要熟悉，套路差不多。
*/
    vector<int> inorderTraversal(TreeNode* root)
    {
        vector<int> ret;
        inorder(root, ret);
        return ret;
    }

    void inorder(TreeNode* root, vector<int>& ret)
    {
        if (root == nullptr)
        {
            return;
        }
        inorder(root->left, ret);
        ret.push_back(root->value);
        inorder(root->right, ret);
    }

    void preorder(TreeNode* head, vector<int>& ret)
    {
        if (head == nullptr)
        {
            return;
        }
        ret.push_back(head->val);
        preorder(head->left, ret);
        preorder(head->right, ret);
    }

    void postorder(TreeNode* head, vector<int>& ret)
    {
        if (head == nullptr)
        {
            return;
        }
        postorder(head->left, ret);
        postorder(head->right, ret);
        ret.push_back(head->val);
    }

    void bfs_order(TreeNode* head, vector<int>& ret)
    {
        ret.clear();
        queue<TreeNode*> q = {head};
        while (!q.empty())
        {
            TreeNode* node = q.pop();
            if (node != nullptr)
            {
                ret.push_back(node->val);
                q.push(node->left);
                q.push(node->right);
            }
        }
    }
};