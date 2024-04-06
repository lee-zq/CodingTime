#include "header.hpp"

class Solution {
public:
/*
解析：先递归将左子节点反转、右子节点反转，然后将根节点的左右节点交换，返回root节点。
*/
    TreeNode* invertTree(TreeNode* root) {
        if (root==nullptr){
            return root;
        }
        invertTree(root->left); 
        invertTree(root->right);
        TreeNode* tmp = root->left;
        root->left = root->right;
        root->right = tmp;
        return root;
    }
};