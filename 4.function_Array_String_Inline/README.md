# 1. C++函数
- 局部变量最好有一个初始值，不然就会随机了
- 全局变量自动初始值为0
- 局部变量也被称之为栈变量，在C++里面需要关心变量的生命周期
- 栈变量，出栈即消亡，内存中栈变量的储存区
- 全局变量储存在常量储存区
- new出来的变量储存在内存中的堆空间，需要自己去控制这个变量的销毁
- C++11出来了智能指针，去控制变量的销毁
- 简单看一个函数的case

```cpp
#include <iostream>

int max(int num1, int num2) {
    // 局部变量声明
    int result = 0;   // 栈变量
    if (num1 > num2) 
        return num1;
    
    else 
        return num2;   // 这里的num1, num2出栈了销毁了，会有另外一个空间去接收他们
}

int main() {
    
    std::cout << "result of max function is: " <<  max(5, 8) << std::endl;
    return 0;
}
```
## 函数传值，传引用，指针
- 传值是在调用的额时候复制了一下，但是可以设置默认值

```cpp
// 传值 值的传递，复制一份value, 下面main函数调用的时候只是把value复制了一份传过来
// 效率是低的
void swap_value(int x = 5, int y = 10) {
    int temp;
    temp = x;
    x = y;
    y = temp;

    return;
}
```

- 传引用的在调用的时候把value绑定在一起，效率高过传值，但是不可以设置默认值

```cpp
// 传引用, 下面main函数调用的时候，a,x   b, y 的数据是绑定在一起的
void swap_reference(int& x, int& y) {
    int temp;
    temp = x;
    x = y;
    y = temp;
    return;
}
```

- 指针: 本身的size是很小的，指向具体对象的地址
	- 可以通过指针找到或者修改一个对象的值，实现访问和修改的功能
	- // 类型 int float map vector 
	- // & * ** const static --> 饰词 
	- int* a = 10; 的意思是a 是一个int型，同时是一个指针 
- 指针和引用起到的效果看起来差不多
	- 引用要确实传入确定的变量，但是指针可以传一个空指针，空指针可以编译成功，但是会有一个segmentation fault 
	- 引用也可以理解为是包了一个指针，他自己会检查是不是都有效
	- 下面的demo包含了传值， 传指针，传引用
	
```cpp
// 类型 int float map vector 
// & * ** const static --> 饰词 
void swap_ptr(int* x, int* y){
    int temp = *x;
    *x = *y;
    *y = temp;
    return;
}
```
完整版的代码如下
```cpp
#include <iostream>

// 传值 值的传递，复制一份value, 下面main函数调用的时候只是把value复制了一份传过来
// 效率是低的
void swap_value(int x = 5, int y = 10) {
    int temp;
    temp = x;
    x = y;
    y = temp;

    return;
}

// 传引用, 下面main函数调用的时候，a,x   b, y 的数据是绑定在一起的
void swap_reference(int& x, int& y) {
    int temp;
    temp = x;
    x = y;
    y = temp;
    return;
}

// 类型 int float map vector 
// & * ** const static --> 饰词 
void swap_ptr(int* x, int* y){
    int temp = *x;
    *x = *y;
    *y = temp;
    return;
}

int main() {
    int a = 300, b = 500;
    // swap_value(a, b);   
    // std::cout << "swap_value value a is: " << a << std::endl;
    // std::cout << "swap_value value b is: " << b << std::endl;
    // swap_reference(a, b);
    // std::cout << "swap_reference value a is: " << a << std::endl;
    // std::cout << "swap_reference value b is: " << b << std::endl;
    swap_ptr(&a, &b);
    std::cout << "swap_ptr value a is: " << a << std::endl;
    std::cout << "swap_ptr value b is: " << b << std::endl;
    return 0;
}
```

## 函数默认参数的注意事项
- 函数的默认参数从左向右，如果一个参数设置了默认参数，那么这个参数之后的参数都必须设置默认参数。
- 如果函数声明和函数定义分开写，函数声明和函数定义不能同时设置默认参数
```cpp
//注意点:
//1. 形参b设置默认参数值，那么后面位置的形参c也需要设置默认参数
void TestFunc02(int a,int b = 10,int c = 10){}
//2. 如果函数声明和函数定义分开，函数声明设置了默认参数，函数定义不能再设置默认参数
void TestFunc03(int a = 0,int b = 0);
void TestFunc03(int a, int b){}
```
## lambda函数
-  一个lambda的案例
	

```cpp
 [捕获](传参){具体的实现}
```
- 捕获外界变量怎么用 

```cpp
#include <iostream>

void lambda_demo_a() {
    int y = 0;
    int z = 11;
    // 一个lambda的案例 [捕获](传参){具体的实现}
    auto a_lambda_func = [z, &y](int x){
        y = 2 * x;
        return y;
    };
    // 调用之前写好的lambda函数
    std::cout << "lambda demo value: " << a_lambda_func(5) << std::endl;
    return;
}

int main() {
    lambda_demo_a();
    return 0;
}
```
# 2. 内联函数
- **先看看宏**
## 宏的定义
- 在c中我们经常把一些短并且执行频繁的计算写成宏，而不是函数，这样做的理由是为了执行效率，宏可以避免函数调用的开销，这些都由预处理来完成。
```cpp
#define ADD(x, y) x + y 

void macro_demo()
{
    int ret1 = ADD(10, 20) * 10;
    cout << ret1 << endl;
}
```
- 为什么最终的执行结果是210而不是300呢？原因就是宏定义在预处理的时候是文本替换，所以ret1 = ADD(10, 20) * 10;被展开后就变成了：ret1 = 10+20*10
- 内联函数为了继承宏函数的效率，没有函数调用时开销，然后又可以像普通函数那样，可以进行参数，返回值类型的安全检查，又可以作为成员函数
## 内联函数的定义
- 在c++中，预定义宏的概念是用内联函数来实现的，而**内联函数本身也是一个真正的函数** 。内联函数具有普通函数的所有行为。唯一不同之处在于内联函数会在适当的地方像预定义宏一样展开，所以不需要函数调用的开销。因此应该不使用宏，使用内联函数

- 在普通函数(非成员函数)函数前面加上inline关键字使之成为内联函数。但是必须注意必须函数体和声明结合在一起，否则编译器将它作为普通函数来对待。
- ```cpp inline void func(int a); ```
- 以上写法没有任何效果，仅仅是声明函数，应该如下方式来做:
- ```cpp inline int func(int a){return ++a;} ```
- 注意: 编译器将会检查函数参数列表使用是否正确，并返回值(进行必要的转换)。这些事预处理器无法完成的。
### 内联函数注意事项

- C++中推荐使用内联函数替代宏代码片段

- 内联函数在最终生成的代码中是没有定义的，C++编译器直接将函数体插入在函数调用的地方，内联函数没有普通函数调用时的额外开销(压栈，跳转，返回)

- 因为内联函数在最终生成的代码中是没有定义的，所以内联函数的作用域可以理解为只在定义的文件内。假如在a.cpp中定义了inline int func(int a){return ++a;}，如果在b.c中需要调用func函数则在b.cpp中需要重新定义内联函数inline int func(int a){return ++a;}

- inline只是对编译器的一个内联请求，c++内联编译会有一些限制，以下情况编译器可能考虑不会将函数进行内联编译：

> 存在任何形式的循环语句
>
> 存在过多的条件判断语句
>
> 函数体过于庞大
>
> 对函数进行取址操作

- 因此， **内联仅仅只是给编译器一个建议，编译器不一定会接受这种建议，如果你没有将函数声明为内联函数，那么编译器也可能将此函数做内联编译。一个好的编译器将会内联小的、简单的函数。**
## 函数默认参数的注意事项
- 函数的默认参数从左向右，如果一个参数设置了默认参数，那么这个参数之后的参数都必须设置默认参数。
- 如果函数声明和函数定义分开写，函数声明和函数定义不能同时设置默认参数
```cpp
//注意点:
//1. 形参b设置默认参数值，那么后面位置的形参c也需要设置默认参数
void TestFunc02(int a,int b = 10,int c = 10){}
//2. 如果函数声明和函数定义分开，函数声明设置了默认参数，函数定义不能再设置默认参数
void TestFunc03(int a = 0,int b = 0);
void TestFunc03(int a, int b){}
```

## **实现函数重载的条件**

* 同一个作用域
* 参数个数不同
* 参数类型不同
* 参数顺序不同
 ```cpp
void func(){}
void func(int x){}
void func(char x){}
void func(int x, int y){}
void func(int x, char y){}
void func(char y, int x){}
 ```
# 3. 数组
- 所谓数组就是一个集合，里面存放了相同类型的数据元素，连续的内存位置组成的
- 数组是可以写超的，设置的是10个，也可以遍历他第11个，他也能写出来，但是数值是不可控的
- C++可以直接操作内存，C++是连续的内存，所以我们拿到的是后面的值
- 不能像python一样全部展示出来

```cpp
void array_demo() {
    int n[10]; // 定义一个数组， 是一个包含10个整数的数组
    // 初始化数组元素, 101 - 109
    for (int i = 0; i < 10; i ++) {
        n[i] = i + 100;
    }

    // Element 之后的到value最后的e占据13个
    cout << "Element" << setw(9) << "Value" << endl;
    // 输出数组中每个元素的值
    for (int j=0; j < 11; j++) {
        cout << setw(7) << j << setw(13) << n[j] <<endl;
    }
}
```
- 数组和指针的关系
- 数组就是一个指向第一个元素的指针
- 下面是实验展示，两个指针地址一样，都可以通过地址+1的方式拿出数组的数据
- 这里的(p + 1) (array + 1 ) 都是指针的地址  *(地址 取出元素)
```cpp
// 数组和指针的关系
// 数组和指针的关系
void array_ptr() {
    double array[5] = {11, 21, 31, 41, 51}; 
    double* p;
    p = array;
    cout << "p的地址" << p << endl;
    cout << "array的地址" << array << endl; 
    cout << "索引"  << setw(13) << "数值" << endl;
    for (int i = 0; i < 5; i++) {
        // 两个一样的，这里的(p + 1) (array + 1 ) 都是指针的地址  *(地址 取出元素)
        // cout << setw(2) << i << setw(12) << *(p + i) << endl;  
        cout << setw(2) << i << setw(12) << *(array + i) << endl;
    }
}
```
# 4. C风格的字符串
- 因为C风格的字符串后面有个0\所以定义字符串的时候要 + 1 个单位

```cpp
void str_len() {
    char str1[4] = "Asd";
    cout << str1 << endl;
}
```
# 数组，C风格的字符串的完整版代码

```cpp
#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;
using std::setw;

void array_demo() {
    int n[10]; // 定义一个数组， 是一个包含10个整数的数组
    // 初始化数组元素, 101 - 109
    for (int i = 0; i < 10; i ++) {
        n[i] = i + 100;
    }

    // Element 之后的到value最后的e占据13个
    cout << "Element" << setw(9) << "Value" << endl;
    // 输出数组中每个元素的值
    for (int j=0; j < 11; j++) {
        cout << setw(7) << j << setw(13) << n[j] <<endl;
    }
}

// 数组和指针的关系
void array_ptr() {
    double array[5] = {11, 21, 31, 41, 51}; 
    double* p;
    p = array;
    cout << "p的地址" << p << endl;
    cout << "array的地址" << array << endl; 
    cout << "索引"  << setw(13) << "数值" << endl;
    for (int i = 0; i < 5; i++) {
        // 两个一样的，这里的(p + 1) (array + 1 ) 都是指针的地址  *(地址 取出元素)
        // cout << setw(2) << i << setw(12) << *(p + i) << endl;  
        cout << setw(2) << i << setw(12) << *(array + i) << endl;
    }
}

void str_len() {
    char str1[4] = "Asd";
    cout << str1 << endl;
}
int main() {
    // array_demo();
    // array_ptr();
    str_len();
    return 0;
}
```

