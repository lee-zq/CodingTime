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
#include "header.hpp"

class Solution {
public:
    vector<int> in_order_arr;
    int kthSmallest(TreeNode* root, int k)
    {
        inOrder(root);
        if (in_order_arr.size()<k){
            return -1;
        }
        return in_order_arr[k-1];
    }

    int inOrder(TreeNode* root){
        if (root==nullptr){
            return 0;
        }
        inOrder(root->left);
        in_order_arr.push_back(root->val);
        inOrder(root->right);
        return 0;
    }
};