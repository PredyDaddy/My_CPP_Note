```cpp
class A
{
public:
    A& operator++() // 前置++ 
    {
        ++a;
        return *this;
    }

    A operator++(int) // 后置
    {
        A a = *this;
        ++*this;
        return a;
    } 
private:
    int a;
};
```