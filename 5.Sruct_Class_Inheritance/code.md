```cpp
class Father
{
public:
    void func1()
    {cout << "father func1" << endl;}

    void func2(int x)
    {cout << "father func2" << endl;}
};

class Son : public Father
{
public:
    void func1()
    {cout << "son func1" << endl;}

    void func2(char x)
    {cout << "son func2" << endl;}
};

int main()
{
    Father father;
    Son son;
    son.func1();
    son.func2('s');
    return 0;
}
```
