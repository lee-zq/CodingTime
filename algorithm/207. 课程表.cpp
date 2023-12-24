#include "header.hpp"

class Solution
{
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites)
    {
        // [[a<=b], [c<=d]]
        vector<int> inDegree(numCourses, 0);
        std::map<int, vector<int>> m;   
        for (int i = 0; i < prerequisites.size(); i++)
        {
            inDegree[prerequisites[i][0]]++;
            m[prerequisites[i][1]].push_back(prerequisites[i][0]);
        }
        std::queue<int> que;
        for (int i = 0; i < inDegree.size(); i++)
        {
            if (inDegree[i] == 0)
            {
                que.push(i);
            }
        }
        int count = 0;
        while (que.size())
        {
            int selected = que.front();
            que.pop();
            count++;
            std::vector<int>& next_nodes = m[selected]; // 后继节点
            for (int i = 0; i < next_nodes.size(); i++)
            {
                if (inDegree[next_nodes[i]]>0){
                    inDegree[next_nodes[i]]--;
                    if (inDegree[next_nodes[i]] == 0)
                    {
                        que.push(next_nodes[i]);
                    }
                }
            }
        }
        if (count == numCourses){
            return true;
        }else{
            return false;
        }
    }
};