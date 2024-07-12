#include "header.hpp"

class Solution
{
public:
/*
解析：p字符串是pattern，s是原始搜索空间字符串，这里采用pair<char,int>的map用来保存子字符串中的字符组合情况
首先将p的字符组成用26个char的map表示pCount，s的前p.size()个字符也存入同样的表示sCount；
然后滑窗更新sCount，并在更新后对比和pCount是否相等，从而对结果进行更新累计；
*/
    vector<int> findAnagrams(string s, string p)
    {
        if (p.size() > s.size())
        {
            return {};
        }
        std::vector<int> ret;
        std::vector<int> sCount(26, 0);
        std::vector<int> pCount(26, 0);
        for (int i = 0; i < p.size(); i++)
        {
            pCount[p[i] - 'a']++;
            sCount[s[i] - 'a']++;
        }
        if (pCount == sCount)
        {
            ret.push_back(0);
        }
        int p_len = p.size();
        for (int i = p_len; i < s.size(); i++)
        {
            int start_pos = s[i - p_len] - 'a';
            int end_pos = s[i] - 'a';
            sCount[start_pos]--;
            sCount[end_pos]++;
            if (pCount == sCount)
            {
                ret.push_back(i - p.size() + 1);
            }
        }
        return ret;
    }
};

int main()
{
    std::string a = "cbaebabacd";
    Solution s;
    auto ret = s.findAnagrams(a, "abc");
    for (auto i : ret)
    {
        std::cout << i << std::endl;
    }
    return 0;
}