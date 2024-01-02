#include "header.hpp"

class Solution {
public:
/*
解析：滑动窗口。窗口用一个set维护，在添加一个字符前判断是否在set内，在的话从窗口左边开始删除字符
，直到不存在再将该字符插入到set中，此时记录set的size即为不重复字符子串的长度，比较求最大值。
*/
    int lengthOfLongestSubstring(string s) {
        std::set<char> lookup;
        int left = 0;
        int right = 0;
        int max_value = 0;
        for (int right = 0; right < s.size();right++){
            char x = s[right];
            while (lookup.find(x)!=lookup.end()){
                lookup.erase(s[left]);
                left++;
            }
            lookup.insert(x);
            max_value = std::max(max_value, right - left + 1);
        }
        return max_value;
    }
};

int main(){
    std::string x = "xyabcdefagh";
    Solution s;
    int ret = s.lengthOfLongestSubstring(x);
    std::cout << ret << std::endl;
}