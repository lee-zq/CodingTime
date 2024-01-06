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
/*
二叉搜索树：根节点值大于左子树最大值且小于右子树最小值，即max(root->left) < root->val < min(root->right)
解析：可以理解为，每个节点存在一个上界和下界，下届为左子树最大值，上界为右子树最小值。递归属性。
当当前节点为空则为true，当当前节点值不在当前上下界内，则为false。在此基础上，左子树上界为当前节点值，下界不更新；
右子树下界为当前节点值，上界不更新。分别求得左右子树的二叉平衡性，都满足则为true，否则false

*/
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