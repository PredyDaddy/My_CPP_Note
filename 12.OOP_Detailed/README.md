
# OOP: 设计思想, this指针, 构造函数，析构函数，浅拷贝深拷贝，构造函数初始化列表，类的各种成员，指向各类成员的指针
# 1. OOP编程, this 指针
## 1.1 基础概念
1. C:各种各样的函数的定义, struct
2. C++: 类: => 实体的抽象类型
3. 实体: 属性, 行为 -》 ADT(abstract data type)
   - 属性: 成员变量
   - 行为: 成员方法
4. 怎么理解OOP思想: 分析场景的实体，通过分析试图的属性和行为
5. OOP语言的四大特征: 
   - 抽象
   - 封装/隐藏 
   - 继承 
   - 多态
6. 封装和隐藏通过访问限定符来体现
   - public
   - private 
   - protected
7. 类是不占空间的，实例化成对象后才占空间，对象的内存在栈上, 对象的内存大小只和成员变量有关
8. 属性一般是私有的，给外部提供公有的方法，来访问私有的属性
   - 解释: 我会唱歌，你不能夺走我唱歌的能力，但是你能通过公有的访问我，让我唱一首歌
9. 类体内实现的方法，自动转成inline内联函数 
## 1.2 一个OOP的思想案例: 用类描述商品实体
1. 私有的成员变量: 商品的名字，价格，量
2. 初始化商品的数据的构造函数
3. 提供查询(get) 接受(set)外部私有变量的方法
4. 类里面的私有变量写上_在前面
5. 提供一个show()方法查询对象的信息，因为商品的属性只有在对象的时候才会访问，也才会占用栈的内存
6. 用C风格的字符串定义的私有属性，其实是定义了一个char类型的数组，后面在类方法和构造函数里面，用指针指向一个字符串，然后用strcpy()把地址内存复制给他
   - 在 C++ 中字符数组是不可修改的，但是字符指针可以直接指向字符串常量，在函数内部使用该字符指针是可以访问字符串常量的。
7. 这个案例中，怎么看类的内存大小？
   - char[20], double 8字节, int 4字节
   - 对齐: 8是最大的， 20个char 补4个，24个字节
   - int 4 字节，补4个字节 对齐  
   - 内存大小: 24 + 8 + 8  = 40 字节

```cpp
#include <iostream>
#include <cstring>


using namespace std;

const int NAME_LEN = 20;


class CGoods
{
public:   // 给外部提供公有的方法，来访问私有的属性
    // 做商品数据初始化, char * 
    void init(const char *name, double price, int amount);
    // 打印商品信息
    void show();

    // 给成员变量getXXX或者setXXX
    // set函数用于接受外部的变量
    void setName(const char *name) {strcpy(_name, name); }
    void setPrice(double price) {_price = price; } 
    void setAmount(int amount) { _amount = amount; }

    // get函数用于提供外部查询这个类的私有属性
    const char* getName() { return _name; }
    double getPrice() { return _price; }
    int getAmout() { return _amount; }
private:  // 属性一般是私有的
    char _name[NAME_LEN];
    double _price;
    int _amount;
};

// 类外定义成员方法
void CGoods::init(const char *name, double price, int amount)
{
    strcpy(_name, name); // 把指针指向的地址内存复制给_name
    _price = price;
    _amount = amount;
}

void CGoods::show()
{
    cout << "name: " << _name << endl;
    cout << "price: " << _price << endl;
    cout << "amount: " << _amount << endl;
}

int main()
{
    CGoods good; // 实例化一个对象
    good.init("面包", 10.0, 200);
    good.setPrice(20.0);
    // good.setName("奶油面包");
    good.show();
    
    CGoods good2;
    good2.init("商品2",  20.0,  999);
    good2.show();
    return 0;
}
```
# 2. this指针
1. CGoods可以定义无数对象，每一个对象都有自己的成员变量，他们共享一套成员方法，放在代码段上的, 用this指针区分对象
2. this指针就是用来区分方法对应的是哪个对象
3.  类的成员方法一经编译，所有方法参数，都会加一个this指针，接受调用该方法的对象地址，CGoods *this 
4.  例如上一个CGoods的初始化为 init(const char *name, double price, int amount)
   - 实际上是init(&goods1, const char *name, double price, int amount)
   - 传入一个引用，才知道调用的是哪一个对象的地址

# 3. OOP 练习，用OOP写一个顺序栈
## 注意事项
1. 释放了内存，但是指针还在，要把指针变成空指针
2. 用top, 栈顶元素的位置来判断空，满，入栈升高，出栈降低
3. 压栈把第二个元素往下压，所以_pstack[0] _pstack[1]依次放元素
4. 栈顶是-1的时候就视为空
5. 动态扩容的时候不用mmcpoy，后面讨论深拷贝会讲
```cpp
#include <iostream>
using namespace std;

class SeqStack
{
public:
    void init(int size = 10)
    {
        _pstack = new int[size];
        _top = -1;
        _size = size;
    }

    void release()
    {
        delete []_pstack; // 释放了指向内存的地址，但是指针还在
        _pstack = nullptr; // 把这个指针变成空指针
    }

    // 压栈
    void push(int val)
    {
        if (full())
        {
            resize();
        }

        _top++;  
        _pstack[_top] = val; // 初始化: _pstack[0]放val
                               // 第二个入栈: _pstack[1]
        // _pstack[++_top];  
    }

    // 出栈
    void pop()
    {
        if (empty())
        {
            return;
        }
        --_top;           
    }

    // 获取栈顶元素
    int top()
    {
        return _pstack[_top];
    }

    // 判断是否为空
    bool empty() { return _top == -1; }
    // 判断是否满了
    bool full() { return _size - 1; } 

   

  
private:
    int *_pstack; // 动态开辟数组，存储顺序栈的元素
    int _top; // 指向栈顶元素的位置
    int _size; // 数组扩容的总大小

    void resize()
    {
        int *ptmp = new int[_size * 2];
        for (int i = 0; i < _size; i++)
        {
            ptmp[i] = _pstack[i];
        }
        delete []_pstack; // 释放内存
        _pstack = ptmp;  // 指向内存的指针指向新的地方
        _size *= 2; 
    }
};

int main()
{
    SeqStack s;
    s.init(5);
    for (int i = 0; i < 15; i++)
    {
        s.push(rand() % 100);
    }
    while (!s.empty())
    {
        cout << s.top() << " ";
        s.pop();
    }

    s.release();
    return 0;
}
```
# 4. 构造函数和解析函数
1. 函数的名字和类名一样
2. 没有返回值
3. 构造函数，开辟资源，析构函数，释放资源
4. 在return 0; 这一行执行析构函数
5. 下面是对照，实例化后可以看到函数开始前调用构造函数，结束调用析构函数
6. 实例化对象: 1. 在栈上开辟内存，2. 调用构造函数
7. 运行下面代码，先构造的后析构，后构造的先析构 
8. 析构函数只能有一个，构造函数可以有多个，叫构造函数的重载
9. 可以自己调用析构函数，掉用完后对象不存在，但是内存还在！再调用就是堆内存的非法访问了
```cpp
#include <iostream>
using namespace std;

class SeqStack
{
public:

    SeqStack(int size = 10) 
    {   
        cout << this << "SeqStack()" << endl;
        _pstack = new int[size];
        _top = -1;
        _size = size;
    }

    ~SeqStack()
    {   
        cout << this << "~SeqStack()" << endl;
        delete []_pstack; // 释放了指向内存的地址，但是指针还在
        _pstack = nullptr; // 把这个指针变成空指针
    }

    // 压栈
    void push(int val)
    {
        if (full())
        {
            resize();
        }

        _top++;  
        _pstack[_top] = val; // 初始化: _pstack[0]放val
                               // 第二个入栈: _pstack[1]
        // _pstack[++_top];  
    }

    // 出栈
    void pop()
    {
        if (empty())
        {
            return;
        }
        --_top;           
    }

    // 获取栈顶元素
    int top()
    {
        return _pstack[_top];
    }

    // 判断是否为空
    bool empty() { return _top == -1; }
    // 判断是否满了
    bool full() { return _size - 1; } 

   

  
private:
    int *_pstack; // 动态开辟数组，存储顺序栈的元素
    int _top; // 指向栈顶元素的位置
    int _size; // 数组扩容的总大小

    void resize()
    {
        int *ptmp = new int[_size * 2];
        for (int i = 0; i < _size; i++)
        {
            ptmp[i] = _pstack[i];
        }
        delete []_pstack; // 释放内存
        _pstack = ptmp;  // 指向内存的指针指向新的地方
        _size *= 2; 
    }
};

int main()
{
    SeqStack s;
    SeqStack s1;
    
    for (int i = 0; i < 15; i++)
    {
        s.push(rand() % 100);
    }
    while (!s.empty())
    {
        cout << s.top() << " ";
        s.pop();
    }

    return 0;
}
```

# 5. 对象的浅拷贝和深拷贝
1. 没有提供任何构造函数的时候，回味我们生成默认构造函数和默认析构函数，是函数
2. 还是以刚刚的顺序列为例子，看一个拷贝构造函数
```cpp
int main()
{
    SeqStack s;  
    SeqStack s1;
    SeqStack s2(s1);  // 拷贝构造函数
    return 0;
}
```
3. 上面的案例会报错，因为拷贝构造函数的时候，会把成员变量(私有属性)也拷贝过来，而int *_pstack;指向一个堆内存，两边都指向一个堆内存，s2调用析构函数释放堆内存，s1的指针依然存在，就变成了野指针。下图紫色区域为堆内存，黑色为栈内存，也可以看出来这个指针指向的不是类的内存
![在这里插入图片描述](https://img-blog.csdnimg.cn/7055a26f85cd48029ba58fb59194824f.png)
4. 对象的成员变量有指针指向对象外部的资源容易出问题

## 5.2 深拷贝函数: 自定义拷贝函数
1. 对象浅拷贝有问题，要自定义拷贝构造函数
```cpp
    // 自定义拷贝构造函数
    SeqStack(const SeqStack &src)
    {
        cout << "自定义拷贝函数" << endl;
        // _pstack = src._pstack; // 这个是浅拷贝
        _pstack = new int[src._size];
        for (int i = 0; i < src._top; ++i)
        {
            _pstack[i] = src._pstack[i];
        }
        _top = src._top;
        _size = src._size;
    }
```
2. 这样就指向新的堆内存
![在这里插入图片描述](https://img-blog.csdnimg.cn/381acd53f23142d2b9513abf8f0c5717.png)

## 5.3 为什么深拷贝不用memcopy用for循环?
1. 假设数组里面放着对象，里面还有指针，那就会出问题, 用memcopy又变成浅拷贝了
## 5.4 赋值重载函数
```cpp
int main()
{
    SeqStack s;  
    SeqStack s1(10);
    SeqStack s2(s1);
    s2 = s1;   // 赋值操作: 需要默认赋值构造函数
    return 0;
}
```
1. 又变成浅拷贝了
2. 本来s2指向独属于自己的外部的资源，赋值让s2里面的指针指向s1的独属堆内存
3. 这样更麻烦，s2丢掉了自己的独属的堆内存，连释放都做不到了所以需要一个赋值重载函数, 这个就是加一个释放当前内存的
4. 如图所示
![在这里插入图片描述](https://img-blog.csdnimg.cn/d85ccad5ba2241a08fdf9221a7ecfddc.png)

```cpp
    // 赋值重载函数
    void operator=(const SeqStack &src)
    {
        cout << "赋值重载函数" << endl;
        delete []_pstack;
        // _pstack = src._pstack; // 这个是浅拷贝
        _pstack = new int[src._size];
        for (int i = 0; i < src._top; ++i)
        {
            _pstack[i] = src._pstack[i];
        }
        _top = src._top;
        _size = src._size; 
    }
```

## 5.5 完整版代码: 赋值重载函数+拷贝构造函数

```cpp
#include <iostream>
using namespace std;

class SeqStack
{
public:
    // 构造函数
    SeqStack(int size = 10) 
    {   
        cout << this << "SeqStack()" << endl;
        _pstack = new int[size];
        _top = -1;
        _size = size;
    }
    // 自定义拷贝构造函数
    SeqStack(const SeqStack &src)
    {
        cout << "自定义拷贝函数" << endl;
        // _pstack = src._pstack; // 这个是浅拷贝
        _pstack = new int[src._size];
        for (int i = 0; i < src._top; ++i)
        {
            _pstack[i] = src._pstack[i];
        }
        _top = src._top;
        _size = src._size;
    }

    // 赋值重载函数
    void operator=(const SeqStack &src)
    {
        cout << "赋值重载函数" << endl;
        delete []_pstack;
        // _pstack = src._pstack; // 这个是浅拷贝
        _pstack = new int[src._size];
        for (int i = 0; i < src._top; ++i)
        {
            _pstack[i] = src._pstack[i];
        }
        _top = src._top;
        _size = src._size; 
    }

    ~SeqStack()
    {   
        cout << this << "~SeqStack()" << endl;
        delete []_pstack; // 释放了指向内存的地址，但是指针还在
        _pstack = nullptr; // 把这个指针变成空指针
    }

    // 压栈
    void push(int val)
    {
        if (full())
        {
            resize();
        }

        _top++;  
        _pstack[_top] = val; // 初始化: _pstack[0]放val
                               // 第二个入栈: _pstack[1]
        // _pstack[++_top];  
    }

    // 出栈
    void pop()
    {
        if (empty())
        {
            return;
        }
        --_top;           
    }

    // 获取栈顶元素
    int top()
    {
        return _pstack[_top];
    }

    // 判断是否为空
    bool empty() { return _top == -1; }
    // 判断是否满了
    bool full() { return _size - 1; } 

   

  
private:
    int *_pstack; // 动态开辟数组，存储顺序栈的元素
    int _top; // 指向栈顶元素的位置
    int _size; // 数组扩容的总大小

    void resize()
    {
        int *ptmp = new int[_size * 2];
        for (int i = 0; i < _size; i++)
        {
            ptmp[i] = _pstack[i];
        }
        delete []_pstack; // 释放内存
        _pstack = ptmp;  // 指向内存的指针指向新的地方
        _size *= 2; 
    }
};

int main()
{
    SeqStack s;  
    SeqStack s1(10);
    SeqStack s2(s1);
    s2 = s1;   // 赋值操作: 需要默认赋值构造函数
    return 0;
}
```
## 6. 指针指向问题: 
1. **拷贝构造函数指向不同，但是内存相同的值相同**
2. **赋值重载函数指针指向相同，内存的值也相同**

# 7. String对象练习拷贝构造函数和辅助重载函数
1. C语言字符串是以\0结束的，所以strcpy 要 + 1
2. 拷贝构造函数两步走: 1. 开辟新内存，2. 把内存的值拷贝过去
3. 赋值重载函数: 1. 防止自赋值 2. 释放当前内存， 拷贝过去
4. 赋值重载函数为什么不用void而是返回地址，因为可以str1 = str2 = str3;为了支持连续的赋值操作
```cpp
#include <iostream>
#include <cstring>
using namespace std;

class Strings
{
public:
    Strings(const char *str = nullptr) // 普通构造函数
    {
        if (str != nullptr)
        {
            m_data = new char[strlen(str) + 1]; // C语言字符串是以\0结束的
            strcpy(this->m_data, str);
        }
        else  // str = nullptr
        {
            m_data = new char[1];
            *m_data = '\0'; 
        }        
    }

     // 拷贝构造函数: 实例化的对象外的堆内存地址相同
     // 重新开一块内存，把other的值写进去
    Strings(const Strings &other)
    {
        m_data = new char[strlen(other.m_data) + 1];
        strcpy(m_data, other.m_data);
    }

    ~Strings()
    {
        delete []m_data;
        m_data = nullptr;
    }

    // 赋值重载函数
    Strings& operator=(const Strings &other) 
    {
        // 防止自我赋值
        if (this == &other)
        {
            return *this;
        }

        // 释放原先内存
        delete []m_data;
        m_data = new char[strlen(other.m_data) + 1];
        // 把右边的内存拷贝过来
        strcpy(m_data, other.m_data);
        return *this;
    }

private:
    char *m_data;
};

int main()
{
    // 默认构造函数
    Strings str1;  // 默认参数，空指针
    Strings str2("hello");
    Strings str3 = "hello";

    // 调用拷贝构造函数
    Strings str4 = str3;
    Strings str5(str3);

    // 调用赋值重载函数
    str1 = str2;
    return 0;
}
```

# 8. 构造函数的初始化列表
1. 自定义了构造函数后，编译器就不产生默认构造函数了
2. 先执行构造函数的初始化列表再执行当前类类型构造函数体
3. 在初始化列表写是int _amount = amount;
4. 在构造函数体写是 int _amount; _amount = amount; 当然两者还有时间差

5.  总结: 可以指定当前成员变量的初始化方法
```cpp
#include <iostream>
#include <cstring>
using namespace std;

#define NAME_LENGTH 20

class CDate
{
public:
    CDate(int year, int month, int day)
        
    {
        _year = year; 
        _month = month;
        _day = day;
    }

    void show()
    {
        cout << _year << "/" << _month << "/" << _day << endl;
    }

private:
    int _year;
    int _month;
    int _day;
};

class CGoods
{
public:
    CGoods(const char *name, double price, int amount, int year, int month, int day)
        : _date(year, month, day), // CDate _date;
          _amount(amount), _price(price) 
    {
        // strcpy函数的第二个参数需要传入一个字符数组的首地址
        // 所以这里不用写*name
        strcpy(_name, name); 
}

void show()
{
    cout << "name: " << _name << endl;
    cout << "price: " << _price << endl;
    cout << "amount: " << _amount << endl;
    _date.show();
}

private:
    char _name[NAME_LENGTH];
    double _price;
    int _amount;
    CDate _date; // 成员对象 1.分配内存 2.调用构造函数
};



int main()
{
    CGoods good1("ASD", 200, 100, 10, 10, 10);
    good1.show();
    return 0;
}
```

## 8.2 成员变量的初始化顺序跟定义的顺序有关，跟初始化列表无关
1. ma输出是无效值，因为ma先定义先初始化，而这个时候的mb是无效值，先定义mb, 那么ma, mb都是10
```cpp
#include <cstring>
using namespace std;

class Test
{
public:
    Test(int data = 10): mb(data), ma(mb){ }
    void show() { cout << "ma" << ma << " mb" << mb << endl; }

private:
    int ma;
    int mb;
};
int main()
{
    Test t;
    t.show();
    return 0;
}
```

# 9. 类的各种成员
## 9.1 普通的成员方法
1. 属于类的作用域
2. 调用该方法时，需要依赖一个对象
3. 可以任意访问对象的私有成员变量
4. 会自动生成一个this指针，可以用这个指针访问私有形参


## 9.2 静态变量/成员方法: 描述对象的共享信息
1. static变量一定要在类外进行定义并且初始化
2. 也是类的作用域
3. 静态成员变量没有依赖的对象
4. 每次产生新对象都会调用构造函数，所以静态变量的操作写在里面可以做记录
5. 静态成员方法可以用对象来调用，但是更好是拿类来调用
6. 静态方法不产生this指针
7. 在静态方法不能访问普通的成员变量因为没有对象this指针

## 9.3 常对象和常方法
1. 类的作用域
2. 调用依赖对象，普通对象常对象都可以
3. 常方法只能读不能写
4. 常对象生成的是const CGoods *this指针
5. 如果只读不写的函数尽量都写成常方法
```cpp
#include <iostream>
#include <cstring>
using namespace std;

#define NAME_LENGTH 20

class CDate
{
public:
    CDate(int year, int month, int day)
        
    {
        _year = year; 
        _month = month;
        _day = day;
    }

    void show()
    {
        cout << _year << "/" << _month << "/" << _day << endl;
    }

private:
    int _year;
    int _month;
    int _day;
};

class CGoods
{
public:
    CGoods(const char *name, double price, int amount, int year, int month, int day)
        : _date(year, month, day), // CDate _date;
          _amount(amount), _price(price) 
    {
        // strcpy函数的第二个参数需要传入一个字符数组的首地址
        // 所以这里不用写*name
        strcpy(_name, name);
        _count++;
    }

static void showcount() // 静态方法: 打印所有商品共享的信息
{
    cout << "we have: " << _count << " goods" << endl;
    // cout << _name;  会报错
}
void show()  // 生成CGoods *this
{
    cout << "name: " << _name << endl;
    cout << "price: " << _price << endl;
    cout << "amount: " << _amount << endl;
    _date.show();
}

void show1()const // 生成const CGoods *this
{
    cout << "name: " << _name << endl;
    cout << "price: " << _price << endl;
    cout << "amount: " << _amount << endl;
    // _name++; // 会报错，只读不写
}

private:
    char _name[NAME_LENGTH];
    double _price;
    int _amount;
    CDate _date; // 成员对象 1.分配内存 2.调用构造函数
    static int _count; // 静态成员变量
};

int CGoods::_count = 0;

int main()
{
    CGoods good1("ASD", 200, 100, 10, 10, 10);
    good1.show();
    good1.showcount();
    CGoods::showcount();
    CGoods good2("ASD", 200, 100, 10, 10, 10);
    CGoods::showcount(); 
    CGoods::showcount(); 

    // 常推对象
    const CGoods good3("ASDDDD", 200, 100, 10, 10, 10);
    // good3.show(); 常对象生成的是const CGoods *this
    good3.show1();
    return 0;
}
```

# 10. 指向类成员(成员变量和成员方法)的指针
1. 类的作用域指针，前面加类的作用域，调用的时候写依赖的对象
2. 访问在堆上的对象要删除在最后，访问用->
3. 静态变量不用写依赖的对象
4. 指向成员方法的指针
```cpp
#include <iostream>
using namespace std;

class Test
{
public:
    void func() { cout << "call Test::func" << endl; }
    static void static_func() { cout << "call static func" << endl; }
    int ma;
    static int mb; // 静态成员变量
};

int main()
{
    Test t1;
    Test *t2 = new Test(); // 在堆上的对象
    // 类的作用域指针
    // int *p = &Test::ma;
    int Test::*p = &Test::ma;
    t1.*p = 20; // 要把指针的作用域写上
    cout << t1.*p << endl;

    t2->*p = 30;
    cout << t2->*p << endl;

    // 定义指向成员方法的指针
    void (Test::*pfunc)() = &Test::func;
    (t1.*pfunc)();
    (t2->*pfunc)();

    delete t2;
    return 0;
}
```
