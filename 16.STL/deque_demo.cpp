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
