#include "header.hpp"

class Solution {
public:
    int maxDepth_bfs(TreeNode* root) {
        if (root==nullptr){
            return 0;
        }
        int height = 1;
        std::vector<TreeNode*> vec{root};
        while (1)
        {
            std::vector<TreeNode*> tmp;
            for (auto x : vec)
            {
                if (x->left){
                    tmp.push_back(x->left);
                }
                if (x->right){
                    tmp.push_back(x->right);
                }
            }
            vec = tmp;
            if (vec.size()>0){
                height++;
            }else{
                break;
            }
        }
        return height;
    }
    int maxDepth_dfs(TreeNode* root) {
        int max_height=0;
        backtrack(root, 0, max_height);
        return max_height;
    }

    void backtrack(TreeNode* root, int height, int& max_height){
        if (root==nullptr){
            max_height = max_height > height ? max_height : height;
            return;
        }
        backtrack(root->left, height + 1,max_height);
        backtrack(root->right, height + 1,max_height);
    }
};