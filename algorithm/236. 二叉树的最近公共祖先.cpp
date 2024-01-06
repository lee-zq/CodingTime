/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
#include "header.hpp"

class Solution
{
public:
    /*
解析：题意转换：当节点p和q在节点root的异侧时，节点root即为最近公共祖先，
递归在左子树和右子树中寻找最近公共祖先，如果两侧都找到了，那么肯定是p和q在root的两侧，root即为最近公共祖先
*/
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
    {
        if (root == nullptr || root == p || root == q)
        {
            return root;
        }
        auto left = lowestCommonAncestor(root->left, p, q);
        auto right = lowestCommonAncestor(root->right, p, q);
        if (left==nullptr && right!=nullptr){
            return right;
        }
        if (right==nullptr && left!=nullptr){
            return left;
        }
        if (left != nullptr && right != nullptr)
        {
            return root;
        }
        return nullptr;
    }
};