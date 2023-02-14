```cpp
// 子类父类都是类模版
template <typename T1, typename T2>
class A   
{
    // 类的默认访问修饰词是private, 所以这里的x, y是私有属性
    // 如果向指定为公有的，需要修改饰词为public
    T1 x;
    T2 y;
};

template <typename T1, typename T2>
class B : public A<T2, T1>
{
    T1 x1;  
    T2 x2;  
};

template<typename T>
class C : public B<T, T>
{
    T x3;
};

int main()
{
    // B中的T1和A中的T1 泛指int, B中的T2,A中的T1 泛指float
    B<int, float> b;

    // 这样A，B，C中全部泛指类型都是int
    C<int> c;
    return 0;
}
```