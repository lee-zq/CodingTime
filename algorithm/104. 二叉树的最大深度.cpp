#include "header.hpp"

class Solution {
public:
    /*
解析：两种方式求解：
1.直观的层序遍历，每遍历一层，高度加一，并将非空子节点作为新的遍历层，直到遍历层为空，得到高度。
2.递归解法，dfs(TreeNode* root, int cur_height, int& max_height). 初始状态下cur_height=0
在遍历过程种，往下遍历一层则cur_height++, 最后在节点为空是，比较当前高度cur_height和max_height
更新max_height
*/
    int maxDepth_bfs(TreeNode* root)
    {
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