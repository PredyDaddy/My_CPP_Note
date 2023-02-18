```cpp
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
```