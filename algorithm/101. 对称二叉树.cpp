#include "header.hpp"

class Solution {
public:
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