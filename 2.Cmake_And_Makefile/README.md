
# Makefile 
跟着打一遍，写完了就知道C++是如何工作的，最强Makefile教程
https://zhuanlan.zhihu.com/p/396448133 


# cmake
- CMake是一个开源的构建系统，它可以自动生成各种各样的构建系统的文件，如Makefile或者Visual Studio工程文件。这样，程序员就可以不必担心不同平台和编译器之间的差异，只需要编写一份CMakeLists.txt文件即可。
- CMake还可以用来管理项目依赖关系和自动检测系统上是否有所需的库。
- CMake适用于跨平台的C++项目，可以在Windows, Linux, MacOS
# 代码展示
- 用这个帖子安装最新版本的cmake，成功了 https://zhuanlan.zhihu.com/p/519732843
- 动态库 + 头文件 交付给客户，具体的实现放到动态库里面，头文件可以告诉客户输入输出是怎么样的
- 头文件就是一个接口，也是我们常说的API，Pytorch里面调用英伟达的程序，其实就是调用他们头文件的API
- 一个简单的项目结构
![在这里插入图片描述](https://img-blog.csdnimg.cn/8879d050bf994b9a8719a3d5aca116fc.png)

- build文件夹用于源码编译，去到build文件夹`cmake ..` ，`make -j8`去到上一个文件夹中找CMakeList.txt的文件开始编译代码
- build会生成很多跟文件无关的文件
- demo 是客户写代码的地方
- include文件夹放着*.h文件	(自己写的)，里面就是接口，写上注释告诉客户这个拿来干嘛的，传什么参数，他就可以用了
- lib里面放动态库(后面会帮我们生成的)
- src 源文件的文件夹中放着开发人员写的代码
- README.md用于给客户解释代码的地方
- 下面是一个简单的Cmake_demo 

```bash
cmake_minimum_required(VERSION 3.16)  # cmake 版本限制
project(dynamic_lib_demo)  # 项目名

set (CMAKE_CXX_STANDARD)   # cpp 版本

include_directories(${CMAKE_SOURCE_DIR}/include)       # 头文件存放路径
link_directories(${CMAKE_SOURCE_DIR}/lib)              # 动态库存放路径
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)       # 动态库的存放路径，不指定默认放在build的下面
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/demo)   # 可执行文件的存放路径

file(GLOB so_file src/*.cpp)       # 用一个变量表示src文件夹下面全部的.cpp文件
message(STATUS "so_file_path :${so_file}")  # 打印信息 链接的时候包含那些.cpp文件
add_library(hello_dynamic SHARED ${so_file}) # 编译动态库 名字是 libhello_dynamic.so   前面会自动加一个lib
# add_library(hello_dynamic STATIC ${so_file}) # 编译成静态库

add_executable(main.bin demo/main.cpp)   # 编译成可执行文件，可写多个
add_executable(main_1.bin demo/main_1.cpp) 
target_link_libraries(main.bin PRIVATE hello_dynamic)  # 将动态库链接到可执行文件， 可多写
target_link_libraries(main_1.bin PRIVATE hello_dynamic)  # 将动态库链接到可执行文件， 可多写
```
- 为什么用PRIVATE不是PUBLIC，因为层次多了容易出问题，有的时候src文件夹下面还会有文件夹，.h,cmake文件等等
- 这个时候做一个尝试，把lib里面的动态库文件挪出来会有什么问题
- `mv ../lib/libhello_dynamic.so ../`   把动态库放出来, main.bin 就找不到动态库执行不了了
- SHARED 是动态库，STATIC是静态库
- 如果编译成静态库，即使是删除了或者移动了/libhello_dynamic.a文件都没有问题, 可以理解为静态库被包含在main.bin里面了
- 可以编译两次用ls -l去查看main.bin的大小,静态库大于动态库
动态库编译
```bash
 ls ../demo/ -l    
total 40
-rwxrwxr-x 1 cqy cqy 13224 Jan 12 22:45 main_1.bin
-rw-rw-r-- 1 cqy cqy   248 Jan 12 21:11 main_1.cpp
-rwxrwxr-x 1 cqy cqy 13224 Jan 12 22:45 main.bin
-rw-rw-r-- 1 cqy cqy   248 Jan 12 21:11 main.cpp
```
把可执行文件改名复制到/usr/bin 下面，把可执行文件变成像ls rm cd一样的操作

```bash
mv main.bin time_stamp
sudo cp time_stamp /usr/bin
time_stamp
```
