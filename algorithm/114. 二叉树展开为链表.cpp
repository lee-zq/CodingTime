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
    void flatten(TreeNode* root) {
        vector<TreeNode*> array;
        preOrder(root, array);
        if (array.size()<=1){
            return;
        }
        for (int i = 0; i < array.size()-1;i++){
            array[i]->left = nullptr;
            array[i]->right = array[i + 1];
        }
    }

    void preOrder(TreeNode* root, vector<TreeNode*>& array){
        if (root==nullptr){
            return;
        }
        array.push_back(root);
        preOrder(root->left, array);
        preOrder(root->right, array);
    }

    TreeNode* pre = nullptr;
    void flatten(TreeNode* root)
    {
        if (root==nullptr){
            return;
        }
        flatten(root->right);
        flatten(root->left);
        root->right = pre;
        root->left = nullptr;
        pre = root;
    }
};