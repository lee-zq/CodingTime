#include "header.hpp"

class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        if (root==nullptr){
            return ans;
        }
        vector<TreeNode*> queue{root};
        while (queue.size()>0){
            vector<int> values;
            vector<TreeNode*> cache_queue;
            for (auto& it : queue){
                values.push_back(it->val);
                if (it->left){
                    cache_queue.push_back(it->left);
                }
                if (it->right){
                    cache_queue.push_back(it->right);
                }
            }
            ans.push_back(values);
            queue = cache_queue;
        }
        return ans;
    }
};