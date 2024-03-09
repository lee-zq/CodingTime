#include "header.hpp"

class Solution
{
public:
/*
解析：题目要求是按照课程依赖关系来判断课程是否可以修完。
解决方法也是模拟选修课程的顺序，先选择没有前置依赖的课程，然后将依赖这个课程的后续课程的入度减一，
如果入度减到0了，则意味着这个课程也可以直接选择了。
从实现层面来看，我们需要设置一个数据结构存储课程入度（这里用vector<int>,索引为课程编号，值为相应入度），
一个数据结构用于存储每个课程直接驱动的后续课程（出度）（这里用std::map<int, vector<int>>）
计算过程：首先将入度为0的课程，放入队列que，然后从que中弹出一个元素，找出该元素对应的后驱节点，对每个节点的入度减一
若入度减到0了，则将对应的节点加入到que中
重复上述过程，que弹出次数即为修了的课程的数目
如果修了的课程数目达到课程总数，表明可以修完，否则否之
*/
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