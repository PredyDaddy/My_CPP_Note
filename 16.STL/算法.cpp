#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

// 以普通函数的方式实现自定义排序规则
bool mycomp(int i, int j)
{
  return (i < j);
}

// 以函数对象的方式实现
class mycomp2
{
public:
  bool operator()(int i, int j)
  {
    return (i < j);
  }
};

class mycomp3
{
public:
  bool operator()(const int &i)
  {
    return ((i % 9 == 1)); //
  }
};

void vec_show(vector<int> vec)
{
  for (int k : vec)
  {
    cout << k << " ";
  }
  cout << endl;
}

// sort()案例
#if 0
int main()
{
  int arr[] = {32, 71, 12, 45, 26, 80, 53, 33};
  vector<int> vec(arr, arr + 8);

  // 第一个语法
  sort(vec.begin(), vec.begin() + 4);
  vec_show(vec);

  // 第二个语法,greater() 是C++标准库中的一个函数对象
  sort(vec.begin(), vec.begin() + 4, greater<int>());
  vec_show(vec);

  // 通过自定义
  sort(vec.begin(), vec.end(), mycomp);
  vec_show(vec);

  sort(vec.begin(), vec.end(), mycomp2());
  vec_show(vec);

  return 0;
}
#endif

// merge()例子
#if 0
int main()
{
  vector<int> vec1{1, 2, 3};
  vector<int> vec2{1, 2, 3, 5, 6, 7, 8, 9};
  vector<int> vec3(vec1.size() + vec2.size());
  merge(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), vec3.begin());
  for (int i : vec3)
  {
    cout << i << " ";
  }
  cout << endl;
  return 0;
}
#endif
// find() 系列查找算法
#if 0
int main()
{
  vector<int> vecInt;
  vecInt.push_back(1);
  vecInt.push_back(2);
  vecInt.push_back(2);
  vecInt.push_back(4);
  vecInt.push_back(5);
  vecInt.push_back(5);

  // 1. 找重复的元素 adjacent_find
  vector<int>::iterator it = adjacent_find(vecInt.begin(), vecInt.end()); //*it == 2
  cout << *it << endl;

  // 2. 二分查找找value
  bool bFind = binary_search(vecInt.begin(), vecInt.end(), 5);

  // 3. count() 返回相等的个数
  int icount = count(vecInt.begin(), vecInt.end(), 2); // 3

  // 4. find() 查找字符串
  string str = "sjadfk";
  auto it1 = str.find("s");
  if (it1 != string::npos)
  {
    cout << "Found at position " << it1 << endl;
  }
  else
  {
    cout << "Not Found" << endl;
  }

  // 5. find() 查找vector的容器
  vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8};
  vector<int>::iterator it2 = find(vec.begin(), vec.end(), 2);
  if (it2 != vec.end())
  {
    cout << "Already Found! " << *it2 << endl;
  }
  else
  {
    cout << "Not Found!" << endl;
  }

  // 6. 以函数对象的形式定义查找规则 find_if
  vector<int> vec1 = {2, 3, 4, 6, 7, 8, 0};
  auto it3 = find_if(vec1.begin(), vec1.end(), mycomp3());
  cout << *it3 << endl; // 可以吧mycomp3数字改改看看不同结果
  

  return 0;
}
#endif

int main()
{
  return 0;
}