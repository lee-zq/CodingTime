#include <iostream>

using namespace std;

void Fun(int& x)
{
    cout << "左值引用" << endl;
}
void Fun(const int& x)
{
    cout << "const 左值引用" << endl;
}

void Fun(int&& x)
{
    cout << "右值引用" << endl;
}
void Fun(const int&& x)
{
    cout << "const 右值引用" << endl;
}
// 模板中的&&不代表右值引用，而是万能引用，其既能接收左值又能接收右值。
// 模板的万能引用只是提供了能够接收同时接收左值引用和右值引用的能力，
// 但是引用类型的唯一作用就是限制了接收的类型，后续使用中都退化成了左值，
// 我们希望能够在传递过程中保持它的左值或者右值的属性, 就需要用我们下面学习的完美转发
template <typename T>
void PerfectForward(T&& t)
{
    // Fun(t);
    Fun(std::forward<T>(t));
}
int main()
{
    PerfectForward(10); // 右值
    int a;
    PerfectForward(a);            // 左值
    PerfectForward(std::move(a)); // 右值
    const int b = 8;
    PerfectForward(b);            // const 左值
    PerfectForward(std::move(b)); // const 右值
    return 0;
}