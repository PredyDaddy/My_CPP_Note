```cpp
#include <iostream>
#include <vector>
using namespace std;

void vec_show(const vector<int>& vec)
{
  cout<<"element: ";
  for (auto element : vec)
  {
    cout << element << " ";
  }
  std::cout<< std::endl;
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
  return 0;
}
```