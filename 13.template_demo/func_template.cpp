#include <iostream>
using namespace std;

// 一个泛指类型的函数模板
template <typename T1>
void fun(T1 a)
{
    cout << "T1 a template func" << endl;
}

// 两个泛指类型的函数模版
template <typename T1, typename T2>
void fun(T1 a, T2 b)
{
    cout << "T1 and T2 template func" << endl;
}

// 普通的void函数
void fun(int a, float b)
{
    cout << "int a, float b void func" << endl;
}

int main()
{
    int a = 10;
    float b = 10.5;
    fun(a); // 只有一个，跟第一个匹配上了

    // 普通函数能完美匹配上的时候，编译器优先选择普通函数
    fun(a, b);

    // 当函数模板有更好的调用的时候，用函数模板去调用
    fun(b, a);

    // 限定只使用函数模板, 就算完美匹配上也会优先调用模板函数
    fun<>(a, b); 

    return 0;
}