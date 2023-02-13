# 1. 掌握形参带默认值的函数
1. 以一个简单的案例来看三种情况
2. 总之，都有压栈，有些没有把数据存入寄存器中的
```cpp
#include <iostream>
using namespace std;

int sum(int a = 10, int b = 20)
{
    return a + b;
}

int main()
{
    // 声明处给形参默认值
    int sum(int a, int b = 30); // 这里有上面那个就不掉用了，编译的时候就发现不了这个错误
    int sum(int a = 20, int b); // 上面只给了b的，初始值，这里给a的默认值
    
    int a = 10;
    int b = 20;
    int ret = sum(a, b);
    /* 先把b放到寄存器里面，入栈，再把a放到寄存器里面，再入栈 再call sum
        有了形参依然要压栈
    mov ecx, dword ptr[ebp - 8]
    push ecx
    mov ecx, dword ptr[ebp - 4]
    push ecx
    call sum
    */

    ret = sum(a);
    /* 只用
    push 14H 
    mov exc, dword ptr[ebp - 4]
    push ecs
    call sum
    */

    ret = sum();
    /*
    push 14H
    push 04H
    call sum()
    */
    cout << "ret is: " << ret << endl;
    return 0;
}
```
1. 默认值只能从右向左给
2. 调用效率的问题
     - 有默认值依然要压栈，有几个参数压几次栈，只是少了mov指令 把参数放到寄存器里面去
     - 分清楚什么时候需要存入寄存器
3. 定义和声明都可以给形参默认值，不论在哪里给，形参默认值只能给一次
```cpp
// 声明处给形参默认值
    int sum(int a, int b = 30); // 这里有上面那个就不掉用了，编译的时候就发现不了这个错误
    int sum(int a = 20, int b); // 上面只给了b的，初始值，这里给a的默认值
```

## 延伸问题？ 要不要压栈，什么情况下会把数据存入寄存器，为什么从右边向左边压栈？

# 2. 内联函数的深入理解
## 内联函数和普通函数的区别？
1. 内联函数在编译过程中，就没有函数调用的开销，在函数的调用点直接把函数的代码进行展开处理
2. 函数的开销: 函数的调用过程，函数栈帧的开辟和回退过程
   - x + y  mov add mov 
   - sum 就有一堆的栈帧开辟，如果循环次数多，就不停的开销
   - 这样函数的开销就远远大于函数本身的指令时间
   - 内联函数直接展开了，没有开辟栈帧，回退操作
   - 但是不会所有的inline都会被处理成内联函数 - 递归
   - inline只是建议编译器处理成内联函数，最终由编译器决定是否成为内联函数
   - inline只有在release版本下才能出现，debug不起作用的
## 问题: 内联函数跟普通函数的区别？
  1. 没有开销，这个时候可以回答开销的具体细节......

# 函数重载: 
1. 函数名相同，参数列表的个数或者类型不同
2. 一定处在同一作用域

## 核心问题
1. 搞明白C++ 为什么支持函数重载？
   - 在C++产生符号的时候，是函数名+参数列表类型组成的
   - 同样的函数名和同样的参数列表(类型)只是函数的重定义
   - C语言是产生符号时候，只由函数名组成
2. 函数重载需要注意什么？
   - 首先得处在同一个作用域
   - const volatitle怎么影响形参类型
   - 函数重载跟返回值无关
   - 要确认什么时候是函数重定义和函数重载，函数重定义是会报错的
1. C++和C语言代码之间如何互相调用？
    - C++ 无法直接调用C 要把C函数的声明写在 extern "C"
    - C可以调用C++ 在被调用的代码里面写在extern "C"
    - 都是在C++里面写，extern "C" 只被C++认识
2. 请解释一下什么事多态？
   - 静态(编译时期)的多态: 函数重载  
   - 动态(运行时期)的多态: ...........
3. 面试官问函数重载，也可以延伸到多态

## 函数重载的全部代码
```cpp
#include <iostream>
#include <cstring>
#include <typeinfo>
using namespace std;

// 三种类型的compare的案例
// 涉及知识点: 作用域的问题，函数重载必须发生在相同的作用域
// 调用的时候会寻找最近的作用域去查找
#if 0
bool compare(int a, int b)
{
    cout << "compare int and int" << endl;
    return a > b;
}

bool comapre(double a, double b)
{
    cout << "compare double and double" << endl;
    return a > b;
}

bool compare(char *a, char *b)
{
    cout << "compare double and double" << endl;
    return strcmp(a, b) > 0;
}

int main() 
{   
    // 在这里声明就会有编译错误，因为函数重载要在一个作用域, 这里就不是函数重载
    // double会损失精度，char没法转成int类型
    // int compare(int a, int b); 
    
    compare(10, 20);
    compare(10.0, 20.0);     // 损失精度，不会有编译问题
    compare("Aaa", "bbb");   // 没法转换成int类型

    return 0;
}
#endif


// 函数重定义的案例，重定义会出现编译错误
void func(int a) {}         // 参数 int
// void func(const int a) {}   // 参数也是 int
int main()
{
    int a = 10;
    const int b = 20;
    // 看一下两个参数的类型
    cout << typeid(a).name() << endl;
    cout << typeid(b).name() << endl;
    return 0;
}
```


```

