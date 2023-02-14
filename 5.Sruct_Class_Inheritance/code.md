```cpp
class Base
{
public:
    static int getNum() { return sNum; }
    static int getNum(int param){
        return sNum + param; }

    public:
        static int sNum;
};
int Base ::sNum = 10;

class Derived : public Base
{
public:
    static int sNum; // 这里的话父类同名的成员属性被隐藏

    // 父类的方法同样被隐藏了
    // 改变基类中一个函数的特征，所有使用该函数名的基类版本都会被隐藏
    static int getNum(int param1, int param2)
    {
        return sNum + param1 + param2;
    }
};
int Derived :: sNum = 100;

int main()
{
        Base obj;
        cout << obj.getNum() << endl;
        cout << obj.getNum(1) << endl;
        Derived obj2;

        // 编译器报错，这里不会去父类找可以匹配到的，因为被隐藏了
        // obj2.getNum();

        cout << obj2.getNum(1, 2) << endl;
        
        return 0;
}
```
