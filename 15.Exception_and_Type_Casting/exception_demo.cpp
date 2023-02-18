#include <iostream>
using namespace std;

#if 0
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
#endif

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