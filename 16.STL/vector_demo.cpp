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

void vec_add(vector<int> &vec)
{
  // 往容器里面添加20个元素
  for (int i = 0; i < 20; i++)
  {
    vec.push_back(rand() % 100 + 1); // 往里面添加1 - 100的元素
  }
}
int main()
{

  // 创建int类型的vector容器
  vector<int> vec, vec1; // 如果想要一个float类型的容器: vector<float> vec;
#if 0
  vec.reserve(20);
  cout << vec.empty() << endl; // 1 是空的
  cout << vec.size() << endl;  // 0 没元素

  vec_add(vec);

  cout << vec.empty() << endl; // 0
  cout << vec.size() << endl;  // 20
#endif

  vec1.resize(20);
  cout << vec1.empty() << endl; // 0 不是是空的
  cout << vec1.size() << endl;  // 20 有元素，都是0

  vec_add(vec1);

  cout << vec1.empty() << endl; // 0
  cout << vec1.size() << endl;  // 40， 从第21个开始扩容
  vec_show(vec1);
  return 0;
}