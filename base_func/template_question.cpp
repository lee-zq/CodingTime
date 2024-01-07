#include <iostream>
#include <string>
using namespace std;

template <class T>
void PrintArg(T t)
{
    cout << t << " ";
}
//展开函数
template <class... Args>
void ShowList(Args... args)
{
    int arr[] = {(PrintArg(args), 0)...};
    cout << endl;
}
int main()
{
    ShowList(1);
    ShowList(1, 'A');
    ShowList(1, 'A', std::string("sort"));
    return 0;
}