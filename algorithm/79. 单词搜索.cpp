#include "header.hpp"

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