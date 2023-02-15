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
# 5. 友元函数
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
6. 友元类
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