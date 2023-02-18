#include <iostream>
using namespace std;

// 1. const修饰普通变量
#if 0
int main()
{
  // a是只读的，必须在定义的时候给一个初始值
  // 以便于编译器能够正常的初始化
  // const int a;  这句话就会报错
  const int a = 0;

  // 这样不会报错的
  const int *p;

  // 建议给指针一个初始化
  // p2是一个指向const int的类型的指针, const修饰*p，*p不能被修改
  // 可以通过修改b的值，p2指向的地址没变，依然是指向b
  int b = 10;
  const int *p2 = &b;
  // *p2 = 12; // 被const修饰成只读对象，这样写会报错
  b = 11;
  cout << *p2 << endl;
  
  // 所以比较规范的const 指针写法是
  const int c = 10;
  const int *p3 = &c; 
  return 0;
}
#endif

// 2. const修饰成员变量，成员函数
#if 0
class A
{
public:
  A() {}
  A(int value) : _value(value) {} // 只能通过这样赋值
  // void get_func(){_value++;} // 会报错的

  void func2() const
  {
    cout << "Legal const function " << endl;
  }

  // const修饰的成员函数不可以改变成员变量和调用非const的成员函数
  // void func3() const{value2++;} 会报错的

  // 只能调用const修饰的成员变量
  void func4() const { func5(); }
  void func5() const {}

public:
  const int _value = 10; // 不能被修改
  int value2;
};

// 全局函数不可以被const修饰
// void func_global() const {} // 会报错的


int main()
{
  A a(100); // 输出 100
  cout << a._value << endl;

  A a1; // 输出 10
  cout << a1._value << endl;

  a1.func4();

  return 0;
}
#endif

// 3. const修饰对象
#if 0
class A
{
public:
  int x = 0;

public:
  void func()
  {
    cout << "Normal Fuction" << endl;
  }

  void func1() const
  {
    cout << "const func" << endl;
  }
};

int main()
{
  A a;
  a.x = 100;
  cout << a.x << endl;

  const A a1;

  // a1.x = 100; // 会报错，不能修改任何成员
  // a1.func();     // 会报错，不能修改任何成员
  a1.func1(); // 可以访问const成员函数
  return 0;
}
#endif

// 4. const修饰引用
#if 0
void func1(const int &t)
{
  // t++; // 引用参数在函数内不可以改变
}

int main()
{
  int a = 19;
  int &b = a;
  b = 20;
  cout << a << endl;

  const int c = 19;
  const int &d = c; // 引用指向某个常量时，需要用const修饰
  // d = 20; // 会报错

  return 0;
}
#endif

// 5. 函数返回值
