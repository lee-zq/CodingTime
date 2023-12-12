#include "header.hpp"

class Solution
{
public:
    void setZeroes(vector<vector<int>>& matrix)
    {
        std::vector<int> m(matrix.size(), 1);
        std::vector<int> n(matrix[0].size(), 1);
        for (int i = 0; i < matrix.size();i++){
            for (int j = 0; j < matrix[0].size(); j++)
            {
                if (matrix[i][j]==0){
                    m[i] = n[j] = 0;
                }
            }
        }
    }
    for (int i = 0; i < m.size();i++){
        if (m[i]==0){
            matrix[i].assign(matrix[i].size(), 0);
            continue;
        }
        for (int j = 0; j < n.size();j++){
            if (n[j]==0){
                matrix[i][j] = 0;
            }
        }
    }
}
