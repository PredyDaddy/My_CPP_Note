
# 前提
- 代码之后交付给客户/用户(同事)一般是给他们*.h文件，他们去看里面有什么类，类里面有什么接口/函数
- 具体的接口/函数实现是在另外的*.cpp里面实现的
- 如果在练习的时候全部写在一个*.cpp文件，有一个Sense, main函数里面是给客户/用户(同事)写的，我们提供这些接口的实现方法和一些限制

# 类和结构体
- stsruct也可以表示一个类，那什么时候用class，什么时候用struct
- 有些约定俗成的默认惯例
- struct: 很少有成员函数的时候，只放public的属性的时候
- 稍微复杂点的时候会去用class
- 可以用sizeof查看内存大小，在里面有变量有函数的时候不影响内存大小
- 影响内存大小的是里面的变量

# 结构体
- C++中的结构体是一种用户自定义的数据类型，它可以用来存储一组具有不同数据类型的数据。结构体可以被用来描述一个实体，如学生、联系人等。

- 结构体的基本语法如下：

```cpp
struct struct_name {
   data_type member1;
   data_type member2;
   // ...
};
```
- struct_name 是结构体的名称。
- member1, member2 是结构体成员，可以是任意数据类型。
- 下面是一个简单的结构体例子，定义了一个名为 Student 的结构体，包含三个成员：姓名、年龄和学号：

```cpp
struct Student {
   string name;
   int age;
   int id;
};

```
结构体变量可以通过使用结构体类型名和点运算符来访问结构体成员。
例如:

```cpp
Student s1;
s1.name = "John Doe";
s1.age = 21;
s1.id = 6;
```
- 看一个完整的案例

```cpp
// C语言的结构体
struct Student{
    char* name;
    int age;
    float score;
};

void struct_demo() {
    // 定义一个student1
    Student s1;
    s1.name = "cqy";
    s1.age = 18;
    s1.score = 100;
    // Student 2 
    Student s2;
    s2.name = "cxk";
    s2.age = 200;
    std::cout << "Student 1 name " << s1.name << " age: "<< s1.age << std::endl;
    std::cout << "Student 2 name " << s2.name << " age: "<< s2.age << std::endl;
}
```

# 类
## 类的定义
```cpp
class 类名
{
访问控制符:
    成员变量 //属性;
    成员函数 //方法
};
```
- C++中的结构体是一种用户自定义的数据类型，它可以用来存储一组具有不同数据类型的数据。结构体可以被用来描述一个实体，如学生、联系人等。
- 类的使用可以使得代码有更好的结构和高效性
- 后面的标准容器也是用类是实现的
- 类的首字母尽量大写
```cpp
// C++ 类
class Student{
public: 
    char* name;
    int age;
    float score;
};

void class_demo() {
    // 定义一个student1
    Student s1;
    s1.name = "cqy";
    s1.age = 18;
    s1.score = 100;
    // Student 2 
    Student s2;
    s2.name = "cxk";
    s2.age = 200;
    std::cout << "Student 1 name " << s1.name << " age: "<< s1.age << std::endl;
    std::cout << "Student 2 name " << s2.name << " age: "<< s2.age << std::endl;
}
```

## 在类外面实现类的方法(成员函数/激活函数)
- 成员变量通常是私有的，外界想知道成员变量很多时候得通过接口函数来
- public的成员函数也被叫做激活函数，有更好的封装性
- 下面这个案例有两个激活函数，先set再get
- 经常我们在写的时候，成员函数写在class里面，具体的操作写在外面
- 成员函数首字母小写
```cpp
// C++ 类
class Student{
public: 
    // 两个激活函数
    int get_age() { return age_; }
    void setAge(int age) {age_ = age; }
    void say();
private: 
    int age_;
    float score_;
};

void Student::say() {
    std::cout << "cqy age is: " << age_ << std::endl;
}

void class_demo() {
    // 定义一个student1
    Student s1;  // 实例化一个类对象
    s1.setAge(20);
    std::cout << "Student 1 Age: " << s1.get_age() << std::endl;
    s1.say();
}
```

```cpp
Student 1 Age: 20
cqy age is: 20
```
- 封装好这个类
class放到*.h文件

```cpp
// C++ 类
class Student{
public: 
    // 两个激活函数
    int get_age() { return age_; }
    void setAge(int age) {age_ = age; }
    void say();
private: 
    int age_;
    float score_;
};
```
- main.cpp文件

```cpp
#include <iostream>
#include "class_demo.h"

void Student::say() {
    std::cout << "cqy age is: " << age_ << std::endl;
    }

int main() {
    // 定义一个student1
    Student s1;  // 实例化一个类对象
    s1.setAge(20);
    std::cout << "Student 1 Age: " << s1.get_age() << std::endl;
    s1.say();
    return 0;
}
```
- 把类包进一个namespace里面，用#ifndef, #define, #endif 这三个预处理器指令组成了一组宏定义，也叫头文件保护符，在头文件中使用时可以保证只被包含一次
- 这种方式可以防止重复包含头文件，如果头文件已经被包含过了，那么后面再次包含该头文件时，就会被编译器忽略，避免重复定义符号、重复定义函数等问题。
- .h 文件

```cpp
// #pragma once
#ifndef CLASS_FIRST_
#define CLASS_FIRST_

namespace Demo{
// C++ 类
class Student{
public: 
    // 两个激活函数
    int get_age() { return age_; }
    void setAge(int age) {age_ = age; }
    void say();
private: 
    int age_;
    float score_;
};
} // namespace class_demo 

#endif
```

- main.cpp

```cpp
#include <iostream>
#include "class_demo.h"

namespace Demo{
void Student::say() {
    std::cout << "cqy age is: " << age_ << std::endl;
    }
}
int main() {
    // 定义一个student1
    Demo::Student s1;  // 实例化一个类对象
    s1.setAge(20);
    std::cout << "Student 1 Age: " << s1.get_age() << std::endl;
    s1.say();
    return 0;
}
```
## 类成员的访问权限
- 类默认的是private
- public可以直接访问
- private 是之后实例化的对象访问不了，上面Student s1实例化出来的s1是访问不了私有变量和私有函数的，这些私有变量和私有函数是供给类里面使用的
- 也可以理解为private是对实例化的对象private, 对成员函数都是可见的
- protected 用对象访问的时候没有区别，继承的时候就有区别了
 

## 类的初始化
- 简单的看一个C++11的案例

```cpp
#include <iostream> 

class Person {
public:
    // constructor with two parameters
    Person(std::string name = "default", int age = 0) : name_(name), age_(age) {}
    // member variables
    std::string name_;
    int age_;
};

int main() {
    Person p1("asd", 10);
    Person p2; 
    std::cout << "P1 name is: " << p1.name_ << std::endl;
    std::cout << "P2 name is: " << p2.name_ << std::endl;
    return 0;
}
```

- python里面有一个init构造函数，C++里面也是有的
- 实例化的有构造函数构造出实例化对象
- 如果你在类中定义了构造函数，那么编译器不再会自动生成默认构造函数。如果你还想使用默认构造函数，你需要自己显式地添加一个默认构造函数。

- 如果你在实例化类的时候不传递任何参数，那么如果类中没有默认构造函数，那么将会报错，因为编译器无法找到可用的构造函数。

- 如果你在类中定义了一个默认构造函数，那么在实例化类的时候不传递任何参数，那么将会调用你自己定义的默认构造函数。
- 如果你使用 C++11 以上版本，可以使用关键字 default 来显式地保留默认构造函数
- 下面也展示了两种初始化的方法
- 下面为*.h文件

```cpp
// #pragma once
#ifndef CLASS_FIRST_
#define CLASS_FIRST_

namespace Demo{
class Student{
public: 
    // 保留构造函数
    Student() = default;
    // 构造函数的声明
    Student(const char* name  , int age, float score);

public: 
    // 两个激活函数
    int get_age() { return age_; }
    void setAge(int age) {age_ = age; }
    void say();
    void setName(char* name) {name_ = name;} 
    
private: 
    // 在定义的时候给成员变量赋予默认值
    const char* name_ = nullptr;
    int age_ = 0;
    float score_ = 0;
};
} // namespace class_demo 


#endif 
```
- main.cpp文件

```cpp
#include <iostream>
#include "class_demo.h"

namespace Demo{
// 类的初始化 
Student::Student(const char* name, int age, float score): name_(name), age_(age),score_(score) {
        std::cout << "==============start Construct===============" << std::endl;
        // 与上面同等写法
        // name_ = name;
        // age_ = age;
        // score_ = score;
        std::cout << "================end Construct===============" << std::endl;
    } 

void Student::say() {
    std::cout << "cqy age is: " << age_ << std::endl;
    }
}
int main() {
    // 定义一个student1
    Demo::Student s1("cqy", 20, 100);  // 实例化一个类对象, 这里调用我们定义的构造函数
    Demo::Student s2;  // 这里调用默认构造函数
    s1.setAge(20);
    std::cout << "Student 1 Age: " << s1.get_age() << std::endl;
    s1.say();
    return 0;
}
```
## 看一个C++11的例子
- const修饰 当函数是 const 时，表示它不会改变对象的状态。这是一种好的编程习惯，因为它可以防止意外修改对象的状态，并且可以让编译器检查错误。
```cpp
#include <iostream>

class Shape {
public:
  // 保留默认构造函数
  Shape() = default;
  // 自己定义一个构造函数初始化, C++ 11语法
  Shape(int width, int height): width_(width), height_(height) {}
  //  当函数是 const 时，表示它不会改变对象的状态。这是一种好的编程习惯，
  // 因为它可以防止意外修改对象的状态
  int GetWidth() const {return width_;}
  int GetHeight() const {return height_;}

  // 改变对象状态的函数
  // 改变对象状态，就是通过函数来修改对象的成员变量的值
  void setWidth(int width) {width_ = width;}
  void setHeight(int height) {height_ = height;}
  int GetArea() const {return width_ * height_;}

private:
  // 定义初始化参数，不写的话自动给0
  int width_ = 10;
  int height_ = 5;  
};

int main() {
    // 初始化一个shape
    Shape shape;
    std::cout << "默认初始化的width: " << shape.GetWidth() << std::endl;
    std::cout << "默认初始化的Height: " << shape.GetHeight() << std::endl; 
    std::cout << "默认初始化的Area: " << shape.GetArea() << std::endl; 
    return 0;
}
```

## C++里面的this特殊指针
- 在 C++ 中，this 是一个特殊的指针，它指向当前对象。当我们在类的函数中使用 this-> 时，它会指向调用该函数的对象。

- 比如说，在下面的代码中:

```cpp
class Shape {
 public:
  Shape() = default;
  Shape(int width, int height) : width_(width), height_(height) {}
  int GetWidth() const { return width_; }
  void SetWidth(int width) { width_ = width; }
  void SetWidthThroughThis(int width) { this->width_ = width; }
  private:
  int width_;
};
```
- 如果我们这样调用 SetWidth(int width) 函数:
```cpp
Shape shape;
shape.SetWidth(5);

```
- 这个函数就会把shape对象的 width_ 成员变量赋值为 5。

- 而如果我们调用 SetWidthThroughThis(int width) 函数，就会像这样

```cpp
shape.SetWidthThroughThis(5);
```
- 这个函数同样会把 shape 对象的 width_ 成员变量赋值为 5，不同的是它使用了 this 指针来访问 width_ 成员变量。

使用 this-> 是一种好的编程习惯，它可以在代码中清晰地表示出当前访问的是对象的成员变量，而不是局部变量。这样可以避免命名冲突，提高代码的可读性。

另外，在某些情况下，使用 this-> 可以解决默认参数和局部变量之间的命名冲突。

总之，使用 this-> 是一种可以提高代码可读性和健壮性的好的编程习惯。

# 静态变量，函数
- 静态变量和静态函数都是类的成员，它们与类本身有关，而不是与对象有关。
- 本身跟类的互动不频繁

- 静态变量是类的全局变量，它只有一个实例，不管类有多少个对象，它们共享同一个静态变量。 通过类名::来访问。
- 在这个例子中，我们定义了一个静态变量 total_shapes_ 和两个静态函数 GetTotalShapes() 和 IncreaseTotalShapes()。 
- 静态变量 total_shapes_ 不属于任何一个对象，所有对象共享它。
- 静态函数 GetTotalShapes() 返回静态变量 total_shapes_ 的值， IncreaseTotalShapes() 函数增加 total_shapes_ 的值。

```cpp
#include <iostream>

class Shape {
 public:
  Shape() = default;
  Shape(int width, int height) : width_(width), height_(height) {}
  int GetWidth() const { return width_; }
  void SetWidth(int width) { width_ = width; }
  // 静态变量
  static int GetTotalShapes() { return total_shapes_; }
  // 静态函数
  static void IncreaseTotalShapes() { total_shapes_++; }
 private:
  int width_;
  int height_;
  // 静态变量
static int total_shapes_;
};

int Shape::total_shapes_ = 0;

int main() {
Shape shape1(3, 4);
Shape shape2(5, 6);
std::cout << "Total Shapes: " << Shape::GetTotalShapes() << std::endl;
Shape::IncreaseTotalShapes();
Shape::IncreaseTotalShapes();
std::cout << "Total Shapes: " << Shape::GetTotalShapes() << std::endl;
return 0;
}
```


# 友元函数/类
- 在 C++ 中，友元函数是一种特殊的函数，它可以访问类的私有成员变量和私有成员函数。这是因为类的私有成员变量和私有成员函数是只能被类的成员函数访问的，而友元函数不属于类的成员函数。

- 友元函数通过在类中用关键字 friend 声明来实现。
- 友元类改的是class的状态，不是实例化出来的object的状态
- 友元类/函数使用的时都要传入实例化的object 

- 这是一个友元函数的案例：

```cpp
class MyClass {
  friend void MyFriendFunction(MyClass& my_class);
  private:
  int x_;
};

void MyFriendFunction(MyClass& my_class) {
  my_class.x_ = 5; // 访问类的私有成员变量
}

```
- 在这个例子中，MyFriendFunction 是一个友元函数，它可以访问 MyClass 类的私有成员变量 x_ 。因为在 MyClass 类中使用了 friend 关键字来声明 MyFriendFunction 是友元函数。
另外，友元函数可以是一个类的成员函数，也可以是一个全局函数。

- 需要注意的是，友元函数并不属于类的成员函数，它不能访问类的 this 指针。
- 完整的一个大代码

```cpp
#include <iostream>

using namespace std;

class Box {
public:
  // 声明友元函数
  friend void printWidth(Box& box);
  // 声明友元类
  friend class BigBox;
  // 保留默认构造函数
  Box() = default;

  // 自定义构造函数
  Box(int width): width_(width) {}

  void setWidth(float width) {width_ = width;}
  int getWidth() {return width_;}

private:
  float width_ = 5;
};

class BigBox{
public:
  // 写一个函数更改变量
   void print(int width, Box& box) {
      box.setWidth(width);
      cout << "width of box: " << box.width_ << endl;
   }
};

void Box_test() {
  Box box;
  cout << "默认的width: " << box.getWidth() << endl;
  box.setWidth(6);
  cout << "更改后的width: " << box.getWidth() << endl;
}

void BigBox_test() {
  Box box;
  BigBox bigbox;
  box.setWidth(9.0);
  bigbox.print(20, box);  // 这里就把Box的width_改了，不是改实例化出来的box
  cout << "box width after friend class change: " << box.getWidth() <<endl;
}

void printWidth(Box& box) {
  cout << "friend box width_ is: " << box.width_ << endl;
}
int main() {
  // Box_test();
  // BigBox_test();
  Box box;
  printWidth(box);
  return 0;
}
```
# 类的继承
- 简单看个案例，子类可以用父类的成员函数和成员变量，但是只能用protected 和 public
- protected: 可以用来修饰一个类里面的成员变量和成员函数，实例化的对象依然不能访问，但是子类/派生类可以访问
- 用public，private,protected 来外加限定继承关系
- 用private，proteced 继承只能访问到protected的成员变量/函数
- 下面是一个public继承的案例

```cpp
#include <iostream>

class Shape{
public:
  // 保留默认构造函数
  Shape() = default;    
  Shape(int width, int height): width_(width), height_(height) {}

// 成员函数
public:
  void setWidth(int width) {width_ = width;}
  void setHeight(int height) {height_ = height;}

// 成员变量
protected:
  int width_ = 5;
  int height_ = 5;
};

class Rectangle: public Shape {
public:
  // 成员函数
  int getArea() {
    // 继承的class Shape 的width_, height_
    return width_ * height_; 
  } 
};

int main() {
    Rectangle rect;
    // 继承了Shape就可以用他的成员函数
    rect.setHeight(10);
    rect.setWidth(10);
    std::cout << "Area: " << rect.getArea() << std::endl;
    return 0;
}
```

## 多继承
- 多加一个


```cpp
#include <iostream>

class Shape{
public:
  // 保留默认构造函数
  Shape() = default;    
  Shape(int width, int height): width_(width), height_(height) {}

// 成员函数
public:
  void setWidth(int width) {width_ = width;}
  void setHeight(int height) {height_ = height;}

// 成员变量
protected:
  int width_ = 5;
  int height_ = 5;
};

class Cost {
public: 
    auto getCost(int area) {return area * 70;}
};

class Rectangle: public Shape, public Cost {
public:
  // 成员函数
  int getArea() {
    // 继承的class Shape 的width_, height_
    return width_ * height_; 
  } 
};


int main() {
    Rectangle rect;
    // 继承了Shape就可以用他的成员函数
    rect.setHeight(10);
    rect.setWidth(10);
    std::cout << "Area: " << rect.getArea() << std::endl;
    auto area = rect.getArea(); 
    auto cost = rect.getCost(area);
    std::cout << "Cost of rect is: " << cost << std::endl;
    return 0;
}
```
## 菱形继承
- 简单看一个菱形继承的案例
```cpp
        //     A
        //    / \ 
        //   B   C 
        //   \   /
        //     D



#include <iostream>

using namespace std;

class A{
public: 
  void func() {
    std::cout << "Class A" << std::endl;
  }
protected:
int base_;
};

class B: public A{
public: 

  
protected:
int b_;
};

class C: public A{
public: 

  
protected:
int c_;
};

class D: public B, public C{
public: 

  
protected:
int d_;
};

int main() {
    // 实例化b
    B b;
    b.func(); 
    // 实例化d
    D d;
    d.func(); // 不可以访问了
    return 0;
}
```
- B可以访问，但是D不能访问
- 因为func() 是来自于A的，B，C都继承自A，编译器就不知道该从哪条线来访问func(); 就会报错

- 第二种解决办法： 指明怎么访问的就行了把 d.func(); 改成
```cpp
d.B::func();
```
- 第二种解决办法： 继承的时候写上 virtual public, d.func();就能够访问了
- 这种方法维护了一个续表，通过续表可以访问到func()的地址，这样避免了每次实例化单独存一个空间。 

## 继承的一些特殊情况 

- 在派生类/子类里边有一样的变量名，访问的时候访问的是子类的变量
- 嵌套变量的作用域（成员里面的成员变量会覆盖父类里面的成员变量）    
- 想使用父类里面的成员变量，需要 父类::变量(来源于父类)
- 先去小作用域搜索，再去大作用域搜索 sizeof(object) 查看
- 下面案例中的height_, width_在父类和子类都有的
- 不过一般不会有这些，这种设计是很差的，我们一般维护的成员变量也就是一份
- 但是函数是会重载的
```cpp
#include <iostream>

class Shape{
public:
  // 保留默认构造函数
  Shape() = default;    
  Shape(int width, int height): width_(width), height_(height) {}

// 成员函数
public:
  void setWidth(int width) {width_ = width;}
  void setHeight(int height) {height_ = height;}

// 成员变量
protected:
  int width_ = 5;
  int height_ = 5;
};

class Cost {
public: 
    auto getCost(int area) {return area * 70;}
};

class Rectangle: public Shape, public Cost {
public:
  // 成员函数
  int getArea() {
    // 继承的class Shape 的width_, height_
    return width_ * height_; 
  } 

  int getShapeArea() {
    return Shape::height_ * Shape::width_;
  }

private:
  int width_ =100;  // 嵌套变量的作用域：
  int height_ = 700;
};


int main() {
    Rectangle rect;
    // 继承了Shape就可以用他的成员函数
    rect.setHeight(10);
    rect.setWidth(10);
    std::cout << "Area: " << rect.getArea() << std::endl;
    auto area = rect.getArea(); 
    auto area2 = rect.getShapeArea();
    auto cost = rect.getCost(area);
    auto cost2 = rect.getCost(area2);
    std::cout << "Cost1 of rect is: " << cost << std::endl;
    std::cout << "Cost2 of rect is: " << cost2 << std::endl;
    std::cout << "Cost2 of rect is: " << sizeof(Shape) << std::endl;
    
    
    return 0;
}
```

# 重载与重写
- 子类的函数会重载父类的函数
- 理解三种 over: overwirte overload override
- overwrite: 子类覆盖父类的的成员变量/函数
- overload: 函数重载: 在一个类下面有两个相同名的函数，按照返回类型来重载函数，或者按照传参需求来重载函数，来匹配函数
- 这个案例就是看下面怎么调用决定怎么返回
```cpp
  auto getCost(int area) {return area * 70;}
  
  void getCost() {
    std::cout << "We are in getCost func in calss rect " << std::endl;
    
  }
```
```cpp
  void getCost(int area) {std::cout << "area is " << area << std::endl;}
  
  void getCost() {
    std::cout << "We are in getCost func in calss rect " << std::endl;
    
  }
```
- 如果子类父类都有相同名字的函数，但是参数不一样，子类依然可以把父类的函数覆盖掉，就会overwirte, 哪怕按照父类的格式写一样会出问题
## **实现函数重载的条件**

* 同一个作用域
* 参数个数不同
* 参数类型不同
* 参数顺序不同
 ```cpp
void func(){}
void func(int x){}
void func(char x){}
void func(int x, int y){}
void func(int x, char y){}
void func(char y, int x){}
 ```