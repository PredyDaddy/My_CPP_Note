

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

## 2.2 顺序容器: vector, list, deque
1. 


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
- 当vector容器的size达到capacity时，vector会自动进行扩容。扩容的过程中，vector会开辟一个新的内存空间，将旧容器中的元素复制到新容器中，然后释放旧的内存空间。默认情况下，vector容器的capacity增加到原来的两倍。
- **vector<int> vec**;
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
1. 双相的循环链表
2. 最大的区别就是insert/erase是一个O(1)的操作
3. 查询使用迭代器，依然是O(n)
4. deque和list因为是二维和双向的原因，相比于vector多了一个push_front和pop_front()的操作
5. 因为是循环列表，需要用std::advance(it, 2);来往后移动迭代器两位，移到元素末尾就会回到头的位置，具体看下面代码中指定元素添加和删除部分
6. 其他操作同deque的操作
![在这里插入图片描述](https://img-blog.csdnimg.cn/fcbff6299137402e8e85df2a2c371995.png)

```cpp
#include <iostream>
#include <list>

using namespace std;

void deq_show(list<int> deq)
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
  list<int> lst = {1, 2, 3};
  deq_show(lst);

  // 在队尾和队首插入元素
  lst.push_front(20);
  lst.push_back(33);
  deq_show(lst);

  // 在队尾和队首删除元素
  lst.pop_front();
  lst.pop_back();
  deq_show(lst);

  // 在指定元素添加删除添加
  auto it = lst.begin();
  std::advance(it, 2);
  lst.insert(it, 99); 
  deq_show(lst);

  std::advance(it, 4);
  lst.erase(it);
  deq_show(lst);
}

int main()
{

  func1();
  return 0;
}

```


# 6. 顺序容器总结: vector, deque, list

1. vector的特点: 动态数组，内存是连续的，2倍的方式进行扩容，vector<int> vec;
2. deque: 动态开辟的二维数组空间，第二维度是固定长度的数组空间，扩容的时候 (第一维度进行2倍扩容)
3. deque的内存不是连续的，只有第一个二维是连续的，哪怕不扩容，上下都是独立的内存空间

## 6.1 vector 和 deque的区别/应用场景的优缺点？
1. 底层数据结构不同: 动态数组，动态开辟的二维数组
2. 前中后插入删除元素的时间复杂度: 最前面插入deque是O(1) vector是O(n)
3. 涉及到front的操作用deque好一些
4. 内存的使用效率: vector 需要的内存空间是连续的，deque可以分块进行数据存储，只要有适合下一个二维数组的内存块就可以存放
5. 在中间进行insert/erase，vector deque哪个好点儿哪个差一点？
- 从时间复杂度都是O(n)，vector稍微好点，内存是连续的，因为诺元素的时候要在内存块儿之间操作 
## 6.2 vector 和 list的区别/应用场景的优缺点？
1. 什么时候用数组好，什么时候用链表好。
2. 底层数据是数组和链表
3. 数组: 增加删除O(n) 链表中间的增删O(1) 但是随机访问(查询)上数组有下标，而链表是O(n) 

# 7. 标准容器-容器适配器
## 7.1 理解适配器
1. 适配器底层没有自己的数据结构，他都是里国内外一个容器的封装，他的方法全部由底层依赖的容器进行实现的，下面是一个案例

```cpp
#include <iostream>
#include <deque>
using namespace std;

template <typename T, typename Container = deque<T>>
class Stack
{
public:
  void push(const T &val) { con.push_back(val); }
  void pop() { con.pop_back(); }
  T top() const { return con.back(); }

private:
  Container con;
};

int main()
{
  
  return 0;
}
```

2. 没有自己的迭代器,所以展示代码只能一个一个pop(),复制一份
```cpp
void stack_show(stack<int> &s1)
{
  stack<int> s(s1); // 复制一份
  cout << "element: ";
  while (!s.empty())
  {
    cout << s.top() << " ";
    s.pop();
  }
  cout << endl;
}
```

## 7.2 stack(栈)的主要用法
1. push 入栈
2. pop 出栈
3. top查看栈顶元素
4. empty判断栈空
5. size返回元素个数
```cpp
#include <iostream>
#include <deque>
#include <stack>
#include <list>
#include <vector>
#include <queue>
using namespace std;

void stack_show(stack<int> &s1)
{
  stack<int> s(s1); // 复制一份
  cout << "element: ";
  while (!s.empty())
  {
    cout << s.top() << " ";
    s.pop();
  }
  cout << endl;
}

int main()
{
  // push 入栈 pop 出栈 top查看栈顶元素  empty判断栈空  size返回元素个数
  stack<int> s1;
  for (int i = 0; i < 20; i++)
  {
    s1.push(rand() % 100 + 1);
  }
  stack_show(s1);
  stack_show(s1);
  return 0;
}
```
# 8. queue(队列): 
1. push 入队
2. pop 出队
3. front 查看对头元素
4. back查看队尾元素
5. empty判断为空
6. size返回元素个数
```cpp
#include <iostream>
#include <deque>
#include <stack>
#include <list>
#include <vector>
#include <queue>
using namespace std;

void queue_show(queue<int> &q1)
{
  queue<int> q(q1); // 复制一份
  cout << "element: ";
  while (!q.empty())
  {
    cout << q.front() << " ";
    q.pop();
  }
  cout << endl;
}

int main()
{

  queue<int> q1;
  for (int i = 0; i < 20; i++)
  {
    q1.push(rand() % 100 + 1);
  }
  queue_show(q1);
  queue_show(q1);
  return 0;
}
```
# 9. 为什么queue, stack 依赖deque
1. vector的初始内存使用效率太低了，慢慢进行扩容，deque 第一次一次性就可以放1024个整数
2. deque支持头部删除，queue如果依赖vector, 其底层出队效率很低
3. vector需要大片的内存，而deque只需要分段的内存，当存储大量数据的时，显然deque对于内存的利用率好一些
# 10. priority queue为什么依赖于vector?
1. 默认的数据是个大根堆结构，适合vector这种连续的内存

# 11. 关联容器
1. 各个容器底层的数据结构 O(1)  O(log2n)
2. 无序的关联容器 => 链式哈希表  增删查O(1)  
- set:集合 key   map:映射表 [key,value]
- unordered_set 单重集合
- unordered_multiset 多重集合
- unordered_map 单重映射表
- unordered_multimap 多重映射表
```cpp
// 使用无序关联容器包含的头文件
#include <unordered_set>
#include <unordered_map>
```
3. 有序关联容器 => 红黑树 增删查O(log2n) 2是底数(树的层数，树的高度)
- set
- multiset
- map
- multimap
```cpp
// 使用有序关联容器包含的头文件  红黑树
#include <set> // set multiset
#include <map> // map multimap
```
## 11.1 set的增删改查代码
- 单重集合，不会存储key值重复的元素
- 多重集合
- 遍历set
- 按key值删除元素
- 用迭代器删除元素
- find方法
- C++ 11的迭代器输出
```cpp
#include <iostream>
#include <unordered_set>
#include <unordered_map>
using namespace std;

int main()
{
  // 1. 单重集合，不会存储key值重复的元素
  unordered_set<int> set1;
  for (int i = 0; i < 50; i++)
  {
    // list/vector/deque insert(it, val)
    // 集合插入不需要迭代器
    set1.insert(rand() % 20 + 1);
  }
  cout << set1.size() << endl;
  cout << set1.count(10) << endl;

  // 2. 多重集合
  unordered_multiset<int> set2;
  for (int i = 0; i < 50; i++)
  {
    set2.insert(rand() % 20 + 1);
  }
  cout << set2.size() << endl;
  cout << set2.count(11) << endl;

  // 3. 遍历set
  auto it1 = set1.begin();
  cout << "Element: ";
  for (; it1 != set1.end(); it1++)
  {
    cout << *it1 << " ";
  }
  cout << endl;

  // 4. 按key值删除元素
  set1.erase(20);

  // 5. 用迭代器删除元素
  for (it1 = set1.begin(); it1 != set1.end();)
  {
    if (*it1 == 20)
    {
      it1 = set1.erase(it1); // 调用了erase，it1迭代器失效了
    }
    else
    {
      it1++; // 万一下一个元素也是20，就不会进来这个else
    }
  }

  // 6. find方法
  it1 = set1.find(14);
  cout << *it1;
  if (it1 != set1.end()) // 找不到返回end
  {
    set1.erase(it1);
  }

  // 7. C++ 11的迭代器输出
  for (int v : set1)
  {
    cout << v << " ";
  }
  cout << endl;
  return 0;
}
```

## 11.2 map的格式是存储键值对

- find()
```cpp
struct Pair
{
private:
  first; // key
  second; // value 
};
```

6. map的基本操作
- 定义map, multimap 打包成键值对
- C++ 11 的方式插入
- [] 运算符重载返回计算值
- 更改操作
- 删除元素
```cpp
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <string>
using namespace std;

// set的使用方法
#if 0
int main()
{
  // 1. 单重集合，不会存储key值重复的元素
  unordered_set<int> set1;
  for (int i = 0; i < 50; i++)
  {
    // list/vector/deque insert(it, val)
    // 集合插入不需要迭代器
    set1.insert(rand() % 20 + 1);
  }
  cout << set1.size() << endl;
  cout << set1.count(10) << endl;

  // 2. 多重集合
  unordered_multiset<int> set2;
  for (int i = 0; i < 50; i++)
  {
    set2.insert(rand() % 20 + 1);
  }
  cout << set2.size() << endl;
  cout << set2.count(11) << endl;

  // 3. 遍历set
  auto it1 = set1.begin();
  cout << "Element: ";
  for (; it1 != set1.end(); it1++)
  {
    cout << *it1 << " ";
  }
  cout << endl;

  // 4. 按key值删除元素
  set1.erase(20);

  // 5. 用迭代器删除元素
  for (it1 = set1.begin(); it1 != set1.end();)
  {
    if (*it1 == 20)
    {
      it1 = set1.erase(it1); // 调用了erase，it1迭代器失效了
    }
    else
    {
      it1++; // 万一下一个元素也是20，就不会进来这个else
    }
  }

  // 6. find方法
  it1 = set1.find(14);
  cout << *it1;
  if (it1 != set1.end()) // 找不到返回end()
  {
    set1.erase(it1);
  }

  // 7. C++ 11的迭代器输出
  for (int v : set1)
  {
    cout << v << " ";
  }
  cout << endl;
  return 0;
}
#endif

int main()
{
  // 1. 定义map, multimap 打包成键值对
  unordered_map<int, string> map1;
  // unordered_multimap<int, string> map1;
  map1.insert(make_pair(1000, "蔡徐坤"));
  // C++ 11 的方式插入
  map1.insert({1001, "鸡哥"});
  map1.insert({1002, "坤哥"});
  map1.insert({1000, "asd"}); // 不允许key重复的
  cout << map1.size() << endl;

  // 2. [] 运算符重载返回计算值
  cout << map1[1000] << endl;
  // 如果key不存在，会插入一对数据以及value默认值
  cout << map1[44] << endl;
  map1[44] = "AAA";
  cout << map1[44] << endl;

  // 更改操作
  map1[1000] = "ASDASDASD";
  cout <<  map1[1000] << endl;

  // 3. 删除元素
  map1.erase(1002);

  // 4. find()
  auto it1 = map1.find(1001);
  if (it1 != map1.end()) // 找不到返回end
  {
    cout << "key: " << it1->first << " value: "<< it1->second << endl;
  }
  
  return 0;
}
```
## 11.3 map在查询海量数据的时候
```cpp
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <string>
using namespace std;

// set的使用方法
#if 0
int main()
{
  // 1. 单重集合，不会存储key值重复的元素
  unordered_set<int> set1;
  for (int i = 0; i < 50; i++)
  {
    // list/vector/deque insert(it, val)
    // 集合插入不需要迭代器
    set1.insert(rand() % 20 + 1);
  }
  cout << set1.size() << endl;
  cout << set1.count(10) << endl;

  // 2. 多重集合
  unordered_multiset<int> set2;
  for (int i = 0; i < 50; i++)
  {
    set2.insert(rand() % 20 + 1);
  }
  cout << set2.size() << endl;
  cout << set2.count(11) << endl;

  // 3. 遍历set
  auto it1 = set1.begin();
  cout << "Element: ";
  for (; it1 != set1.end(); it1++)
  {
    cout << *it1 << " ";
  }
  cout << endl;

  // 4. 按key值删除元素
  set1.erase(20);

  // 5. 用迭代器删除元素
  for (it1 = set1.begin(); it1 != set1.end();)
  {
    if (*it1 == 20)
    {
      it1 = set1.erase(it1); // 调用了erase，it1迭代器失效了
    }
    else
    {
      it1++; // 万一下一个元素也是20，就不会进来这个else
    }
  }

  // 6. find方法
  it1 = set1.find(14);
  cout << *it1;
  if (it1 != set1.end()) // 找不到返回end()
  {
    set1.erase(it1);
  }

  // 7. C++ 11的迭代器输出
  for (int v : set1)
  {
    cout << v << " ";
  }
  cout << endl;
  return 0;
}
#endif

// map的基本操作
#if 0
int main()
{
  // 1. 定义map, multimap 打包成键值对
  unordered_map<int, string> map1;
  // unordered_multimap<int, string> map1;
  map1.insert(make_pair(1000, "蔡徐坤"));
  // C++ 11 的方式插入
  map1.insert({1001, "鸡哥"});
  map1.insert({1002, "坤哥"});
  map1.insert({1000, "asd"}); // 不允许key重复的
  cout << map1.size() << endl;

  // 2. [] 运算符重载返回计算值
  cout << map1[1000] << endl;
  // 如果key不存在，会插入一对数据以及value默认值
  cout << map1[44] << endl;
  map1[44] = "AAA";
  cout << map1[44] << endl;

  // 更改操作
  map1[1000] = "ASDASDASD";
  cout <<  map1[1000] << endl;

  // 3. 删除元素
  map1.erase(1002);

  // 4. find()
  auto it1 = map1.find(1001);
  if (it1 != map1.end()) // 找不到返回end
  {
    cout << "key: " << it1->first << " value: "<< it1->second << endl;
  }
  
  return 0;
}
#endif

// map在处理海量数据时候的优势
int main()
{
  const int ARR_LEN = 10000;
  int arr[ARR_LEN] = {0}; // 全部初始化为0
  for (int i = 0; i < ARR_LEN; i++)
  {
    arr[i] = rand() % 10000 + 1;
  }

  // 统计上面数字那些重复了，并且统计数字的重复的次数
  unordered_map<int, int> map1; // 值， 次数
  // 方法1
#if 0
  for (int k : arr) // arr里的元素依次给k
  {
    auto it = map1.find(k);
    if (it == map1.end()) // 没找到
    {
      map1.insert({k, 1});
    }
    else
    {
      it->second++;
    }
  }

  // 查看结果
  for (pair<int, int> p : map1)
  {
    if (p.second > 1)
    {
      cout << "key: " << p.first << " count: " << p.second << endl;
    }
  }
  return 0;
#endif

  // 方法2:
  for (int k : arr)
  {
    // []查询操作,找到了先来个{k, 0}，++后就是{k, 1} 再找到一个就是{k, 2}
    map1[k]++;
  }

  for (auto it = map1.begin(); it != map1.end(); it++)
  {
    if (it->second > 1)
    {
      cout << "int: " << it->first << " value: " << it->second << endl;
    }
  }
  return 0;
}
```

# 12. 有序的关联容器map
1. 使用都是一样的
```cpp
int main()
{
  set<int> set1;
  for (int i = 0; i < 20; i++)
  {
    set1.insert(rand() % 20 + 1);
  }

  cout << "Element: ";
  for (int v : set1)
  {
    cout << v << " ";
  }
  cout << endl;
  return 0;
}
```
# 13. 迭代器与可迭代对象
1. 在C++中，迭代器是一种访问容器或序列中元素的方式，它相当于一个指针，指向容器或序列中的某个元素。通过使用迭代器，可以实现对容器或序列中元素的访问、添加、删除等操作。使用迭代器可以遍历容器或序列中的所有元素，对每个元素进行操作。

2。 可迭代对象是指实现了迭代器的对象，通常是容器或序列。对于一个可迭代对象，可以使用迭代器遍历其中的元素，对每个元素进行操作。STL中的诸如vector、list、map等容器都是可迭代对象，它们实现了迭代器，并且可以使用迭代器进行遍历。除了容器之外，还可以通过实现自定义迭代器来使自己的对象成为可迭代对象，从而可以使用STL算法进行操作。
# 13. 迭代器itertor
1. 普通的正向迭代器
2. 普通的反向迭代器
3. 常量的正向迭代器(只可以解引用读取不可以更改)
4. 常量的反向迭代器(只可以解引用读取不可以更改)
```cpp
#include <iostream>
#include <vector>
using namespace std;

// 正向迭代器
#if 0
int main()
{
   
  vector<int> vec;
  for (int i = 0; i < 20; i++)
  {
    vec.push_back(rand() % 100);
  }

  // vector<int>::interator
  auto it1 = vec.begin();
  for (; it1 != vec.end(); it1++)
  {
    cout << *it1 << " ";
  }
  cout << endl;
}
#endif

// 反向迭代器
#if 0
int main()
{
  vector<int> vec;
  for (int i = 0; i < 20; i++)
  {
    vec.push_back(rand() % 100);
  }
  auto rit = vec.rbegin();
  for (; rit != vec.rend(); rit++)
  {
    cout << *rit << " ";
  }
  cout << endl;
  return 0;
}
#endif

// 常量迭代器
int main()
{

  vector<int> vec;
  for (int i = 0; i < 20; i++)
  {
    vec.push_back(rand() % 100);
  }

  // vector<int>::interator
  // auto it1 = vec.begin();
  vector<int>::const_iterator it1 = vec.begin(); // 不能截引用赋值
  for (; it1 != vec.end(); it1++)
  {
    *it1 = 20; // 报错的
  }
  cout << endl;
}
```

