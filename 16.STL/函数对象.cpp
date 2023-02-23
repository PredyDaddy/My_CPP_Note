#include <iostream>
using namespace std;

// 什么是函数对象
#if 0
// 普通函数
int sum(int a, int b)
{
  return a + b;
}

// 有operator小括号运算符重载函数的对象称作函数对象/仿函数
class Sum
{
public:
  int operator()(int a, int b)
  {
    return a + b;
  }
};
int main()
{
  cout << "普通函数: " << sum(10, 20) << endl;
  Sum sum1;
  cout << "函数对象: " << sum1(10, 20) << endl;
  return 0;
}
#endif

// 函数对象的好处
