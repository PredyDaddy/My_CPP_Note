```cpp
class Base
{
public:
    Base()
    {
        cout << "Base构造函数" << endl;
    }
    virtual ~Base()
    {
        cout << "Base析构函数" << endl;
    }
};

class Derived : public Base
{
public:
    Derived()
    {
        cout << "Derived构造函数" << endl;
    }
    ~Derived()
    {
        cout << "Derived的析构函数" << endl;
    }
};

int main()
{
    Base *ptr;
    ptr = new Derived;
    delete ptr;
    return 0;
}
```