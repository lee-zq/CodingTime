#include "header.hpp"

class Solution {
public:
    int diameterOfBinaryTree(TreeNode* root) {
        int ans = 1;
        depth(root, ans);
        return ans-1;
    }

    int depth(TreeNode* root, int& ans){
        if (root==nullptr){
            return 0;
        }
        int L = depth(root->left);
        int R = depth(root->right);
        ans = std::max(ans, R + L + 1);
        return std::max(L, R) + 1;
    }
};