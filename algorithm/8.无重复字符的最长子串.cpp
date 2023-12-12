#include "header.hpp"

class Solution {
public:
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