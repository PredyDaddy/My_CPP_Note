// 06 C++ STL.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//



/*
C++ STL standard template libaray 标准模板库
一、标准容器 C++11 array  forward_list
1.顺序容器 
vector
deque
list
2.容器适配器
stack
queue
priority_queue
3.关联容器 
无序关联容器 => 链式哈希表  增删查O(1) 
set:集合 key   map:映射表 [key,value]
unordered_set 单重集合
unordered_multiset 多重集合
unordered_map 单重映射表
unordered_multimap 多重映射表

有序关联容器 => 红黑树 增删查O(log2n) 2是底数(树的层数，树的高度)
set
multiset
map
multimap

二、近容器
数组，string，bitset(位容器)

三、迭代器
iterator和const_iterator
reverse_iterator和const_reverse_iterator

四、函数对象（类似C的函数指针）
greater,less

五、泛型算法
sort,find,find_if,binary_search,for_each
*/

#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <stack> // stack
#include <queue> // queue和priority_queue
#include <string>

// 使用无序关联容器包含的头文件
#include <unordered_set>
#include <unordered_map>

// 使用有序关联容器包含的头文件  红黑树
#include <set> // set multiset
#include <map> // map multimap
using namespace std;

#if 0
class Student
{
public:
	Student(int id=0, string name="")
		:_id(id), _name(name) {}
private:
	int _id;
	string _name;
	friend ostream& operator<<(ostream &out, const Student &stu);
};
ostream& operator<<(ostream &out, const Student &stu)
{
	out << "id:" << stu._id << " name:" << stu._name << endl;
	return out;
}
int main()
{
	map<int, Student> stuMap;
	stuMap.insert({ 1000, Student(1000, "张雯") });
	stuMap.insert({ 1020, Student(1020, "李广") });
	stuMap.insert({ 1030, Student(1030, "高洋") });

	// stuMap.erase(it) stuMap.erase(1020)  stuMap[2000] [2000, V()]
	// cout << stuMap[1020] << endl;   stuMap.find(key)
	auto it = stuMap.begin();
	for (; it != stuMap.end(); ++it)
	{
		cout << "key:" << it->first << " value:" << it->second << endl;
	}
	cout << endl;

	return 0;
}


class Student
{
public:
	Student(int id, string name)
		:_id(id), _name(name) {}
	bool operator<(const Student &stu)const
	{
		return _id < stu._id;
	}
private:
	int _id;
	string _name;
	friend ostream& operator<<(ostream &out, const Student &stu);
};
ostream& operator<<(ostream &out, const Student &stu)
{
	out << "id:" << stu._id << " name:" << stu._name << endl;
	return out;
}
int main()
{
	set<Student> set1;

	set1.insert(Student(1020, "李广"));
	set1.insert(Student(1000, "张雯"));
	
	for (auto it = set1.begin();
		it != set1.end(); ++it)
	{
		cout << *it << endl;
	}
	
	/*
	set<int> set1;
	for (int i = 0; i < 20; ++i)
	{
		set1.insert(rand()%20+1);
	}

	for (int v : set1)
	{
		cout << v << " ";
	}
	cout << endl;
	*/

	return 0;
}




/*
关联容器：
1.各个容器底层的数据结构 O(1)  O(log2n)
2.常用增删查方法
增加：insert(val)
遍历：iterator自己搜索， 调用find成员方法
删除：erase(key)  erase(it)
*/
int main()
{
	// 处理海量数据查重复；去重复的时候
	const int ARR_LEN = 100;
	int arr[ARR_LEN] = { 0 };
	for (int i = 0; i < ARR_LEN; ++i)
	{
		arr[i] = rand() % 20 + 1;
	}

	// 上面的10万个整数中，把数字进行去重打印  set  map
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

#if 0
	// 上面的10万个整数中，统计哪些数字重复了，并且统计数字重复的次数
	unordered_map<int, int> map1;
	for (int k : arr)
	{
		/*
		auto it = map1.find(k);
		if (it == map1.end())
		{
			map1.insert({k, 1});
		}
		else
		{
			it->second++;
		}
		*/
		map1[k]++; // map1[k]  [k, 1]
	}

	/*
	for (const pair<int, int> &p : map1)
	{
		if (p.second > 1)
		{
			cout << "key:" << p.first << " count:" << p.second << endl;
		}
	}
	*/

	auto it = map1.begin();
	for (; it != map1.end(); ++it)
	{
		if (it->second > 1)
		{
			cout << "key:" << it->first <<
				" count:" << it->second << endl;
		}
	}
#endif


	/*
	[key, value]
	struct pair
	{
	 first; => key
	 second; => value
	}

	map的operator[]
	1.查询
	2.如果key不存在，它会插入一对数据[key, string()]
	V& operator[](const K &key)
	{
		insert({key, V()});
	}
	*/

	/*
	unordered_map<int, string> map1;
	map1.insert(make_pair(1000, "张三"));
	map1.insert({1010, "李四"}); // map表增加元素
	map1.insert({1020, "王五" });
	map1.insert({1030, "王凯" });
	map1.erase(1020); // {1020, "王五" }删除了

	auto it1 = map1.find(1030);
	if (it1 != map1.end())
	{
		// it1 -> pair对象
		cout << "key:" << it1->first << " value:" << it1->second << endl;
	}

	//map1[2000]; // key:2000 value:""
	//map1[2000] = "刘硕"; // map1.insert({2000, "刘硕"});
	//map1[1000] = "张三2"; // 
	//cout << map1.size() << endl;
	// map operator[](key) => value  查询
	//cout << map1[1000] << endl;
	*/

#if 0
	unordered_set<int> set1; // 不会存储key值重复的元素
	for (int i = 0; i < 50; ++i)
	{
		set1.insert(rand()%20+1); // vector/deque/list  insert(it, val)
	}

	//cout << set1.size() << endl;
	//cout << set1.count(15) << endl;

	auto it1 = set1.begin();
	for (; it1 != set1.end(); ++it1)
	{
		cout << *it1 << " ";
	}
	cout << endl;

	set1.erase(20); // 按key值删除元素

	for (it1 = set1.begin(); it1 != set1.end(); )
	{
		if (*it1 == 30)
		{
			it1 = set1.erase(it1); // 调用erase，it1迭代器就失效了
		}
		else
		{
			++it1;
		}
	}
	
	it1 = set1.find(20);
	if (it1 != set1.end())
	{
		set1.erase(it1);
	}

	for (int v : set1)
	{
		cout << v << " ";
	}
	cout << endl;
#endif

	return 0;
}



/*
标准容器 - 容器适配器 => 设计模式，就叫做适配器模式
怎么理解这个适配器？
1.适配器底层没有自己的数据结构，它是另外一个容器的封装，它的方法全部由底层依赖的容器进行实现的
2.没有实现自己的迭代器

template<typename T, typename Container=deque<T>>
class Stack
{
public:
	void push(const T &val) { con.push_back(val); }
	void pop() { con.pop_back(); }
	T top()const { return con.back(); }
private:
	Container con;
};

stack: push入栈  pop出栈  top查看栈顶元素  empty判断栈空  size返回元素个数 

queue: push入队  pop出队  front查看队头元素 back查看队尾元素  empty判断队空   size返回元素个数
queue => deque  为什么不依赖vector呢？？？
stack => deque  为什么不依赖vector呢？？？
1.vector的初始内存使用效率太低了！没有deque好  queue<int> stack<int>  vector 0-1-2-4-8 deque 4096/sizeof(int) = 1024
2.对于queue来说，需要支持尾部插入，头部删除，O(1)  如果queue依赖vector，其出队效率很低
3.vector需要大片的连续内存，而deque只需要分段的内存，当存储大量数据时，显然deque对于内存的利用率更好一些

priority_queue: push入队  pop出队  top查看队顶元素  empty判断队空  size返回元素个数  默认：大根堆
priority_queue => vector 为什么依赖vector？？？
底层默认把数据组成一个大根堆结构  在一个内存连续的数组上构建一个大根堆或者小根堆的
*/
int main()
{
	priority_queue<int> pque;
	for (int i = 0; i < 20; ++i)
	{
		pque.push(rand() % 100 + 1);
	}
	cout << pque.size() << endl;
	while (!pque.empty())
	{
		cout << pque.top() << " ";
		pque.pop();
	}


	cout << endl;
	cout << "---------------------------" << endl;

	queue<int> que;
	for (int i = 0; i < 20; ++i)
	{
		que.push(rand() % 100 + 1);
	}
	cout << que.size() << endl;
	while (!que.empty())
	{
		cout << que.front() << " ";
		que.pop();
	}

	cout << endl;
	cout << "---------------------------" << endl;
	
	stack<int> s1;
	for (int i = 0; i < 20; ++i)
	{
		s1.push(rand() % 100 + 1);
	}

	cout << s1.size() << endl;

	while (!s1.empty())
	{
		cout << s1.top() << " ";
		s1.pop();
	}
	
	return 0;
}


/*
vector特点：动态数组，内存是连续的，2倍的方式进行扩容， vector<int> vec; 0-1-2-4-8... reserve(20)/resize
deque特点：动态开辟的二维数组空间，第二维是固定长度的数组空间，扩容的时候（第一维的数组进行2倍扩容）
		面经问题：deque底层内存是否是连续的？   并不是  每一个第二维是连续的，

容器的纵向考察：容器掌握的深度
容器的横向考察：各个相似容器之间的对比

vector和deque之间的区别？
1.底层数据结构：
2.前中后插入删除元素的时间复杂度： 中间和末尾 O(1)  前 deque O(1) vector O(n)
3.对于内存的使用效率： vector 需要的内存空间必须是连续的    deque 可以分块进行数据存储，不需要内存空间必须是一片连续的
4.在中间进行insert或者erase，vector和deque它们的效率谁能好一点(vector)？谁能差一点(deque)？  O(n)

for(int i=0; i<10000; ++i)
{
	cout << arr[i] << endl;
}

vector和list之间的区别？   数组:增加删除O(n) 查询O(n) 随机访问O(1)   链表:(考虑搜索的时间)增加删除O(1)  查询O(n)
1.底层数据结构：数组   双向循环链表
*/
int main()
{
	return 0;
}




/*
deque：双端队列容器
底层数据结构：动态开辟的二维数组，一维数组从2开始，以2倍的方式进行扩容，每次扩容后，原来第二维的数组，从
新的第一维数组的下标oldsize/2开始存放，上下都预留相同的空行，方便支持deque的首尾元素添加

deque<int> deq;
增加：
deq.push_back(20); 从末尾添加元素 O(1)  
deq.push_front(20); 从首部添加元素 O(1)   // vec.insert(vec.begin(), 20) O(n)
deq.insert(it, 20); it指向的位置添加元素 O(n)

删除：
deq.pop_back(); 从末尾删除元素 O(1)  
deq.pop_front(); 从首部删除元素 O(1)  
deq.erase(it);  从it指向的位置删除元素 O(n)

查询搜索：
iterator(连续的insert和erase一定要考虑迭代器失效的问题)

list：链表容器
底层数据结构：双向的循环链表   pre data next
list<int> mylist;
增加：
mylist.push_back(20); 从末尾添加元素 O(1)
mylist.push_front(20); 从首部添加元素 O(1)   // vec.insert(vec.begin(), 20) O(n)
mylist.insert(it, 20); it指向的位置添加元素 O(1) // 链表中进行insert的时候，先要进行一个query查询操作
    对于链表来说，查询操作效率就比较慢了

删除：
mylist.pop_back(); 从末尾删除元素 O(1)
mylist.pop_front(); 从首部删除元素 O(1)
mylist.erase(it);  从it指向的位置删除元素 O(1)

查询搜索：
iterator(连续的insert和erase一定要考虑迭代器失效的问题)

deque和list，比vector容器多出来的增加删除函数接口：
push_front和pop_front
*/
int main()
{


	return 0;
}




/*
vector：向量容器 
底层数据结构：动态开辟的数组，每次以原来空间大小的2倍进行扩容的

vector<int> vec;
增加:
vec.push_back(20); 末尾添加元素 O(1)   导致容器扩容
vec.insert(it, 20); it迭代器指向的位置添加一个元素20  O(n)   导致容器扩容

删除:
vec.pop_back(); 末尾删除元素 O(1) 
vec.erase(it); 删除it迭代器指向的元素 O(n)

查询:
operator[] 下标的随机访问vec[5]  O(1)
iterator迭代器进行遍历
find，for_each
foreach => 通过iterator来实现的

注意：对容器进行连续插入或者删除操作(insert/erase)，一定要更新迭代器，否则第一次insert或者erase完成，
迭代器就失效了

常用方法介绍:
size()
empty()
reserve(20)：vector预留空间的   只给容器底层开辟指定大小的内存空间，并不会添加新的元素
resize(20)：容器扩容用的  不仅给容器底层开辟指定大小的内存空间，还会添加新的元素
swap ： 两个容器进行元素交换

*/
int main()
{
	vector<int> vec; // vector<string> vec; 0 1 2 4 8 16 32 64
	//vec.reserve(20); // 叫做给vector容器预留空间
	vec.resize(20);

	cout << vec.empty() << endl;
	cout << vec.size() << endl; // int()

	for (int i = 0; i < 20; ++i)
	{
		vec.push_back(rand()%100 + 1);
	}

	cout << vec.empty() << endl;
	cout << vec.size() << endl;



	// vector的operator[]运算符重载函数
	int size = vec.size();
	for (int i = 0; i < size; ++i)
	{
		cout << vec[i] << " ";
	}
	cout << endl;

	// 把vec容器中所有的偶数全部删除
	auto it2 = vec.begin();
	while (it2 != vec.end())
	{
		if (*it2 % 2 == 0)
		{
			it2 = vec.erase(it2);
		}
		else
		{
			++it2;
		}
	}

	// 通过迭代器遍历vector容器
	auto it1 = vec.begin();
	for (; it1 != vec.end(); ++it1)
	{
		cout << *it1 << " ";
	}
	cout << endl;

	// 给vector容器中所有的奇数前面都添加一个小于奇数1的偶数   44 45    56 57
	for (it1 = vec.begin(); it1 != vec.end(); ++it1)
	{
		if (*it1 % 2 != 0)
		{
			it1 = vec.insert(it1, *it1-1);
			++it1;
		}
	}

	for (it1 = vec.begin(); it1 != vec.end(); ++it1)
	{
		cout << *it1 << " ";
	}
	cout << endl;


	return 0;
}
#endif