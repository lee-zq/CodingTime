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
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        return helper(root, LONG_MIN, LONG_MAX);
    }

    bool helper(TreeNode* root, int lower, int upper){
        if (root==nullptr){
            return true;
        }
        if (root->val<lower || root->val>upper){
            return false;
        }
        bool left_status = helper(root->left, lower, root->val);
        bool right_status = helper(root->right, root->val, upper);
        return left_status && right_status;
    }

    long long pre = LONG_MIN;
    bool isValidBST(TreeNode* root)
    {
        if (root==nullptr){
            return true;
        }
        if (isValidBST(root->left)==false){
            return false;
        }
        if (root->val>pre){
            return true;
        }
        pre = root->val;
        return isValidBST(root->right);
    }
};