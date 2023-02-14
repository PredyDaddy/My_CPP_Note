#include <iostream>
#include <type_traits> 
using namespace std;

// 类模版的定义
#if 0
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
#endif

// 类模版的完全特化
#if 0
template<typename T1, typename T2> // 原始模版，也叫模版的声明
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
#endif

// 类模版的部分特化
#if 0

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
#endif

// 父类是一般类，子类是类的模版
#if 0
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
#endif

// 子类是一般类，父类是模版类
#if 0
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
#endif

// 子类父类都是类模版
#if 0
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
#endif

//使用模板类限制模版类型的属性和方法
#if 1
template <typename T>
struct HasValue {
  template <typename U>
  static std::true_type test(decltype(&U::value));

  template <typename U>
  static std::false_type test(...);

  static constexpr bool value = decltype(test<T>(nullptr))::value;
};

template <typename T>
typename std::enable_if<HasValue<T>::value>::type
printValue(T arg) {
  std::cout << "Value: " << arg.value << std::endl;
}

struct MyStruct {
  int value = 42;
};

struct MyOtherStruct {
  float otherValue = 3.14f;
  int value = 43;
};

int main() {
  MyStruct s;
  MyOtherStruct os;

  printValue(s); // 输出：Value: 42

  // 下面这行代码会在编译时出现错误，因为MyOtherStruct类型不满足HasValue的限定条件
  printValue(os);
}
#endif