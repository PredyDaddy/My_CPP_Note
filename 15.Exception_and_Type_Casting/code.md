```cpp
class Base
{
public:
  Base(){};
  virtual void show()
  {
    cout << "This is Base class" << endl;
  }
  void func1()
  {
    cout << "Base::func1" << endl;
  }
};

class Derived : public Base
{
public:
  Derived(){};
  void show()
  {
    cout << "This is Derived class" << endl;
  }
};

int main()
{
  // 基类指针转向派生类指针
  Base *ptr = new Base;
  Derived *ptr1 = dynamic_cast<Derived *>(ptr);
  // ptr1->show(); // 转失败了，这里是个空指针
  delete ptr;

  Base *ptr2 = new Derived;
  Derived *ptr3 = dynamic_cast<Derived *>(ptr2);
  ptr2->show(); // 转换成功
  delete ptr2;

  // 派生类指针转向父类，向上转总是安全的，不用用到dynamic_cast
  Derived *der = new Derived;
  Base *base;
  base = der; // 完成转换，虽然基类指针依然指向派生类，但是也没报错，安全
  base->show();
  base->func1();
  
  return 0;
}
```