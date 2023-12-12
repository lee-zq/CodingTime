#include "header.hpp"

using namespace std;

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        std::map<std::string, std::vector<std::string>> m;
        for (auto& it : strs){
            std::string s = it;
            std::sort(s.begin(), s.end());
            if (m.find(s)!=m.end()){
                m[s].push_back(it);
            }else{
                m[s] = {it};
            }
        }
        std::vector<std::vector<string>> ret;
        for (auto& it : m){
            ret.push_back(it.second);
        }
        return ret;
    }
};

int main(){
    Solution s;
    std::vector<std::string> src = {"eat", "tea", "tan", "ate", "nat", "bat"};
    std::vector<std::vector<string>> dst = s.groupAnagrams(src);
    for (auto& it : dst){
        for (auto& it2 : it){
            std::cout << it2 << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}