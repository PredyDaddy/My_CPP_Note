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