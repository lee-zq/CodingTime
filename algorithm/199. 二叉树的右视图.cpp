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
    vector<int> rightSideView(TreeNode* root) {
        vector<int> ans;
        if (root==nullptr){
            return ans;
        }
        vector<TreeNode*> layer_nodes{root};
        while (layer_nodes.size()>0){

            TreeNode* right_node = layer_nodes.back();
            ans.push_back(right_node->val);
            vector<TreeNode*> next_layer_nodes;
            for (auto& item : layer_nodes)
            {
                if (item->left!=nullptr){
                    next_layer_nodes.push_back(item->left);
                }
                if (item->right!=nullptr){
                    next_layer_nodes.push_back(item->right);
                }
            }
            layer_nodes = next_layer_nodes;
        }
        return ans;
    }
};