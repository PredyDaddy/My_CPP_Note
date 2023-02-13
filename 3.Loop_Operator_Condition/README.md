# 知识点
- cpp里面会经常查看数据类型的大小，python倒不会用太多这些东西
- 条件符号
- 类型模版
- 结构体，指针类型， &在等号左边是取引用，在等号右边是取地址，这里是取地址
- C语言的强转类型
- 引用的案例
- 指针案例

```cpp
#include <iostream>
#include <math.h>

// 查看类型的size demo
// 变量和类型的大小size一样
void size_of_demo() {
    int a = 1000000;
    std::cout << "size int: " << sizeof(int) << std::endl;
    std::cout << "size a: " << sizeof(a) << std::endl;
    return;
}

// 条件符号demo
int condition_demo(int a) {
    int b = (a == 5) ? 5 : 0;
    return b;
}

// 类的模板  
void comma_demo() {
    // 模板类
    // typedef std::pair<float, float> pointer;
    float x;
    std::pair<float, float> y = {x = 2.7, sqrt(x)};   // 改成pointer就行了
    std::cout << "Second value of y is: " << y.second << std::endl;
    }

// 结构体，指针demo
struct Conv
{
    int pad = 0;
    int stride = 1;
};

void point_demo(){
    Conv conv;
    conv.pad = 10;
    std::cout << "pointer demo pad result is :" << conv.pad << std::endl;
    // 指针
    Conv* conv_2 = &conv;  // 指针类型， &在等号左边是取引用，在等号右边是取地址，这里是取地址
    std::cout << "pointer demo stride result is :" << conv_2 ->stride << std::endl;
    conv_2 ->stride = 100;
    std::cout << "pointer demo stride result is :" << conv_2 ->stride << std::endl;
    return;
}

// 类型转换，C，C++的不同
// C++ 有四种专门的类型转换
void cast_demo() {
    float a = 3.3;
    // C语言的强转类型
    std::cout << "value a: " << (int)a << std::endl;
    return;
}

// 引用的demo 
void reference_demo(){
    int a = 10;
    int b = a;
    b = 20;
    // 这里的a还是10
    std::cout << "First try of reference demo result: " << a << std::endl;

    // &在左边引用,这里的a变成了20， 这里c跟a的地址绑定了，相互共享了，不会建立出另外一个数据
    int& c = a;
    c = 20;
    std::cout << "Second try of reference demo result: " << a << std::endl;
}

void ptr_demo(){
    int a = 10;
    int* b = &a;
    std::cout << "ptr demo result is: " <<  (*b) << std::endl;
    // 更改b也是去到a的地方更改
    *b = 6;
    std::cout << "ptr demo result is: " <<  a << std::endl;
}


int main(){ 
    // size_of_demo();
    // std::cout << "result of condition_demo 1: " << condition_demo(5) << std::endl;
    // std::cout << "result of condition_demo 2: " << condition_demo(9) << std::endl;
    // comma_demo();
    point_demo();
    // cast_demo();
    // reference_demo();
    // ptr_demo();
    return 0;
}
```

- 配置cmake

```bash
cmake_minimum_required(VERSION 3.16) # cmake版本限制
project(operator_demo)  # 项目名

set(CMAKE_CXX_STANDARD 14) # cpp 版本

add_executable(operator_demo operator_demo.cpp) # 编译成可执行文件
```

- 循环
- while for 用的比较多
- do_while, goto用的很少了

```cpp
# include <iostream>

// while 循环
// 到19停下来，到不了20
void while_demo(){
    int a = 10;
    while (a < 20) {
        std::cout << "value a: " << a << std::endl;
        ++a;
    }
}

void for_demo(){
    for (int a = 10; a < 20; ++a) {
        std::cout << "value a: " << a << std::endl;
    }
}

// 用的很少
void do_while_demo(){
    int a = 10;
    do { 
        std::cout << "value a: " << a << std::endl;
        ++a;
    }while (a < 20);
}

// 用的更少，汇编的时候容易引起混乱，但是也保留下来了
void goto_demo() {
    int a = 10;
    LOOP: do {
        //     if (a == 16) {
        //     ++a;
        //     goto LOOP;
        // }
        std::cout << "goto demo value: " << a << std::endl;
        ++a;
    }while (a < 20);
}

int main() {
    // while_demo();
    // for_demo();
    // do_while_demo();
    goto_demo();
    return 0;
}
```
- 配置cmake

```cpp
cmake_minimum_required(VERSION 3.16) # cmake版本限制
project(operator_demo)  # 项目名

set(CMAKE_CXX_STANDARD 14) # cpp 版本

add_executable(loop_demo loop_demo.cpp) # 编译成可执行文件
```
# 条件判断

```cpp
#include <iostream>

// 不加break会一直往下执行所有的case 
void switch_case_demo(char grade) {
    // char grade = 'D';
    switch(grade) {
        case 'A':
            std::cout << "very good" << std::endl;
            break; // break 
        case 'B': // 执行下一个case
        case 'C':
            std::cout << "passed" << std::endl;
            break;
        case 'D':
            std::cout << "failed" << std::endl;
            break;
        default:
            std::cout << "Invaild" << std::endl; 
            break;
    } 
}

void condition_demo() {
    int x, y = 10;
    int a = 55;
    // x = (y < 10) ? 30: 4; 

    if (y < 10) {
        x = 30;
    }
    else if (a = 55) {
        x = 200;
    }
    else {
        x = 4;
    }
    std::cout << "x value is: "<< x << std::endl;
}

int main() {
    // char grade = 'B';
    // switch_case_demo(grade);
    condition_demo();
    return 0; 
}
```
