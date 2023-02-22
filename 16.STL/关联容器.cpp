#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <set> // set multiset
#include <map> // map multimap
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
#if 0
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

  unordered_set<int> set;
  for (int v : arr) // O(n)
  {
    set.insert(v); // O(1)
  }

  for (int v : set)
  {
    cout << v << " ";
  }
  cout << endl;
  return 0;
}
#endif

// 有序关联容器
#if 0
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
#endif 

