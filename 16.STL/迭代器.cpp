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
    // *it1 = 20; // 报错的
  }
  cout << endl;
}