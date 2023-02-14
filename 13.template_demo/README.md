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
   - 详细的代码解释如下
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
2. 函数返回值在第一个参数中指定, 从左向右部分指定类型参数
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

# 7. 类模版的完全特化
1. 特化分成部分特化跟完全特化
2. 表示可以存在多个相同的类名,但是模板类型都不一致(和函数重载的参数类似)
3. 完全特化的意义
 - 如果您希望为特定类型提供特殊的实现，则可以使用类模板的完全特化版本。这样，您可以将代码的实现与代码的接口分离开来，并且在不同的情况下使用不同的实现。
 - 此外，类模板的完全特化版本还可以帮助您避免不必要的代码冗余，并且可以使代码更具可读性。因此，在某些情况下，使用类模板的完全特化版本可以是一种有效的代码组织方式。
 3. 看一个案例了解类模版的完全特化的意义
 ```cpp
#include <iostream>

template <typename T>
class MyClass {
public:
  void print() {
    std::cout << "This is a generic version of MyClass." << std::endl;
  }
};

template <>
class MyClass<int> {
public:
  void print() {
    std::cout << "This is an integer-specialized version of MyClass." << std::endl;
  }
};

int main() {
  MyClass<double> myClass1;
  myClass1.print();  // Output: This is a generic version of MyClass.

  MyClass<int> myClass2;
  myClass2.print();  // Output: This is an integer-specialized version of MyClass.

  return 0;
}
```
- **输出结果将不同，从而说明了如何使用类模板的完全特化版本来为特定类型提供特殊的实现。**

4. 类模版的特化匹配
```cpp
// 类模版的特化

// 原始模版，也叫模版的声明
template<typename T1, typename T2>
class Operator
{
public:
    Operator()
    {
        cout << "Operator" << endl; 
    }

    void add(T1 a, T2 b)
    {
        cout << a + b << endl;
    }
};

// 完全特化的类模版不需要指定模版类型
template <>
class Operator<int, int>  // 指定类型参数，因为为2个参数，和正常模版参数个数一致
{
/*
原始的类模板 Operator 有两个泛型类型：T1 和 T2。因此，其创建的完全特化版本 Operator<int, int> 也必须有两个类型参数
*/
public:
    Operator()
    {
        cout << "Operator<int int>" << endl;
    }
    void add(int a, int b, int c)
    {
        cout << a + b << endl;
    }
};



int main()
{       
    // 匹配完全特化类模版
    Operator<int, int> op1;

    // 匹配正常模版
    Operator<int, float> op2;
    return 0;
}
```
- **原始的类模板有两个泛型类型（例如 T1 和 T2），那么为其创建的完全特化版本也必须有两个类型参数，否则编译器将报错**
- 完全特化的类模版不能使用泛指类型 T1 和 T2

5. 类模版的部分特化
- 不管是部分特化的类模版还是完全特化的类模版，如果声明的类模版有两个参数，他们都要有两个参数
- 编译时,会根据对象定义的类模板类型,首先去匹配完全特化,再来匹配部分特化,最后匹配正常的类模板
```cpp
template<typename T1, typename T2> // 声明的类模版参数个数是两个
class Operator                     // 正常的类模版
{
public:
    Operator()
    {
        cout << "Operator" << endl;
    }
    void add(T1 a, T2 b)
    {
        cout << a + b << endl;
    }
};

template<typename T>     // 有指定模版类型及其参数，所以是部分特化的类模版
class Operator<T*, T*>   // 指定类型参数，必须为2个参数，和正常摩安参数个数一样
{
public:
Operator()
{
        cout << "Operator<T*, T*>" << endl;
}
void add(T* a, T* b)
{
        cout << *a + *b << endl;
}
};

template<typename T1, typename T2>     // 有指定模版类型及其参数，所以是部分特化的类模版
class Operator<T1*, T2*>   // 指定类型参数，必须为2个参数，和正常摩安参数个数一样
{
public:
Operator()
{
        cout << "Operator<T1*, T2*>" << endl;
}
void add(T1* a, T2* b)
{
        cout << *a + *b << endl;
}
};

int main()
{
Operator<int*, float*> op1; // 匹配部分特化模版
Operator<int, float> op2;   // 匹配原始模版
Operator<int *, int *> op3; // 匹配部分特化模版
}
```
# 8. 继承中类的模版使用
1. 父类是一般类，子类是类的模版，没什么特别要注意的
```cpp
class A
{
public:
    A(int temp): _temp(temp){}; 
    ~A(){}

private:
    int _temp;
};

template <typename T>
class B : public A
{
public:
    B(T t = 0): A(666)
    {
        this->t = t;
    }
    ~B(){}

private:
    T t;
};

int main()
{
    B<int> b;
    return 0;
}
```
2. 子类是一般类，父类是模版类，继承的时候要写上类型，这就是模版的调用点
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
3. 父类子类都是类模版
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

面试可能会问到的问题
1. 
