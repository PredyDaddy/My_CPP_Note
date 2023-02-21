
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
# 3.9 对vector里元素的操作
1. 删除vector里面的偶数
2. 给奇数前面加一个小的数字

```cpp
#include <iostream>
#include <vector>
using namespace std;

void vec_show(const vector<int> &vec)
{
  cout << "element: ";
  for (auto element : vec) // C++ 11 中的新特性
  {
    cout << element << " ";
  }
  std::cout << std::endl;
}

int main()
{
  // 创建int类型的vector容器
  vector<int> vec; // 如果想要一个float类型的容器: vector<float> vec;

  // 往容器里面添加20个元素
  for (int i = 0; i < 20; i++)
  {
    vec.push_back(rand() % 100 + 1); // 往里面添加1 - 100的元素
  }

  vec_show(vec);

  auto it2 = vec.begin();

  while (it2 != vec.end())
  {
    if (*it2 % 2 == 0)
    {
      // 里面放迭代器
      it2 = vec.erase(it2); // 删掉之后再继续判断上到这个位置的元素是不是偶数
    }
    else
    {
      ++it2;
    }
  }
  vec_show(vec);

  for (auto it3 = vec.begin(); it3 < vec.end(); it3++)
  {
    if (*it3 % 2 != 0)
    {
      // 前面放迭代器，后面放元素
      vec.insert(it3, *it3 - 1);
      it3++; // 假如第三个是奇书，我们插入后，本来在第三个的元素去到第四个了，我们下一个判断的是第五个元素
    }
  }
  vec_show(vec);
  return 0;
}
```

## 3.10 vector的常用用法
1. reserve() 预留了空间，不用一次一次扩容，有效率
2. resize 不仅开辟了空间还添加了元素
```cpp
#include <iostream>
#include <vector>
using namespace std;

void vec_show(const vector<int> &vec)
{
  cout << "element: ";
  for (auto element : vec) // C++ 11 中的新特性
  {
    cout << element << " ";
  }
  std::cout << std::endl;
}

int main()
{
  // 创建int类型的vector容器
  vector<int> vec; // 如果想要一个float类型的容器: vector<float> vec;

  // 往容器里面添加20个元素
  for (int i = 0; i < 20; i++)
  {
    vec.push_back(rand() % 100 + 1); // 往里面添加1 - 100的元素
  }

  vec_show(vec);

  auto it2 = vec.begin();

  while (it2 != vec.end())
  {
    if (*it2 % 2 == 0)
    {
      // 里面放迭代器
      it2 = vec.erase(it2); // 删掉之后再继续判断上到这个位置的元素是不是偶数
    }
    else
    {
      ++it2;
    }
  }
  vec_show(vec);

  for (auto it3 = vec.begin(); it3 < vec.end(); it3++)
  {
    if (*it3 % 2 != 0)
    {
      // 前面放迭代器，后面  放元素
      vec.insert(it3, *it3 - 1);
      it3++; // 假如第三个是奇书，我们插入后，本来在第三个的元素去到第四个了，我们下一个判断的是第五个元素
    }
  }
  vec_show(vec);
  return 0;
}
```
# 4. deque容器(双端队列容器)
## 4.1 底层逻辑(以int类型的deque容器为例)
1. 两头，每头元素的个数取决于类型
```cpp
#define MAP_SIZE 2
#define QUE_SIZE 4096/sizeof(T)

// 以int类型的deque容器为例
deque<int> deq;
4096 / sizeof(int) = 1024 // 双端二维，每头都有1024个元素
```
2. 开始放元素前
![在这里插入图片描述](https://img-blog.csdnimg.cn/50a91ca920974ce385f74447d908894b.png)
3. 第一个满了，map_size 2 ->4, 从2/2 = 1， 从第一个队列开始放元素
![在这里插入图片描述](https://img-blog.csdnimg.cn/551e3d50571e4fd5a5e1ca7480d66c9d.png)
![在这里插入图片描述](https://img-blog.csdnimg.cn/5861ce7704a6468fbe5de70a2286b78e.png)


4. 第二次满了，map_size 4->8，从第2个队列开始放元素
![在这里插入图片描述](https://img-blog.csdnimg.cn/5b495b2f76c1419e81930ecfaa1cc17b.png)

5. **总结: 动态开辟的二维数组，以为数组从2开始，以两倍的方式进行扩容。每次扩容后，原来的二维数组，从oldsize/2的下标开始存放元素，上下预留相同的空行，便于增加元素**  

## 4.2 增加
1. deq.push_back(20); 尾部添加O(1)
2. deq.push_front(20); 首部添加哎O(1)
3. deq.insert(it, 20); 指定元素添加O(n)

## 4.3 删除
1. deq.pop_back();  尾部删除 O(1)
2. deq.pop_front(); 首部删除 O(1)
3. dq.erase(it); 指定元素删除 O(n)

## 4.4 查询
iterator(连续的inseret和erase要考虑迭代器失效，用返回更新迭代器)

## 4.5 一些案例
```cpp
#include <iostream>
#include <deque>

using namespace std;

void deq_show(deque<int> deq)
{
  cout << "Element: ";
  for (auto element : deq)
  {
    cout << element << " ";
  }
  cout << endl;
}

void func1()
{
  deque<int> dq = {1, 2, 3};
  deq_show(dq);

  // 在队尾和队首插入元素
  dq.push_front(20);
  dq.push_back(33);
  deq_show(dq);

  // 在队尾和队首删除元素
  dq.pop_front();
  dq.pop_back();
  deq_show(dq);

  // 在指定元素添加删除添加
  auto it = dq.begin();
  it = it + 2;
  dq.insert(it, 99);
  deq_show(dq);

  dq.erase(it);
  deq_show(dq);
}

int main()
{

  func1();
  return 0;
}

```

# 5. list: 链表容器
## 5.1 底层的数据结构
1. 
