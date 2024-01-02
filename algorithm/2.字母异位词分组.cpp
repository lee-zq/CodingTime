#include "header.hpp"

using namespace std;

class Solution {
public:
/*
解析：将每个字符串元素sort()后的值作为key，原始字符串作为vector<string>的元素保存，构建map，最后将map转为
vector<string>即为答案
*/
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