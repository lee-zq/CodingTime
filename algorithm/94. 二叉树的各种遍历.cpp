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
        vector<int> res;
        inorder(root, res);
        // preorder(root, res);
        // postorder(root, res);
        return res;
    }

    void inorder(TreeNode* root, vector<int>& res)
    {
        if (root == nullptr)
        {
            return;
        }
        inorder(root->left, res);
        res.push_back(root->val);
        inorder(root->right, res);
    }

    void preorder(TreeNode* root, vector<int>& res)
    {
        if (root == nullptr)
        {
            return;
        }
        res.push_back(root->val);
        preorder(root->left, res);
        preorder(root->right, res);
    }

    void postorder(TreeNode* root, vector<int>& res)
    {
        if (root == nullptr)
        {
            return;
        }
        postorder(root->left, res);
        postorder(root->right, res);
        res.push_back(root->val);
    }

    void bfs_order(TreeNode* root, vector<int>& res)
    {
        res.clear();
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty())
        {
            TreeNode* node = q.front();
            q.pop();
            if (node != nullptr)
            {
                res.push_back(node->val);
                q.push(node->left);
                q.push(node->right);
            }
        }
    }
};