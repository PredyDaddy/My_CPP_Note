```cpp
template<typename T>
class A
{
public:
    A(T t=0)
    {
        this->t = t;

    }

private:
    T t;
};

class B : public A<int>
{
public:
    B(int temp = 0):A<int>(666)
    {
        this->temp = temp;
    }

private:
    int temp;
};

int main()
{
    B b;
    return 0;
}
```