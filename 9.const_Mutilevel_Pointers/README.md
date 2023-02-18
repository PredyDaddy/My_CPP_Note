# 1. Const的详解
## 1.1 const修饰普通变量(被修饰的对象是只读的)
1. 在C++中，如果一个变量被声明为const，那么它的值是不能被修改的，因此必须在声明时就为其指定一个初始值。如果没有给const变量指定初始值，则编译器无法确定它的值是什么，这可能会导致代码错误或不可预测的行为。
2. 指针变量被const修饰的时候，不初始化也不会报错，因为他被定义的时候已经有指向的地方了，只不过地址是未知的，建议初始化，避免不可预测的行为。
3. 后面会对const结合指针进行详细解释
```cpp
int main()
{
  // a是只读的，必须在定义的时候给一个初始值
  // 以便于编译器能够正常的初始化
  // const int a;  这句话就会报错
  const int a = 0;

  // 这样不会报错的
  const int *p;

  // 建议给指针一个初始化
  // p2是一个指向const int的类型的指针, const修饰*p，*p不能被修改
  // 可以通过修改b的值，p2指向的地址没变，依然是指向b
  int b = 10;
  const int *p2 = &b;
  // *p2 = 12; // 被const修饰成只读对象，这样写会报错
  b = 11;
  cout << *p2 << endl;
  
  // 所以比较规范的const 指针写法是
  const int c = 10;
  const int *p3 = &c; 
  return 0;
}
```

## 1.2 const修饰成员变量, 成员函数
1. const修饰类的成员变量，表示成员常量，不能被修改，同时它只能在初始化列表中赋值。
2. 被const修饰的成员函数是**常成员函数**，不改变对象的**成员变量**， 不能调用
3. const修饰的成员函数不可以改变成员变量和调用非const的成员函数
4. 全局函数不可以被const修饰
```cpp
class A
{
public:
  A() {}
  A(int value) : _value(value) {} // 只能通过这样赋值
  // void get_func(){_value++;} // 会报错的

  void func2() const
  {
    cout << "Legal const function " << endl;
  }

  // const修饰的成员函数不可以改变成员变量和调用非const的成员函数
  // void func3() const{value2++;} 会报错的

  // 只能调用const修饰的成员变量
  void func4() const { func5(); }
  void func5() const {}

public:
  const int _value = 10; // 不能被修改
  int value2;
};

// 全局函数不可以被const修饰
// void func_global() const {} // 会报错的


int main()
{
  A a(100); // 输出 100
  cout << a._value << endl;

  A a1; // 输出 10
  cout << a1._value << endl;

  a1.func4();

  return 0;
}
```


# 1.3 const修饰对象
1. const修饰的对象为常对象，其中任何成员都不允许修改
2. 常对象只能访问类中的const函数
3. 长对象可以访问public成员变量，但是不能被修改
```cpp
class A
{
public:
  int x = 0;

public:
  void func()
  {
    cout << "Normal Fuction" << endl;
  }

  void func1() const
  {
    cout << "const func" << endl;
  }
};

int main()
{
  A a;
  a.x = 100;
  cout << a.x << endl;

  const A a1;

  // a1.x = 100; // 会报错，不能修改任何成员
  // a1.func();     // 会报错，不能修改任何成员
  a1.func1();  // 可以访问const成员函数
  return 0;
}
```

# 1.4 const修饰引用
1. 引用参数在函数内不可以改变
2. 引用指向某个常量时，需要用const修饰
```cpp
void func1(const int &t)
{
  // t++; // 引用参数在函数内不可以改变
}

int main()
{
  int a = 19;
  int &b = a;
  b = 20;
  cout << a << endl;

  const int c = 19;
  const int &d = c; // 引用指向某个常量时，需要用const修饰
  // d = 20; // 会报错

  return 0;
}
```

# 1.5 const修饰函数返回值
1. 在 C++ 中，可以使用 const 关键字修饰成员函数的返回值类型。这意味着，通过调用该函数返回的结果将被视为一个常量，不能被修改。


# 2. const与指针的结合
## 2.1 指针的复习: 
```cpp
int main()
{   
    int a = 10;   // 定义变量a
    int *p = &a;  // &a取地址，赋给指针变量*p
    int b = 20;   // 定义变量b
    p = &b;       // 让指针变量p指向b的地址
    cout << (*p) << endl; // 输出指针指向地址的内存，b=20
    *p = 30;      // 这里更改指针指向的内存，
    cout << b << endl; // 更改后内存是30
    return 0;
}
```
## 2.2 const的定义
1. 普通的变量可以作为左值，如果变量被const修饰过后是不能够成为左值的
2. 初始化完成后，值不能被修改
3. 左值是可以被赋值和修改的
4. const只能保证作为左值不被修改，但是内存是可以改的
5. C++ const修饰的变量必须初始化，叫常量  
6. C 中const修饰的变量不一定要初始化
7. 如果初始化的值是一个变量，叫常变量，变量的值只有在运行的时候才知道
8. C++ 中const修饰的变量可以作为数组的下标但是C中不可以
```cpp
int main()
{
    const int a = 20;
    int array[a] = {};
    return 0;
}
```
## 2.3修改内存案例, 可修改左值和不可修改左值的操作
被const修饰，左值不会改，但是可以改地址
a的内存已经被更改成20了，出现a，用常量替代
```cpp
int main()
{
    // 可修改左值的案例
    int b = 10;
    int* ptr1 = &b; // 通过引用获取地址
    *ptr1 = 20;
    cout << "b: " << b << " ptr1: " << *ptr1 << endl;

    // 不可修改左值的案例
    const int a = 10;
    int *ptr2 = (int*)&a;
    *ptr2 = 20;
    cout << "a: " << a << " ptr2: " << *ptr2 << endl;
    return 0;
}
```
```cpp
b: 20 ptr1: 20
a: 10 ptr2: 20
```
# 3. Const与一级指针的结合
## 3.1 先理解一级指针和二级指针
C++ 中的一级指针指的是普通指针，它指向一个普通变量的地址。二级指针指的是指向一级指针的指针，它指向一个普通指针的地址。
```cpp
int a = 10;
int *p1 = &a; // p1 是一级指针，指向变量 a 的地址
int **p2 = &p1; // p2 是二级指针，指向指针 p1 的地址
```
在这个例子中，p1 是一级指针，它指向了变量 a 的地址。p2 是二级指针，它指向了一级指针 p1 的地址。

## 3.2 注意事项
1. 不能把常量的地址泄露给一个普通的指针或者普通的
```cpp
int main()
{   
    int a;
    int* ptr1 = &a;

    const int b = 10; // C++ 常量必须初始化
    // int* ptr2 = &b;  这样会报错的
    return 0;
}
```
## 3.3 const与指针几种不同的结合方法
**const修饰的是离他最近的类型, 去掉类型后修饰的表达式**
- 搞明白修饰的是指针的指向还是指针指向的内存
- const int *p;
- int const *p; 
- 这两种是一样的，*p必须指向int类型，但是可以修改指向
```cpp
int main()
{   
    int a = 10;
    const int *p = &a;
    int b = 20;
    float c = 32.0;
    p = &b;     // 更改p的指向，指到b
    cout << *p << endl;
    // p = &c;     // 报错，指向非int类型
    // *p = 20;    // 报错  不能通过指针修改内存的值
    return 0;
}
```

int *const  p;
1. 修饰的是p, 这种p依然是指针，但是不能更改指向
2. *p 没有被修饰，也就是说值是可以改的
```cpp
int main()
{   
    int a = 10;
    int b = 20;
    int *const p = &a;
    *p = 20;
    cout << a << endl;
    // p = &b; // 会报错，指针指向不能更改
    return 0;
}
```
const int *const p; 
p不能指向其他内存，也不能更改指向内存的值

## 3.4 const和指针的类型转换公式:
1. int* <= const int* 是错误的，这是一个类型错误
2. const int* <= int*  可以的
3. 下面都是 const int* <= int *
4. 错误的原因是不能把一个常量的地址赋给一个普通的指针
```cpp
int main()
{   
    int a = 10;
    int *p1 = &a;
    const int *p2 = p1; 
    const int *p3 = &a; 
    int *const p3 = &a;
    return 0;
}
```
1. int* <= const int*  案例, 会出现编译报错
```cpp
int main()
{   
    int a = 10;
    int *p1 = &a;
    const int *p = &a; 
    int *p2 = p;
    return 0;
}
```
这是一个类型转换的错误，跟有没有a没关系, 换成空指针也是一样的，不可以把整形常量的地址泄露给正常的指针
```cpp
int main()
{   
    const int *p = nullptr;  // p类型是 int const * 不能泄露给正常的指针
    int *p2 = p;
    return 0;
}
```

# 4. const和二级指针的结合
## 4.1 二级指针
1. 二级指针指向一个int *的地址
2. &(*p)的数据类型是int ** 
```cpp
int main()
int main()
{   
    int a = 10;
    int b = 20;
    int *p = &a;
    int **q = &p;
    // int *q = &p; // &p 是一个 int**的类型
    
    *q = &b; // 更改二级指针的指向
    cout << a << endl;
    return 0;
}
```
## 4.2 几种不同的结合方法
1. const除去类型修饰的表达式
2. const int **q;  
-修饰的是**q, *q, q是可以被赋值的
3. int *const* q; 修饰的是*q, **q, q是可以更改的
4. int **const q; 修饰的是q, q是不可以更改的

## 4.3 二级指针公式(类型转换) 
1. int** <= const int** 错误
2. const int** <= int** 错误
3. 跟一级指针不一样，两边都要有const，不然就是类型的错误
4. int *const* <= int** 这个可以，因为左边const修饰的是一级指针
5. 同样错误的原因也是不能够把常量的地址泄露一个普通的指针

## 4.4 二级指针结合const防止报错的方法
1. 这是一个错误案例，下面两种改法
```cpp
int main()
{   
    int a = 10;
    int *p = &a;
    const int **q = &p;
    return 0;
}
```
2. 这样就不是泄露给普通的指针
```cpp
int main()
{   
    int a = 10;
    const int *p = &a;
    const int **q = &p;
    return 0;
}
```
3. 下面这种改法直接修饰*q，直接不让你赋值了
```cpp
int main()
{   
    int a = 10;
    const int *p = &a;
    const int *const*q = &p;
    return 0;
}
```
# 4.5 从几道题目训练
1. 没有const的版本  int * <= int *
```cpp
int a = 10;
    int *p1 = &a;   // 把a的地址赋给指针变量p1
    int *p2 = p1;   // 把p1的地址赋给p2
    *p2 = 20;       
    cout << a << endl;
```
2. int * <= int *   (不会出现编译错误)
```cpp
int a = 10;
    int *const p = &a; // p: int * 
    int *q = p;        // int * <= int *
```
3. int * <= const int * (会出现编译错误)
```cpp
int a = 10;
    const int *p = &a; // p: const int * 
     int *q = p;  //  int * <= const int *
```
4. int * <= int *   (不会出现编译错误)
```cpp
int a = 10;
    int * const p = &a; // p: int * 
    int * const q = p;  //  int * <= const int *
```
5. const int * <= int *
```cpp
int a = 10;
int * const p = &a; // p: int * 
const int *q = p;  //  const int * <= int *
```



