# 1. 抛出异常
```cpp
#include <iostream>
using namespace std;

double division(int a, int b)
{
   if( b == 0 )
   {
      throw "Division by zero condition!";
   }
   return (a/b);
}  

int main()
{
  cout << division(10, 0) << endl;
  return 0;
}
```

# 2. 捕获异常
**由于我们抛出的异常为字符串，所以，当捕获该异常时，我们必须在 catch 块中使用 const char***
```cpp
try
{
   // 保护代码
}catch( ExceptionName e )
{
  // 处理 ExceptionName 异常的代码
}
```
```cpp
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
```

```cpp
class MyException : public exception
{
public:
  const char *what() const throw()
  {
    return "C++ Exception";
  }
};

int main()
{
  try
  {
    throw MyException();
  }
  catch (MyException &e)
  {
    cout << "MyException caught" << endl;
    cout << e.what() << endl;
  }
  catch (exception &e)
  {
    // 其他的错误
  }
}
```

# 3. C++ 中的隐式类型转换
1. C++ 中的隐式类型转换指的是在某些情况下，编译器会自动将一种类型转换成另一种类型，而不需要显式地进行强制类型转换（即使用类型转换运算符）。
```cpp
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
```
2. 由于隐式转换可能会先精度下降的问题，所以建议用显示的强制类型转换

# 4. 显示类型转换(const_cast)
1. const_cast是一种C++运算符，主要是用来去除复合类型中const和volatile属性(没有真正去除)

2. 变量本身的const属性是不能去除的，要想修改变量的值，一般是去除指针（或引用）的const属性，再进行间接修改。

3. 下面案例中的(int *)是不安全的，data的类型是const,只读类型，任何尝试修改他的操作都会导致未定义的行为，最好用const_cast转换

4. 下面案例中，data都是100，改了还是，同地址的值却不一样，是因为常量折叠，有点像宏，把碰到的data全部用最初的100替换掉。常量折叠只对原生类型起作用
```cpp
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
```
```cpp
data = 100      地址: 0x7fffffffdec4
ptr = 300       地址: 0x7fffffffdec4
data = 100      地址: 0x7fffffffdec4
ptr1 = 300      地址: 0x7fffffffdec4
data = 100      地址: 0x7fffffffdec4
ptr1 = 200      地址: 0x7fffffffdec4
```

5. 常量折叠对自己的数据类型不起作用
```cpp
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
```
# 5. 显示类型转换static_cast
1. 主要用内内助数据之间的相互转换
```cpp
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
```

2. static_cast转换自定义数据类型
```cpp
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
```

3. 类之间的转换需要继承关系
```cpp
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
```
# 3. dynamic_cast
1. 支持在运作的时候识别指针的转换
2. dynamic_cast用于继承层次之间的引用转换，主要还是用于执行“安全的向下转型（safe downcasting）”，也即是基类对象的指针或引用转换为同一继承层次的其他指针或引用。
3. “向下转型”的前提条件：被转换对象必须是多态类型（必须公有继承自其他类，或者有虚函数）
```cpp
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
```



# 4. dynamic_cast 安全转换的流程
1. 在C++中，dynamic_cast用于运行时类型识别（RTTI），将基类指针或引用转换为派生类指针或引用。它用于在多态类层次结构中安全地转换类型。dynamic_cast转换后，如果转换成功，则可以通过派生类的指针或引用访问派生类特有的成员函数或成员变量，否则将返回NULL或引发std::bad_cast异常。
```cpp
Derived* d = dynamic_cast<Derived*>(basePtr);
if (d) {
    // 转换成功，d是指向Derived的指针
    d->derivedFunc();
}
else {
    // 转换失败，basePtr指向的不是Derived类型的对象
    // 这里可以做一些异常处理
}

```

2. 完整的案例(指针转换成功或者指针转换失败)
```cpp
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
```






