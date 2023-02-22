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