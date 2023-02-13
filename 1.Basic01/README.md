# C++ 笔记(一):环境配置和基础语法: 变量_命名空间_引用

# 1.环境配置
## 在Ubuntu中Vscode配置环境
- 安装Ubuntu, 这里可以用服务器，wsl等等，我是两个都用过，操作没有任何区别
- -　分别执行下面代码内容，安装g++, gdb

```cpp
sudo apt-get update
sudo apt-get install g++
sudo apt-get install gdb
```
- 在Vsocde下面安装C/C++拓展插件
－配置lanuch.json

```cpp
{
  "version": "0.2.0",
  "configurations": [
      {
          "name": "C/C++",
          "type": "cppdbg",
          "request": "launch",
          "program": "${fileDirname}/${fileBasenameNoExtension}",
          "args": [],
          "stopAtEntry": false,
          "cwd": "${workspaceFolder}",
          "environment": [],
          "externalConsole": false,
          "MIMode": "gdb",
          "preLaunchTask": "compile",
          "setupCommands": [
              {
                  "description": "Enable pretty-printing for gdb",
                  "text": "-enable-pretty-printing",
                  "ignoreFailures": true
              }
          ]
      }
  ]
}

```
- 配置task.json

```cpp
{
  "version": "2.0.0",
  "tasks": [
    {
      "label": "compile",
      "command": "g++",
      "args": [
        "-g",
        "${file}",
        "-o",
        "${fileDirname}/${fileBasenameNoExtension}"
      ],
      "problemMatcher": {
        "owner": "cpp",
        "fileLocation": [
          "relative",
          "${workspaceRoot}"
        ],
        "pattern": {
          "regexp": "^(.*):(\\d+):(\\d+):\\s+(warning|error):\\s+(.*)$",
          "file": 1,
          "line": 2,
          "column": 3,
          "severity": 4,
          "message": 5
        }
      },
      "group": "build"
    },
    {
      "type": "cppbuild",
      "label": "C/C++: g++ 生成活动文件",
      "command": "/usr/bin/g++",
      "args": [
        "-fdiagnostics-color=always",
        "-g",
        "${file}",
        "-o",
        "${fileDirname}/${fileBasenameNoExtension}"
      ],
      "options": {
        "cwd": "${fileDirname}"
      },
      "problemMatcher": [
        "$gcc"
      ],
      "group": {
        "kind": "build",
        "isDefault": true
      },
      "detail": "调试器生成的任务。"
    }
  ]
}
```
## C++ 编译
- 写个简单的程序, 终端输入，vim a.cpp 

```cpp
# include <iostream>

int main() {
  printf("Hello World\n");
  return 0;
}
```
- 编译写过的a.cpp
```cpp
g++ a.cpp
g++ a.cpp -o a.bin
```
- 目录会多出一个a.out/a.bin, 终端输入./a.out  ./a.bin 就可以直接执行这个文件了

## 查看一下动态库
- 我们写代码最终交付的时候是可执行文件，静态库，动态库
- 静态库以 *a, *lib 格式出现
- 动态库以 *.so *ddl 格式出现，为了让可执行文件调用的
```cpp
ldd a.out
ldd a.bin
```

```cpp
        linux-vdso.so.1 (0x00007ffdb83c8000)
        libstdc++.so.6 => /usr/lib/x86_64-linux-gnu/libstdc++.so.6 (0x00007f4a5ee0e000)
        libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f4a5ea1d000)
        libm.so.6 => /lib/x86_64-linux-gnu/libm.so.6 (0x00007f4a5e67f000)
        /lib64/ld-linux-x86-64.so.2 (0x00007f4a5f399000)
        libgcc_s.so.1 => /lib/x86_64-linux-gnu/libgcc_s.so.1 (0x00007f4a5e467000)
```
- 交付的时候，如果是给静态库是比较方便的，什么都编译到了a.out / a.bin里面了
- 虽然给静态库是比较方便的，但是什么都编译进去会导致可执行文件太大，所以一般是交付动态库 + 可执行文件(.bin)

# 2. C++基本概念
-  调用内部库时候使用
```cpp
#include <>
```
- 自己写的.h 文件时候使用

```cpp
#include "*.h" 
```
- <> 先去标准库里面找头文件
- "aa.h" 先从当前目录里面去查找
- namespace概念: <> 标准命名空间 std, 我们写程序也会包在标准命名空间里面
- 尽量一定不要在头文件(aaa.h)中使用using namespace std; 
- 有main函数的时候，main() --> 可执行文件
- #define a = 10, 简单的宏指令，C++宏指令都是以#开头，代码替换
- 多行注释:  /*   */
- C++是强类型语言，定义任何变量的时候，包括函数参数，都必须指定类型，auto让C++自己猜，型别推导，有的时候命名空间嵌套  A: : B : : C, 自己推导，不过有些同事非常不喜欢
- int 函数必须有返回值，没有返回值用void代替
- {} 来定义代码块
- Coding Style 在每一个项目开发前一定要定下来，空格是多少个，大括号什么的，代码规范性很重要

## 不同后缀文件的意义
- cpp: 里面写函数的实现
- .h: 变量， 函数，类的声明
- *hpp: 声明函数放到一起了
- 头文件的概念: 函数，类的声明
- 声明和定义在CPP里面一般都是分开写的
## 缓冲区
- cout是c++中的标准输出流，endl是输出换行并刷新缓冲区。
- C++ 中的缓冲区是一种内存区域，用于在读写操作过程中缓存数据。它可以加速读写操作的速度，减少系统调用的次数，提高程序的效率。常见的缓冲区有输入缓冲区和输出缓冲区。C++ 中的流类，如 std::cout 和 std::fstream，都有自己的缓冲区。缓冲区可以由程序员手动清空或刷新。

# 3. 变量的基础语法
## 条件编译
相当于多行注释，
```cpp
#include <iostream>


#if 0
using namespace std;
int main() {
  // auto a = add(1, 2);
  printf("Hello World\n");
  return 0;
}
#endif
```
## 变量基础

- 全部的变量可以尽可能的往前面写(如果你想要口头警告也可以的)
- static修饰局部变量的时候: 告诉编译器这个变量在程序的整个生命周期存在，这样后面就不好访问了
- static修饰全局变量的时候，使得该变量的作用域仅作为当前文件


- 外部写一个var.cpp 

```cpp
#include <iostream>

// 定义宏
#define LENGTH 11
#define WIDTH 5
#define NEWLINE '\n'

//只能在这个cpp文件里面使用
const static int k_lenth = 8;

using namespace std;

//没有返回的函数
void define_demo() {
    int area = LENGTH * WIDTH;
    cout << area << endl;
}

int main() {
    define_demo();
    return 0;
}
```
- 外部写一个var.cpp 

```cpp
// 全局变量，声明和定义要放在一起
int a = 10, b = 20, c = 30;
```

```cpp
#include <iostream>

// 定义一次，声明多次
extern int a;

int main() {
	std::cout << "a is: " << a << std::endl;
	return 0;
}
```

- 如果不定义，全局变量默认是0， 局部变量随便来了
- 当局部变量被定义时，系统不会对其初始化，您必须自行对其初始化
- 局部变量最好有的默认值


```cpp
#include <iostream>

extern int a;

int b;

void local_var_demo() {
  int a;
  // a = 10;
  std::cout << "local value a is: " << a << std::endl;
}

int main() {
  local_var_demo();
	// std::cout << "a is: " << a << std::endl;
  std::cout << "global value b is: " << b << std::endl;
	return 0;
}
```

```cpp
local value a is: 21845
global value b is: 0
```


## Typedef 
- Rename: using feet = int; 或者 typedef int feet; 
-  这样feet a = 9; 就可以隐藏我们的数据类型了，在展示的时候比较好用

```cpp
#include <iostream>

// tydef 方法
void typedef_demo()
{
  typedef int asd;
  asd a = 10.1;
  std::cout << "a is " << a << std::endl;
  return;
}

// using method
void using_type_demo()
{
  using sss = float;
  sss b = 10;
  std::cout << "b is " << b << std::endl;
}
int main()
{
  typedef_demo();
  using_type_demo();
  return 0;
}
```

```cpp
a is 10
b is 10
```

## 枚举法

- 枚举类型: c++是一个强类型的语言，枚举类型可以给很多种数据类型一种分类
	- 枚举类型不能直接输出。需要将其转换为 int 类型才能输出
	- 下面提供两种枚举的转换方法
	- 自动延续，下面的Wed自动顺位成3
	- 枚举类型不能直接输出到控制台。在这种情况下，您需要使用static_cast将枚举类型转换为整数类型，然后才能输出

```cpp
#include <iostream>
using namespace std;

enum class Week {
  Mon = 1,
  Tue = 2,
  Wed,
};


int main() {
  Week a = Week::Mon;
  auto b = (int)(a);
  Week c = Week::Wed;
  std::cout << "a is : "  << static_cast<int>(a) << std::endl;
  std::cout << "b is : " << b << std::endl;
  std::cout << "c is : " << static_cast<int>(c) << std::endl;
  return 0;
}
```

```cpp
a is : 1
b is : 1
c is : 3
```
- 再来个例子，int强转类型
```cpp
#include <iostream>
using namespace std;

// 加class, class相当于一个namespace
enum class OpType {
AveragePoo1,
BatchNormalization,
Concat ,
Conv,
Dropout,
Flatten ,
Gemm ,
Matmul,
MaxPool
};

void enum_demo(){
  OpType conv = OpType::Conv;
  std::cout << "conv is " << int(conv) << std::endl;
  return;
}

int main() {
  enum_demo();
  return 0;
}
```

## 变量的声明，定义
- 当您使用多个文件且只在其中一个文件中定义变量时（定义变量的文件在程序连接时是可用的），变量声明就显得非常有用。您可以使用 extern 关键字在任何地方声明一个变量。虽然您可以在 C++ 程序中多次声明一个变量，但变量只能在某个文件、函数或代码块中被定义一次。



```cpp
#include <iostream>
using namespace std;
 
// 变量声明
extern int a, b;
extern int c;
extern float f;
  
int main ()
{
  // 变量声明
  int a, b;
  int c;
  float f; 
 // 实际初始化
  a = 10;
  b = 20;
  c = a + b;
 
  cout << c << endl ;
 
  f = 70.0/3.0;
  cout << f << endl ;
 
  return 0;
}

```
- 类的声明经常是放在一个.h, 定义是在.cpp里面
- .h文件也能够把声明和定义都放在一起但是这样违反了.h文件轻量化的需求

## 变量作用域

```cpp
#include <iostream>
using namespace std;
 
// 全局变量声明
int g = 20;
 
int main ()
{
  // 局部变量声明
  int g = 10;
 
  cout << g;
 
  return 0;
}
```
## 定义C++中的常量
- #define 定义的宏要大写，这样下面看到马上就知道他是个宏
- 用宏变量可以快速的修改全部文件中的变量，只用在头文件定义一次
- 如果你想在中间改宏的变量，就定义两个宏，不要破坏代码的可维护性
- 宏定义

```cpp
#include <iostream>
using namespace std;
 
#define LENGTH 10   
#define WIDTH  5
#define NEWLINE '\n'
 
int main()
{
 
   int area;  
   
   area = LENGTH * WIDTH;
   cout << area;
   cout << NEWLINE;
   return 0;
}
```
- const 
- 优化，把变量从内存放到寄存器里面去加快读写效率(速度: 硬盘 < 内存 < 寄存器(直接跟计算单元打交道))
- 下面这个案例来自于菜鸟，这个案例不好，变量是大写的

```cpp
#include <iostream>
using namespace std;
 
int main()
{
   const int  LENGTH = 10;
   const int  WIDTH  = 5;
   const char NEWLINE = '\n';
   int area;  
   
   area = LENGTH * WIDTH;
   cout << area;
   cout << NEWLINE;
   return 0;
}
```
# 3. 命名空间
## 命名空间的定义
```cpp
namespace name
{
    // 定义变量，函数，类型，对象....
}
```

## 命名控件成员的访问
```cpp
// 命名空间成员的访问
namespace A
{
    int a = 10; 
}
namespace B
{
    int a = 20;
}

void namespace_test() 
{
    std::cout << "namespace A::a is:" << A::a << std::endl;
    std::cout << "namespace B::a is:" << B::a << std::endl;
}
```
## 命名空间只能在全局范围内定义，不能嵌套在函数里面！！！
## 命名控件的嵌套定义
```cpp
namespace C
{
    int a = 10;
    namespace D 
    {
        int a = 20;
    }
}

void namespace_test() 
{
    std::cout << "namespace C::a is:" << C::a << std::endl;
    std::cout << "namespace C::D::a is:" << C::D::a << std::endl;
}
```
## 命名空间的声明和实现分开
```cpp
void E::func1() {
    std::cout << "This is namespace E::func1()" << std::endl;
}

void E::func2(int a)
{
    std::cout << "namespace E::func2: " << a << std::endl;
}

void namespace_test() 
{
    E::func1();
    E::func2(5);
}
```
## 命名空间别名
### 别名不是改名，nameA nameB 都可以用
```cpp
namespace nameA
{
    int a = 15;
    void func1(){
        std::cout << "This is nameA::func1()" << std::endl;
    }
}

void namespace_test() 
{
    namespace nameB = nameA;
    std::cout << "nameB::a: " << nameB::a << std::endl;
    nameA::func1();
}
```
## 自己的命名空间
- 不用非得写在一起的
- 后面加上注释
```cpp
#include <iostream>

namespace asd{
  int a = 100;
} // namespace asd

namespace asd{
  int c = 999;
} // namespace asd

int main()
{
  std::cout << "a is " << asd::a << std::endl;
  std::cout << "c is " << asd::c << std::endl;
  return 0;
}
```
## 声明一个命名空间
- 新建一个head_demo.h文件

```cpp
#ifndef HEAD_DEMO_H_
#define HEAD_DEMO_H_

namespace space_demo {
  int a = 10;
  int b = 30;
}


#endif
```
- main.cpp文件加上.h就能用了
- 下面展示两种访问方法

```cpp
#include <iostream>
#include "head_demo.h"

namespace space_demo {
  void namespace_demo() {
    std::cout << "namespace demo b is " << b << std::endl;

  }
}
int main(){
  // 外部访问需要声明他的命名空间
  std::cout << "value b is: " << space_demo::b << std::endl;

  //内部访问不需要声明命名空间
  space_demo::namespace_demo();   
  return 0;
}
```

```cpp
value b is: 30
namespace demo b is 30
```

# 4. 引用
## 引用的基本概念
- 引用可以看作一个**已定义变量的别名**
- 引用的语法：**Type&   name = var;**
- 引用的注意事项: 
  - &不是求地址运算，而是起标识运算
  - 类型标识符是指目标变量的类型
  - 必须在声明引用变量的时候初始化
  - 引用只能在定义时初始化一次，之后不能改变指向其它变量（从一而终）
  - 不能有NULL引用。必须确保引用是和一块合法的存储单元关联
## 引用的使用
- **操作别名就是操作指向的变量本身**
- **一个变量可以有无数个别名，他们都指向一个地址**
```cpp
void test1() 
{
    int a = 10;
    int& b = a; // 等于给变量a取了一个别名b
    std::cout << "a is: " << a << std::endl;
    std::cout << "b is: " << b << std::endl;
    std::cout << "----------------------------" <<std::endl;
    // 操作b就是操作a本身
    b = 200;
    std::cout << "a is: " << a << std::endl;
    std::cout << "----------------------------" <<std::endl;
    // 一个变量可以有无数个别名
    // 操作一个就是操作了全部
    int& c = a;
    std::cout << "a is: " << a << std::endl;
    std::cout << "b is: " << b << std::endl;
    std::cout << "c is: " << c << std::endl;
    std::cout << "----------------------------" <<std::endl;
    // 他们的地址都是相同的
    std::cout << "地址a: " << &a << std::endl;
    std::cout << "地址b: " << &b << std::endl;
    std::cout << "地址c: " << &c << std::endl;
}
```
## 引用的注意事项案例
- 必须初始化
- 下面案例中: 初始化了一个整型引用ref，它指向变量a。当ref = b执行时，不是改变b的值，而是改变了a的值，因为引用ref实际上指向的就是变量a的内存地址。所以最终的输出a is: 20。
```cpp
void test2() 
{
    // 引用必须初始化
    // int& c;  这样会报错,必须初始化引用
    int a = 10;
    int b = 20;
    int& ref = a;
    ref = b; 
    std::cout << "a is: " << a << std::endl;
}
```
## 引用的本质
- **引用的本质在c++内部实现是一个常指针.**
```cpp
Type& ref = val; // Type* const ref = &val;
```
- c++编译器在编译过程中使用常指针作为引用的内部实现，因此**引用所占用的空间大小与指针相同**，只是这个过程是编译器内部实现，用户不可见。
```cpp
void test3()
{
    int a = 10;
    int& ref = a; // 自动转换为 int* const ref = &a; 
    ref = 20;
    std::cout << "a is: " << a << std::endl; 
}
```
- 验证引用占用内存空间大小：
```cpp
// 验证引用占内存空间的大小
struct test_size 
{
    int &a;
    int &b;
    int &casdasd;
};

void test4()
{
    std::cout << sizeof(test_size) << std::endl;
}
```
- 上面这段代码是错误的，但是运行没有报错
- 在结构体定义里面定义了引用，但是没有对引用进行初始化，那么当这个结构体在使用的时候就会报错。这是一个常见的编译错误。你的代码只输出了结构体的大小，所以在编译的时候没有发现错误，但是当你真正使用这个结构体的时候，就会报错。

##　引用作为函数的参数
- 普通引用在声明时必须用其它的变量进行初始化，引用作为函数参数声明时不进行初始化
- 下面案例展示了指针和引用的两种写法
```cpp
struct Teacher
{
   char name[64];
    int age; 
};

// 引用的案例
void print1(Teacher &ref)
{
    cout << "reference age is: " << ref.age << endl;
}

// 指针的案例
void print2(Teacher *ptr)
{
    cout << "ptr age is: " << ptr->age << endl;
}

void test5()
{
    Teacher t1;
    t1.age = 35;
    // 引用案例
    print1(t1);
    // 指针的案例，指向结构体的指针
    // 传入指向结构体的指针时需要使用 &t1 来获取指针
    print2(&t1);
}
```
## 引用的意义
- 一些场合代替指针，有着更好的可读性和实用性
- 案例: 交换swap的指针写法和引用写法
```cpp
void swap1(int& a, int& b)
{
    int t = a;
    a = b;
    b = t;
    cout << "swap1() " << endl;
    cout << "a is: " << a << endl;
    cout << "b is: " << b << endl;
}

void swap2(int* a, int*b)
{
    int t = *a;
    *a = *b;
    *b = t; 
    cout << "swap2() " << endl;
    cout << "a is: " << *a << endl;
    cout << "b is: " << *b << endl;
}

void test5()
{
    int a = 10;
    int b = 20;
    swap1(a, b);

    // 用&获取a, b的地址才可以赋值给指针变量a, b
    // 之前换了，这里换回来
    int* c = &a;
    int* d = &b;
    swap2(c, d);
}
```