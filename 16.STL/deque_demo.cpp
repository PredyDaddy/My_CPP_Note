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
