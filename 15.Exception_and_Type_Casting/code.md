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