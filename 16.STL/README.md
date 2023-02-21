# 1. STL 概念
1. C++ STL 是指 C++ Standard Template Library，是一套标准的 C++ 模板类库。它提供了一系列的容器类（如向量、队列、列表、集合等等）、算法（如排序、查找、删除、替换等等）以及迭代器等重要组件，可以大大提高程序的开发效率和代码质量。

2. STL 的出现是为了简化 C++ 中复杂数据类型的处理，并提供高效、灵活、通用、可重用的代码实现。它不仅可以避免代码重复编写，还可以增加代码的可读性、可维护性和可扩展性。

3. STL 是 C++ 标准库的一部分，使用 STL 需要包含 <iostream> 和 <algorithm> 头文件，也可以通过 #include <bits/stdc++.h> 来包含所有标准头文件。


4. 在C++中，容器是一种数据结构，它可以存储和组织不同类型的数据。C++标准库提供了许多容器类，包括vector、deque、list、set、map、unordered_set、unordered_map等。这些容器类都提供了一些基本的操作，如添加元素、删除元素、查找元素、排序等。
5. C++中的容器有许多优点，例如它们可以自动调整大小、提供快速的随机访问、提供高效的插入和删除操作、提供方便的迭代器操作等等。由于C++标准库中的容器类可以适应各种应用需求，所以在C++编程中使用容器可以让程序更加简洁、高效和可维护。

# 2. STL分类
## 2.1 迭代器
1. 迭代器（iterator）是一个泛化的指针，提供对容器内元素的访问，类似于指针的功能。但是，与指针不同，迭代器可以遍历容器中的所有元素，而不需要知道容器的内部结构。

2. 可以将迭代器看作一个容器元素的指针。不同类型的容器（比如 vector，list 等）拥有不同的迭代器类型。一般情况下，迭代器提供了遍历容器元素的功能，支持移动、访问和修改容器中的元素。


# 3. vector容器
## 3.1 Vector的简介
1. vector是将元素至于一个动态数组加以管理的容器
2. veector可以随机存取元素(支持索引值直接存取，用[]操作符或at()方法)
3. vector尾部添加或一处元素非常快速，在中间或者头部插入元素或移除元素比较费时

## 3.2 Vector的构造
vector采用模板类实现，vector对象的默认构造形式
```cpp
vector<T> vecT; 

vector<int> vecInt;        	//一个存放int的vector容器。
vector<float> vecFloat;     	//一个存放float的vector容器。
vector<string> vecString;   	//一个存放string的vector容器。
...				    //尖括号内还可以设置指针类型或自定义类型。
class CA{};
vector<CA*> vecpCA;	  	//用于存放CA对象的指针的vector容器。
vector<CA> vecCA;     	//用于存放CA对象的vector容器。由于容器元素的存放是按值复制的方式进行的，
                        //所以此时CA必须提供CA的拷贝构造函数，以保证CA对象间拷贝正常。
```
# 3.3 底层数据结构: 动态开辟的数组，每次以原来空间大小的2倍进行扩容的
- 开辟新的空间
- 把之前的元素复制过去
- 把之前的容器析构掉
- vector<int> vec;
# 3.4 增加
- vec.push_back(20); 末尾添加元素 O(1) 有可能导致元素扩容
- vec.insert(it, 20); 在指定位置it上添加一个元素20, O(n) 有可能导致元素扩容
# 3.5 删除
- vec.pop_back(); 末尾删除元素 O(1)
- vec.erase(it); 删除迭代器指定元素 O(n)
# 3.6 查询
- operator[] 下表随机访问 vec[5]  O(1)
- iterator迭代器进行遍历
- find, for_each 
- for_each 通过iterator来实现
- 对容器进行连续插入或者删除操作(inseret/erase)，一定要更新迭代器，否则第一次insert或者erase完成，迭代器就失效了
- 当插入或删除元素时，可能会导致容器中元素的位置发生变化，这样原来的迭代器指向的元素的位置也会发生变化，导致迭代器失效。因此，在进行插入或删除操作后，必须更新迭代器指向的元素的位置。如果不更新迭代器，那么在使用它访问容器中的元素时，程序会出现未定义的行为。

# 3.7 常用的方法
- size()
- empty()
- reserve(20) : vector预留空间
- resize(20) : 容器扩容用的
- swap: 两个容器进行元素交换
 
# 3.8 两种方式便利访问vector
```cpp
#include <iostream>
#include <vector>
using namespace std;

int main()
{
  // 创建int类型的vector容器
  vector<int> vec; // 如果想要一个float类型的容器: vector<float> vec;

  // 往容器里面添加20个元素
  for (int i = 0; i < 20; i++)
  {
    vec.push_back(rand() % 100 + 1); // 往里面添加1 - 100的元素
  }

  // 遍历访问vector容器
  // 1. vector的operator[]运算符重载函数
  int size = vec.size();
  for (int i = 0; i < size; i++)
  {
    cout << vec[i] << " ";
  }
  cout << endl;

  // 2. 通过迭代器访问vector
  auto it1 = vec.begin();
  cout << *vec.end() << endl; // 是0, 因为19才是最后的元素
  for (; it1 != vec.end(); it1++)
  {
    cout << *it1 << " ";
  }
  cout << endl;

  return 0;
}
```
# 3.9 删除vector里面的偶数

