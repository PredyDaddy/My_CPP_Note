# 1. 多态引入
1. 多态是一种面向对象编程的一种概念，值得是同一种操作或者方法可以在不同对象上具有不同的行为或实现方式。换句话说，他允许不同对象对同一消息做出不同响应，多态性是面向对象编程中的重要特性之一，它提高了代码的可复用性和灵活性
2. 多态分为静态联编和动态联编
- 联编（Binding）是指将方法调用与方法实现关联起来的过程。在编程中，联编分为静态联编和动态联编。
- 动态联编（Dynamic Binding）也称为晚期绑定（Late Binding），它在运行时根据方法调用的实际对象类型来决定要调用的方法。动态联编通常用于虚函数，即通过基类指针或引用调用派生类重写的虚函数，实现多态性。动态联编可以提高代码的灵活性和可扩展性。

# 2. 怎么理解静态联编
1.  静态联编（Static Binding）也称为早期绑定（Early Binding），它在编译时就将方法调用与方法实现进行绑定，即在编译时就能确定要调用的具体方法。静态联编通常用于非虚函数，如全局函数、类的成员函数和静态成员函数等。优点是效率搞，但是灵活性很差
2. 静态联编的体现
- 隐藏（Hide）：当一个类定义了与基类同名的成员函数时，派生类的成员函数会隐藏基类的成员函数，即使它们的参数列表不同。这种隐藏也是静态联编的体现，因为编译器在编译时就能确定要调用哪个成员函数。

- 函数的重载（Function Overloading）：在一个类中定义多个同名函数，但是它们的参数列表不同，这就是函数的重载。编译器会根据函数调用时提供的参数类型和数量来确定要调用的具体函数，这也是静态联编的体现。

- 运算符重载（Operator Overloading）：在C++中，可以通过运算符重载来定义自定义的运算符，例如重载"+"运算符来实现两个对象的加法运算。运算符重载也是静态联编的体现，因为编译器会根据运算符及其参数的类型来确定要调用的具体函数。

- 泛型编程（Generic Programming）：C++中的模板是一种泛型编程的机制，它允许定义通用的类或函数，这些类或函数可以在不同的类型上进行操作。编译器会根据使用模板时提供的具体类型来实例化模板，并生成针对这些具体类型的代码，这也是静态联编的体现。


# 3. 运算符重载
1. C++ 运算符重载是一种特殊的语言特性，它允许程序员为自定义的数据类型定义与内置类型相似的运算符行为。通过运算符重载，我们可以使用与内置类型相似的语法对自定义类型进行操作，从而使代码更易读、更易理解。
2. 运算符重载通常是通过在类或结构体中定义特殊的成员函数来实现的，这些函数使用运算符的名称作为函数名，并定义运算符的操作行为。例如，如果要为一个名为 MyClass 的类定义加法运算符 +，可以在该类中定义一个名为 operator+ 的成员函数。
3. 改造前案例
```cpp
class Time
{
public:
    Time();                 // 默认构造函数
    Time(int h, int m = 0); // 带参数的构造函数
    void AddMin(int m);     // add minues
    void AddHr(int hr);     // add hours
    void Reset(int h = 0, int m = 0);

    // 返回的是一个Time类型的对象，传入的是一个Time类型的对象
    // Time& t 取地址保证了不是对这个对象进行拷贝，而是直接操作
    // Sum我们只是取里面的信息，为了保证对象不被修改，函数里面用const修饰t
    // 外面的const保证了返回的对象不能被修改，保证进来和出去都不能被修改
    Time Sum(const Time &t) const;
    void show() const;

private:
    int hours;
    int minutes;
};

// 外面实现构造函数
Time::Time()
{
    hours = minutes = 0;
}
Time::Time(int h, int m)
{
    hours = h;
    minutes = m;
}

void Time::AddMin(int m)
{
    minutes += m;
    hours += m / 60;
    minutes % 60;
}

void Time::AddHr(int h)
{
    hours += h;
}

void Time::Reset(int h, int m)
{
    hours = h;
    minutes = m;
}

Time Time::Sum(const Time &t) const
{
    Time sum;
    sum.minutes = t.minutes + minutes;
    sum.hours = t.hours + hours;
    sum.minutes % 60;
    return sum;
}

void Time::show() const
{
    cout << hours << " hours " << minutes << " minutes " << endl;
}

main()
{
    Time t1(45, 10);
    Time t2(12, 45);
    Time total;
    total = t1.Sum(t2);
    total.show();
    return 0;
}
```
4. 改造后案例
```cpp
class Time
{
public:
    Time();                 // 默认构造函数
    Time(int h, int m = 0); // 带参数的构造函数
    void AddMin(int m);     // add minues
    void AddHr(int hr);     // add hours
    void Reset(int h = 0, int m = 0);

    // 返回的是一个Time类型的对象，传入的是一个Time类型的对象
    // Time& t 取地址保证了不是对这个对象进行拷贝，而是直接操作
    // operator+/-我们只是取里面的信息，为了保证对象不被修改，函数里面用const修饰t
    // 外面的const保证了本来的对象(this指向的对象)不能被修改，保证进来和出去都不能被修改
    // 总之，两个const保证了this对象和传进来的参数对象不被修改
    Time operator+(const Time &t) const;
    Time operator-(const Time &t) const;
    void show() const;

private:
    int hours;
    int minutes;
};

// 外面实现构造函数
Time::Time()
{
    hours = minutes = 0;
}
Time::Time(int h, int m)
{
    hours = h;
    minutes = m;
}

void Time::AddMin(int m)
{
    minutes += m;
    hours += m / 60;
    minutes % 60;
}

void Time::AddHr(int h)
{
    hours += h;
}

void Time::Reset(int h, int m)
{
    hours = h;
    minutes = m;
}

Time Time::operator+(const Time &t) const
{
    Time sum;
    sum.minutes = t.minutes + minutes;
    sum.hours = t.hours + hours;
    sum.minutes % 60;
    return sum;
}

Time Time::operator-(const Time & t) const
{
    Time res;
    res.minutes = minutes - t.minutes;
    res.hours = hours - t.hours;
    res.minutes % 60;
    return res;
}
void Time::show() const
{
    cout << hours << " hours " << minutes << " minutes " << endl;
}

main()
{
    Time t1(45, 10);
    Time t2(12, 45);
    Time total;
    Time diff;
    total = t1 + t2;
    diff = t1 - t2;
    total.show();
    diff.show();
    return 0;
}
```
4. 前置++和后置++
1. 从代码来看，后置++在实现的时候需要构造一个临时对象，临时对象的构造和销毁都需要一定的系统资源，所以后置++的效率不如前置++
```cpp
class A
{
public:
    A& operator++() // 前置++ 
    {
        ++a;
        return *this;
    }

    A operator++(int) // 后置
    {
        A a = *this;
        ++*this;
        return a;
    } 
private:
    int a;
};
```
# 4. 友元函数
在上面的案例中，我们使用了友元函数，友元函数是一个非成员函数，但可以访问一个类的私有成员。在该案例中，我们定义了两个类 CCar 和 CDriver，其中 CDriver 是 CCar 的友元类，CCar 类中声明了两个友元函数 MostExpensiveCar 和 CDriver::ModifyCar，这两个函数都可以访问 CCar 类中的私有成员 price。

需要注意的是，使用友元函数可以使得一个函数访问另一个类中的私有成员，这在某些情况下非常有用，但也会破坏类的封装性。因此，需要谨慎使用友元函数，不要滥用。以下是一些需要注意的点：

1. 友元函数不是类的成员函数，它是一个全局函数或另一个类的成员函数。

2. 友元函数可以访问类的私有成员，这可能破坏类的封装性。

3. 友元函数的声明通常在类的定义中，但它的实现必须在类外。

4. 友元函数的实现中可以访问该类的所有成员，包括私有成员。

5. 友元函数通常不具有类成员函数的继承性，即如果一个类是另一个类的友元类，那么它的派生类不一定是另一个类的友元类。

6. 友元函数的声明可以放在类的私有部分，也可以放在公有部分，没区别的。

7. 友元函数是没有指针的。

总之，友元函数是一个强有力的工具，可以使得某些函数访问类的私有成员，但需要谨慎使用，以免破坏类的封装性和增加代码的复杂性。

```cpp
class CCar;
class CDriver
{
public:
    void ModifyCar(CCar *pCar);
};

class CCar
{
public:
    CCar(int p) : price(p) {}
    int getPrice() { return price; }

private:
    int price;
    friend int MostExpensiveCar(CCar cars[], int total); // 声明友元
    friend void CDriver::ModifyCar(CCar *pCar);          // 声明友元
};

void CDriver::ModifyCar(CCar *pCar) // 这里的pCar是一个指向CCar的指针
{
    pCar->price += 1000;
}

int MostExpensiveCar(CCar cars[], int total)
{
    int tmpMax = -1;
    for (int i = 0; i < total; ++i)
    {
        if (cars[i].price > tmpMax)
        {
            tmpMax = cars[i].price;
        }
    }
    return tmpMax;
}

int main()
{
    CCar cars[3] = {CCar(10000), CCar(15000), CCar(12000)};
    cout << "Most Expensive Car price: " << MostExpensiveCar(cars, 3) << endl;

    CDriver driver;
    driver.ModifyCar(&cars[1]);
    cout << "After Modification, Car price: " << cars[1].getPrice() << endl;
    return 0;
}

```
# 5. 友元类
1. 友元类可以访问另一个类的全部成员，包括私有。
2. 友元的关系不能被继承
3. 友元类的关系是单向的，不具备交换性，一定要看声明
```cpp
class Cars;
// class Driver;

class Driver
{
public:
    int PriceChange(Cars *ptr);
};

class Cars
{
private:
    int price = 0;
    friend Driver;
    friend int Driver::PriceChange(Cars *ptr);
};

int Driver::PriceChange(Cars *ptr)
{
    ptr->price += 1000;
    int temp = ptr->price;
    return temp;
}

int main()
{
    Cars car;
    Driver driver;
    cout << driver.PriceChange(&car) << endl;
    return 0;
}
```



# 6. 动态多态
1. 动态多态（Dynamic Polymorphism）是指在运行时（而不是编译时）确定对象的类型，从而实现基于对象类型的动态行为。在面向对象的程序设计中，动态多态是一个重要的概念，它允许不同的子类对象表现出不同的行为。

2. 动态多态满足的条件
- 有继承关系
- 基类中需要有虚函数。只有在基类中将成员函数声明为虚函数，才能在派生类中重写该函数并实现动态多态
- 使用指向基类对象的指针或引用来调用虚函数。只有通过指向基类对象的指针或引用来调用虚函数，才能在运行时确定对象的实际类型，并调用相应的函数
- 简单点说这个对象是一个父类的指针变量，然后通过new赋值为子类的对象(让指针指向子类)，然后才能在运行的时候调用定义好的虚函数

3. 下面这个案例，Shape是一个有虚函数的父类，Square Circle是继承Shape的子类，在main函数中Shape *并不是实例化对象，而是定义了父类的指针，然后通过new来给这个指针开辟内存，指向了一个Circle或者是Square的对象，然后再运行的时候才确定下来调用子类的draw()
```cpp
class Shape
{
public:
    virtual void draw()
    {
        cout << "draw shape" << endl;
    }
};

class Circle : public Shape
{
public:
    void draw()
    {
        cout << "draw Circle" << endl;
    }
};

class Square : public Shape
{
public:
    void draw()
    {
        cout << "draw Square" << endl;
    }
};

int main()
{
    Shape *shape1;       // 定义一个指向父类的指针
    shape1 = new Circle; // 指向一个Circle类型的对象
    shape1->draw();  
    delete shape1;  // 释放内存

    Shape *shapes[2]; // 指针数组实例化多个对象
    shapes[0] = new Circle;  // 指向一个Circle类型的对象
    shapes[1] = new Square;  // 指向一个Square类型的对象
    shapes[0]->draw();
    shapes[1]->draw();    

    // 释放内存，避免内存泄露的问题
    for (int i = 0; i < 2; i++)
    {
        delete shapes[i];
    }
    return 0;
}
```

# 7. 虚函数
1. 虚函数的基本使用
- C++中虚函数的主要作用是实现多态的机制。基类定义虚函数，自雷可以重写该函数
2. 不用指针看不出区别，用了指针才发现多态的牛逼之处，**根据实际对象类型而不是指针类型来调用函数**
3. 这个ptr是Base类型的ptr，可以调用Base的func() 和func2(), 被继承之后Derveried重写了func()这个虚函数，这里是一个动态联编，
4. 使用作用域限定符限制作用域并不会影响虚函数的动态绑定。当使用作用域限定符Base::明确指出要调用基类中的函数时，仍然会发生动态绑定
```cpp
class Base
{
public:
    virtual void func()
    {
        cout << "Base Function" << endl;
    }

    void func2()
    {
        cout << "Base func2" << endl;
    }
};

class Deveried : public Base
{
public:
    void func()
    {
        cout << "Derveried func" << endl;
    }
};

int main()
{
    // 不用指针看不出来，本来子类就会覆盖
    Deveried d;
    d.func();          // 静态联编

    // 用了指针，这里是定义父类类型的指针
    Base *ptr;
    ptr = new Deveried; // 开辟内存，使得父类类型的指针指向子类
    ptr->func();        // 动态联编 
    ptr->Base::func();  // 动态联编: 虽然用限定符作用域，依然是动态绑定
    ptr->func2();       // 静态联编: 这个指向父类的ptr本来就可以调用父类的func2()
    return 0;
}
```


# 8. 虚函数指针
1. 在上面两个案例中，当子类调用虚函数的时候，实际上是通过调用虚函数的指针从而找到接口。(调用虚函数就是指向父类的指针调用子类的函数)

# 9. 虚函数表
1. 当一个类有虚函数的情况下，他是拥有自己的虚函数表的，他的派生类也可以调用这些虚函数
2. 虚表是属于类的，不是属于某个对象的，一个类只需要一个虚表即可。同一个类的所有对象都使用同一个虚表

# 10. 虚函数的表指针
1. 虚表指针（Virtual Table Pointer，简称 VTable 指针）是实现 C++ 多态机制的一种技术。在使用虚函数时，每个类都会生成一个虚表（Virtual Table），虚表中保存了该类的所有虚函数的地址。当我们通过一个指向基类的指针或引用调用虚函数时，程序会根据指针或引用的实际类型来查找相应的虚表，并从虚表中获取相应的函数地址，然后调用该函数。
2. 虚函数表指针_vfptr是对象中的第一个元素，虚函数表指针的地址就是对象的首地址

# 11. 动态绑定
```cpp
class A {
public:
    virtual void vfunc1();
    virtual void vfunc2();
    void func1();
    void func2();
private:
    int m_data1, m_data2;
};

class B : public A {
public:
     void vfunc1(); //重写了vfunc1
    void func1();
private:
    int m_data3;
};

class C: public B {
public:
    virtual void vfunc2(); //重写了vfunc2
    void func2();
private:
    int m_data1, m_data4;
};
```
1. A的虚表中有vfunc1 vfunc2 
2. B的虚表中有自己重写的vfunc1, 和从A中集成的vfunc2
3. C中有自己的重写的vfunc2, 从B中继承来的vfunc1
4. 三个类都有自己的两个*vfptr指针，指向自己的虚表
5. B想调用A的虚函数，需要用作用域调用，下面是调用案例
```cpp
class A {
public:
    virtual void vfunc1();
    void func1();
};

class B : public A {
public:
    void vfunc1() override; // 重写 A::vfunc1()
    void func1();
    using A::func1; // 指定 A::func1() 的作用域
    void func2();
};

void B::vfunc1() {
    std::cout << "This is B::vfunc1()." << std::endl;
}

void B::func1() {
    std::cout << "This is B::func1()." << std::endl;
}

void B::func2() {
    std::cout << "This is B::func2()." << std::endl;
}

int main() {
    B b;
    b.vfunc1(); // 调用 B::vfunc1()
    b.func1(); // 调用 B::func1()
    b.A::func1(); // 调用 A::func1()
    b.func2(); // 调用 B::func2()
    return 0;
}
```
# 7. 从编译器的角度看动态绑定
1. 之前的案例，指针定义是基类的指针，指向派生类，然后我们通过基类指针调用派生类函数，编译器是如何处理的？
- 编译器先确定是否为虚函数，如果不是虚函数，采用静态变异，直接调用基类的函数，不管派生类是否隐藏了函数。
- 当指针的类型是基类的时候，就算指向派生类中有同名的函数，不是虚函数不会调用。
2. 如果是虚函数，在程序运行的时候，指针指向了派生类对象，通过该指针就能够访问到派生类对象中的虚函数表指针。如果派生类没有重写，这个虚函数表指针指向基类的虚函数。如果重写了，指针指向的是派生类的函数
3. **总结：多态就是父类类型的指针，可以调用自己全部的函数，但是如果有虚函数，且被继承的子类中有覆盖的函数(不用写virtual)，虚函数表的指针指向子类的函数。**
# 8. 设计思考: 什么时候将函数设计成虚函数
1. 如果基类的某个行为，在所有派生类都是一样的，意思是不用背重写，设计成普通函数就好
2. 如果设计成虚函数，在子类中不重写，那都是一样的，静态联编还有更高的效率。
3. 图方便的话全部写成虚函数会导致效率很低。

# 9. 纯虚函数
1. 在项目开发的时候，只确定了基类中函数的功能但是没有确定他们的实现方法，这个时候就要用到纯虚函数 virtual type func() = 0;
2. 派生类必须实现在基类中定义的纯虚函数，纯虚函数体现了一个规范的作用。
3. 纯虚函数没有函数体，只是一个声明，在函数声明结尾加上=0也只是为了告诉编译器此函数为纯虚函数
4. =0 也只是在虚函数表中保留一个位置，但是这个特定的位置不放地址
5. 之前说到每个虚函数都有自己的虚函数指针，这里就用到了。子类实现了基类的纯虚函数之后对应的指针指向实现的地方。

