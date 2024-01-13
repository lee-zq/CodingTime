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
/*
解析：二叉搜索树的左右子树也是二叉搜索树
将有序数组的中点值作为根节点，然后左右子数组分别构建根节点的左右子树，返回根节点
递归结束条件是子数组为空了
*/
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return helper(nums, 0, nums.size() - 1);
    }

    TreeNode* helper(vector<int>& nums, int start, int end){
        if (end<start){
            return nullptr;
        }
        int mid = start + (end - start) / 2;
        TreeNode* root = new TreeNode(nums[mid]);
        
        root->left = helper(nums, start, mid-1);
        root->right = helper(nums, mid+1, end);
        return root;
    }
};