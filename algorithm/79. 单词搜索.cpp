#include "header.hpp"

/*
题目描述：在一个字符二维数组中查找是否存在和目标字符串相等的路径
解析：这个题目和在二维数组中查找岛屿数量、岛屿周长问题类似，需要递归分析。
对二维数组中某一个位置展开搜索，搜索成功则直接返回。
搜索函数定义为process(int r, int c, int idx, string& word, vector<vector<char>>& board)
表示在从r行c列开始，搜素从idx索引开始的word字串在board中是否存在。
存在的条件是递归搜索到字串末尾，要注意在搜索过的位置将值置为0，并在回退时恢复该值。
子问题是当前值匹配，且剩余字符在当前搜索位置的四周存在一个匹配即可。
*/

class Solution
{
    int row_;
    int col_;
public:
    bool exist(vector<vector<char>>& board, string word)
    {
        row_ = board.size();
        col_ = board[0].size();

        for (size_t r = 0; r < row_; r++)
        {
            for (size_t c = 0; c < col_; c++)
            {
                if(process(r, c, 0, word, board)){
                    return true;
                }
            }
        }
        return false;
    }

    bool process(int r, int c, int idx, string& word, vector<vector<char>>& board)
    {
        if (idx == word.size())
        {
            return true;
        }
        if (r < 0 || c < 0 || r >= row_ || c >= col_)
        {
            return false;
        }
        char& ch = word[idx];
        if (board[r][c] != ch)
        {
            return false;
        }
        board[r][c] = '0';
        bool flag = process(r - 1, c, idx + 1, word, board) || process(r + 1, c, idx + 1, word, board) ||
                    process(r, c - 1, idx + 1, word, board) || process(r, c + 1, idx + 1, word, board);
        board[r][c] = ch;
        return flag;
    }
};