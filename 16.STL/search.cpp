#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

template <typename T>
void vec_show(const vector<T> vec)
{
  cout << "Element: ";
  for (T k : vec)
  {
    cout << k << ' ';
  }
  cout << endl;
}

bool mycomp(int i, int j)
{
  return (i % j == 0);  // 能被整除就算是合格
}

class mycomp2
{
public:
  bool operator()(const int &i, const int &j)
  {
    return (i % j == 0 );
  }
};
int main()
{
  vector<int> vec = {1, 2, 3, 4, 8, 12, 18, 1, 2, 3};
  vec_show(vec);
  int arr[] = {1, 2, 3};

  // 1. 调用第一种语法
  auto it = search(vec.begin(), vec.end(), arr, arr + sizeof(arr) / sizeof(int));

  if (it != vec.end())
  {
    cout << "第一个{1,2,3}的起始位置为：" << it - vec.begin() << ",*it = " << *it << endl;
  }
  else
  {
    cout << "Not Found!" << endl;
  }

  // 2. 调用第二种语法
  it = search(vec.begin(), vec.end(),
              arr, arr + 3, mycomp);
  if (it != vec.end()) {
        cout << "第一个{2,3,4}的起始位置为：" << it - vec.begin() << ",*it = " << *it;
    }

  // 3. 调用第三种语法
  it = search(vec.begin(), vec.end(),
              arr, arr + 3, mycomp2());
  if (it != vec.end()) {
        cout << "第一个{2,3,4}的起始位置为：" << it - vec.begin() << ",*it = " << *it;
    }
    cout << endl;
    return 0;
}