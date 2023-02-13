# 1. 导语
1. 在C++里面不考虑具体数据类型的编程模式叫做泛型编程，泛型也是一种数据类型，是一种可以用来代替所有数据类型的**通用类型**
2. 可以通过函数模版和类模版实现反省变成。

# 2. 函数模版的基本使用
1. 简单看下函数模版的定义

2. 函数模版的意义: 对类型也可以进行参数化了，不仅仅是减少了工作量，从汇编的角度不用重复构造compare()函数，从而减小了可执行文件的大小
3. 函数模版的语法:
   - template 关键字用于声明开始进行泛型编程
   - typename 关键字用于声明泛指类型
4. **需要注意的是：函数模板是不允许隐式类型转换的，调用时类型必须严格匹配**
```cpp
#include <iostream>
using namespace std;

template<typename T>
bool compare(T a, T b)
{
    cout << "Template compare" << endl;
    return a > b;
}

int main()
{
    // 函数的调用点
    compare<int>(10, 20);
    compare<double>(10.1, 20.5);
    return 0;
}
```

4. 模版函数的两种应用
   - 自动类型推导
   - 具体的类型显示调用
   - 详细的代码解释
```cpp
#include <iostream>
using namespace std;


// template 告诉编译器即将开始泛型编程
template<typename T> // typename 告诉编译器后面代码中的T是一个泛指类型
void Swap(T &a, T &b)
{
    // 不带&，程序传递的是实参的副本，交换的是副本而非实参本身
    // 而当加了&，则传递的是实参的地址，程序将直接对实参进行交换
    T temp = a;
    a = b;
    b = temp;
}

int main()
{
    // 函数的调用点
    int a = 1;
    int b = 2;

    // 自动类型推导: a, b都是int -> T 也是int
    Swap(a, b); 
    cout << "a: " << a << " b: " << b << endl;

    // 显示类型调用: 用float替换参数类型T
    Swap<int>(a, b); 
    cout << "a: " << a << " b: " << b << endl;

    // 函数模板是不允许隐式类型转换的, 调用时类型必须严格匹配
    float c = 3.0;
    // Swap(a, c);  
    // Swap<float>(a, c); 配型错误也是错的
    return 0;
}
```
# 3. 通过符号表深入理解函数模版
1. 无法自动推导函数的返回值
2. 函数返回值在第一个参数中指定, 从做向右部分指定类型参数
```cpp
#include <iostream>
using namespace std;

template <typename T1, typename T2, typename T3>
T1 add(T2 a, T3 b)
{
    T1 ret;
    ret = static_cast<T1>(a + b);
    return ret;
}

int main()
{
    int a = 10;
    float b = 0.5;

    // 报错的原因是无法自动推导函数的返回值
    // cout  << add(a, b) << endl;

    // 函数返回值在第一个参数中指定, 从做向右部分指定类型参数
    cout << add<int>(a, b) << endl; // 掉精度了

    cout << add<float, int, float>(a, b) << endl;
    cout << add<int, int, float>(a, b) << endl;
    return 0;
}
```
# 4. 函数模版的重载
1. C++编译器优先考虑普通函数
2. 如果函数模板可以产生一个更好的匹配，那么就选择函数模板
3. 也可以通过空模板实参列表<>限定编译器只匹配函数模板
```cpp
#include <iostream>
using namespace std;

// 一个泛指类型的函数模板
template <typename T1>
void fun(T1 a)
{
    cout << "T1 a template func" << endl;
}

// 两个泛指类型的函数模版
template <typename T1, typename T2>
void fun(T1 a, T2 b)
{
    cout << "T1 and T2 template func" << endl;
}

// 普通的void函数
void fun(int a, float b)
{
    cout << "int a, float b void func" << endl;
}

int main()
{
    int a = 10;
    float b = 10.5;
    fun(a); // 只有一个，跟第一个匹配上了

    // 普通函数能完美匹配上的时候，编译器优先选择普通函数
    fun(a, b);

    // 当函数模板有更好的调用的时候，用函数模板去调用
    fun(b, a);

    // 限定只使用函数模板, 就算完美匹配上也会优先调用模板函数
    fun<>(a, b); 

    return 0;
}
```
# 5. 函数模版总结
1. 函数模板是泛型编程在C++中的应用方式之一
2. 函数模版能根据实参类型对参数类型进行推导
3. 函数模版支持显示的指定参数类型 (用实际类型去代替T)
```cpp
// 显示的指定返回值为float, 参数a为int, b为float
add<float>(int a, float b);
```
4. 函数模版是C++中重要的代码复用的方式
5. 函数模版可以通过类型产生不同的函数，产生有不同的符号表 
6. 函数模版可以定义多个不同类型的参数 (typename a, typename b)
7. 函数模版的返回值必须显示指定 (不确定返回类型的时候可以用static_cast<类型>强转来保证)
8. 函数模版可以被重载
9. 在任何一个模版中都必须使用template <typename 泛型>声明开始泛型编程

# 6. 类模版的定义
1. 使用类模版构造对象必须指定数据类型 Operator<float> op2;
2. 编译器从类模版通过具体类型产生不同的类
3. 编译器在声明的地方对类模版代码本身进行编译
4. 编译器在使用的地方对参数替换后的代码进行了编译
5. 只有被调用的类模板成员函数才会被编译器生成可执行代码
6. 在类外定义累的成员函数，要加上template<tyname T>
```cpp
#include <iostream>
using namespace std;

template<typename T>
class Operator
{
public:
    T add(T a, T b);

    T minus(T a, T b);
};

// 在类模版外定义成员函数，也要加上template 
template<typename T>
T Operator<T>::add(T a, T b)
{
    return a + b;
}

template<typename T>
T Operator<T>::minus(T a, T b)
{
    return a - b;
}

int main()
{
    Operator<int> op1;
    Operator<float> op2;
    cout << op1.add(3, 5) << endl;
    cout << op1.minus(3, 1.5) << endl; // op1.minus(3, 1)

    cout << op2.add(0.5, 0.2) << endl; 
    cout << op2.minus(3, 2) << endl; 

    return 0;
}
```

# 7. 类模版的特化
1. 