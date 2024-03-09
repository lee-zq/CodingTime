#include "header.hpp"

class Solution {
public:
/*
题意：就是求二叉树中最长的通路的节点数量，也就是某个节点 左子树深度+右子树深度+1 最大
解析：这个题也引出了求二叉树最大深度的递归解法
而求最大直径则是在这个过程中，对每个递归到的节点的左右深度之和+1进行收集对比。
*/

    int diameterOfBinaryTree(TreeNode* root) {
        int ans = 1;
        int height = depth(root, ans);
        // height是二叉树的深度
        return ans-1;
    }

    int depth(TreeNode* root, int& ans){
        if (root==nullptr){
            return 0;
        }
        int L = depth(root->left, ans);
        int R = depth(root->right, ans);
        ans = std::max(ans, R + L + 1);
        return std::max(L, R) + 1;
    }
};