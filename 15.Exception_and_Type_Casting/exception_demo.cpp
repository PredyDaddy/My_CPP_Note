#include <iostream>
using namespace std;
#include <typeinfo>

#if 0
double division(int a, int b)
{
  if (b == 0)
  {
    throw "Division by zero condition!";
  }
  return (a / b);
}

double division1(int a, int b)
{
  if (b == 0)
  {
    throw "Division1 by zero condition!";
  }
  return (a / b);
}

int main()
{
  try
  {
    division(10, 0);
    division1(10, 0);
  }
  catch (const char *msg)
  {
    std::cerr << msg << endl;
  }

  return 0;
}
#endif

// class MyException : public exception
// {
// public:
//   const char *what() const throw()
//   {
//     return "C++ Exception";
//   }
// };

// int main()
// {
//   try
//   {
//     throw MyException();
//   }
//   catch (MyException &e)
//   {
//     cout << "MyException caught" << endl;
//     cout << e.what() << endl;
//   }
//   catch (exception &e)
//   {
//     // 其他的错误
//   }
// }

// 3. 隐式类型转换
#if 0
int main()
{
  int a = 10;
  float b = a; // 隐式转换，将整数类型转换为浮点数类型

  int c = 10;
  float d = 5.5;
  int e = c + d; // 隐式类型转换，将d转换成整数

  cout << typeid(b).name() << endl; // float
  cout << typeid(e).name() << endl; // int
  return 0;
}
#endif

// 4. const_cast
#if 0
int main()
{
  const int data = 100;
  int *ptr = (int *)&data; // const int 转成int *
  *ptr = 300;
  cout << "data = " << data << "\t地址: " << &data << endl;
  cout << "ptr = " << *ptr << "\t地址: " << ptr << endl;

  int *ptr1 = const_cast<int *>(&data);
  cout << "data = " << data << "\t地址: " << &data << endl;
  cout << "ptr1 = " << *ptr1 << "\t地址: " << ptr << endl;

  *ptr1 = 200;
  cout << "data = " << data << "\t地址: " << &data << endl;
  cout << "ptr1 = " << *ptr1 << "\t地址: " << ptr << endl;

  return 0;
}
#endif

// 常量折叠
#if 0
class MyType
{
public:
  int a = 10;
};

int main()
{
  const MyType t;
  MyType *ptr = const_cast<MyType *>(&t);
  cout << "t = " << t.a << endl;
  ptr->a = 20;
  cout << "t = " << t.a << endl;
  cout << "*ptr = " << ptr->a << endl;
  return 0;
}
#endif

// static_cast用于内置数据类型之间的转换
#if 0
int main()
{
  double value1 = 12.12;
  float value2 = 3.14;
  int value3 = static_cast<int>(value1);
  int value4 = static_cast<int>(value2);
  cout << value3 << endl; // 12
  cout << value4 << endl; // 3 
  return 0;
}
#endif

// static_cast转换自定义数据类型
#if 0
class Person
{
public:
  Person(string n, int a) : name{n}, age(a) {}
  string getName() const { return name; }
  int getAge() const { return age; }

private:
  string name;
  int age;
};

int main()
{
  Person p("Alice", 30);
  cout << typeid(p.getAge()).name() << endl; // int 
  double age = static_cast<double>(p.getAge());  // double
  return 0;
}
#endif

// static_cast 类型之间的强转
#if 0
class A
{
};

class B : public A
{
public:
  void f();
};

class C
{
};


int main()
{
  // 不会报错，因为A B是继承关系
  A *pA = new A;
  B *pB = static_cast<B *>(pA);

  pB = new B;
  pA = static_cast<A *>(pB);

  C *pC = new C;
  // pc = static_cast<A *>; // 会报错，因为没有继承关系

  return 0;
}
#endif

// static_cast
#if 1
class Base
{
public:
  Base(){};
  virtual void show()
  {
    cout << "This is Base class" << endl;
  }
  void func1()
  {
    cout << "Base::func1" << endl;
  }
};

class Derived : public Base
{
public:
  Derived(){};
  void show()
  {
    cout << "This is Derived class" << endl;
  }
};

int main()
{
  // 基类指针转向派生类指针
  Base *ptr = new Base;
  Derived *ptr1 = dynamic_cast<Derived *>(ptr);
  // ptr1->show(); // 转失败了，这里是个空指针
  delete ptr;

  Base *ptr2 = new Derived;
  Derived *ptr3 = dynamic_cast<Derived *>(ptr2);
  ptr2->show(); // 转换成功
  delete ptr2;

  // 派生类指针转向父类，向上转总是安全的，不用用到dynamic_cast
  Derived *der = new Derived;
  Base *base;
  base = der; // 完成转换，虽然基类指针依然指向派生类，但是也没报错，安全
  base->show();
  base->func1();

  return 0;
}
#endif

// 安全转换流程的案例
#if 0
class Animal
{
public:
  virtual void makeSound() {}
};

class Cat : public Animal
{
public:
  void makeSound()
  {
    cout << "Cat is meowing" << endl;
  }
};

class Dog : public Animal
{
public:
  void makeSound()
  {
    cout << "Dog is barking" << endl;
  }
  void bark()
  {
    cout << "wolf!" << endl;
  }
};

// 判断是否转换成dog格式
void dogCheck(Animal *p)
{
  Dog *dog = dynamic_cast<Dog *>(p);
  if (dog != nullptr)
  {
    cout << "This is a dog type" << endl;
    dog->bark();
  }
  else
  {
    cout << "not a dog type" << endl;
  }
}

void catCheck(Animal *ptr)
{
  Cat *cat = dynamic_cast<Cat *>(ptr);
  if (cat) // if (cat != nullptr)
  {
    cout << "This is a cat Type" << endl;
  }
  else
  {
    cout << "This is a not cat type" << endl;
  }
}
int main()
{
  Animal *animal1 = new Cat;
  Animal *animal2 = new Dog;

  dogCheck(animal1); // 转换失败，animal1是指向cat的指针
  dogCheck(animal2); // 转换成功的案例

  catCheck(animal1);
  catCheck(animal2);

  // 释放内存
  delete animal1;
  delete animal2;
  return 0;
}
#endif