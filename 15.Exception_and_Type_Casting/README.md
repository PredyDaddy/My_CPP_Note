# 1. 抛出异常
```cpp
#include <iostream>
using namespace std;

double division(int a, int b)
{
   if( b == 0 )
   {
      throw "Division by zero condition!";
   }
   return (a/b);
}  

int main()
{
  cout << division(10, 0) << endl;
  return 0;
}
```

# 2. 捕获异常
**由于我们抛出的异常为字符串，所以，当捕获该异常时，我们必须在 catch 块中使用 const char***
```cpp
try
{
   // 保护代码
}catch( ExceptionName e )
{
  // 处理 ExceptionName 异常的代码
}
```
```cpp
double division(int a, int b)
{
  if (b == 0)
  {
    throw "Division by zero condition!";
  }
  return (a / b);
}

double division1(int a, int b)
{
  if (b == 0)
  {
    throw "Division1 by zero condition!";
  }
  return (a / b);
}

int main()
{
  try
  {
    division(10, 0);
    division1(10, 0);
  }
  catch (const char *msg)
  {
    std::cerr << msg << endl;
  }

  return 0;
}
```

```cpp
class MyException : public exception
{
public:
  const char *what() const throw()
  {
    return "C++ Exception";
  }
};

int main()
{
  try
  {
    throw MyException();
  }
  catch (MyException &e)
  {
    cout << "MyException caught" << endl;
    cout << e.what() << endl;
  }
  catch (exception &e)
  {
    // 其他的错误
  }
}
```
