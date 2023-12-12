#include "header.hpp"

class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        if (p.size()>s.size()){
            return {};
        }
        std::vector<int> ret;
        std::vector<int> sCount(26, 0);
        std::vector<int> pCount(26,0);
        for (int i = 0; i < p.size();i++){
            pCount[p[i] - 'a']++;
            sCount[s[i] - 'a']++;
        }
        if (pCount==sCount){
            ret.push_back(0);
        }
        for (int i = p.size(); i < s.size();i++){
            sCount[s[i - p.size()]-'a']--;
            sCount[s[i] - 'a']++;
            if (pCount==sCount){
                ret.push_back(i - p.size()+1);
            }
        }
        return ret;
    }
};

int main(){
    Solution s;
    auto ret = s.findAnagrams("cbaebabacd", "abc");
    for (auto i : ret){
        std::cout << i << std::endl;
    }
    return 0;
}