#include "header.hpp"

class Solution {
public:
/*
解析：按行打印二叉树，每行遍历过程中，将结果保存的同时，将非空子节点按从左到右的顺序缓存到队列
并迭代式重复，直到缓存队列为空
ps：因为这里要区分行，所以使用两个vector，而那种z字形打印不区分行，可以使用一个容器完成
*/
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