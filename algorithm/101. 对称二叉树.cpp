#include "header.hpp"

class Solution {
public:
/*
解析：一个二叉树是对称二叉树，也就是左右子树互为翻转二叉树。
而且是递归的左子树的左子树和右子树的右子树对称
*/
    bool isSymmetric(TreeNode* root) {
        return same(root->left, root->right);
    }

    bool same(TreeNode* tree1, TreeNode* tree2){
        if (tree1==nullptr && tree2==nullptr){
            return true;
        }else if (tree1!=nullptr && tree2!=nullptr){
            if (tree1->val==tree2->val){
                return same(tree1->left, tree2->right) && same(tree1->right, tree2->left);
            }
            else
            {
                return false;
            }
        }else{
            return false;
        }
    }
};