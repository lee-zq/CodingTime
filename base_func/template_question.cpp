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
    // ShowList(1);
    // ShowList(1, 'A');
    // ShowList(1, 'A', std::string("sort"));
    using namespace std;
    cout << is_integral<int>::value << endl;    //int属于整型，所以输出1
    cout << is_integral<double>::value << endl; //double不属于整型，所以输出0
    cout << is_integral_v<int> << endl;         //这是更好的写法，输出1
    cout << is_integral_v<double> << endl;      //这是更好的写法，输出0
    return 0;
}