#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> split(const std::string& str, char delimiter)
{
    std::vector<std::string> tokens;
    size_t start = 0;
    size_t end = str.find(delimiter);

    while (end != std::string::npos)
    {
        tokens.push_back(str.substr(start, end - start));
        start = end + 1;
        end = str.find(delimiter, start);
    }

    tokens.push_back(str.substr(start)); // 添加最后一个片段
    return tokens;
}

std::vector<std::string> split_str(const std::string& str, std::string delimiter)
{
    std::vector<std::string> tokens;
    size_t start = 0;
    size_t end = str.find(delimiter);

    while (end != std::string::npos)
    {
        tokens.push_back(str.substr(start, end - start));
        start = end + delimiter.size();
        end = str.find(delimiter, start);
    }

    tokens.push_back(str.substr(start)); // 添加最后一个片段
    return tokens;
}

int main()
{
    std::string str = "one,two,three555ee 666";
    std::string delimiter = "ee";
    std::vector<std::string> tokens = split_str(str, delimiter);

    for (const std::string& token : tokens)
    {
        std::cout << token << std::endl;
    }

    return 0;
}