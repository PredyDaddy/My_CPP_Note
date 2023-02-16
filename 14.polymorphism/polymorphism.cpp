#include <iostream>
using namespace std;

// 原版，后面用于运算符重载改造
#if 0
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
#endif

// 使用运算符重载去改造
#if 0
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
#endif

// 前置++和后置++
#if 0
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
#endif
// 友元函数案例
#if 0
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
#endif

#if 0
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
#endif

// 动态多态的案例
#if 0
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
#endif

// 虚函数的基本使用
#if 0
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
    d.func();

    // 用了指针，这里是指向父类的指针
    Base *ptr;
    ptr = new Deveried; // 开辟内存
    ptr->func();
    ptr->Base::func();  // 这样才能调用父类的func()
    ptr->func2(); // 这个指向父类的ptr就可以调用子类的func了
    return 0;
}
#endif

#if 0
// 动态绑定调用案例
class A
{
public:
    virtual void vfunc1()
    {
        cout << "A::vfunc1" << endl;
    }
};

class B : public A
{
public:
    virtual void vfunc1() override
    {
        cout << "B::vfunc1" << endl;
    }

    void func1()
    {
        cout << "B::func1" << endl;
    }

    virtual void vfunc2()
    {
        cout << "B::vfunc2" << endl;
    }

    void func2()
    {
        cout << "B::func2" << endl;
    }
};

int main()
{
    B b;
    b.func1();
    b.func2();
    b.vfunc1();
    b.vfunc2();

    b.A::vfunc1();
    return 0;
}
#endif

// A, B, C, 哪里写Virtual
#if 0
class A {
public:
    virtual void fun() {
        cout << "A::func" << endl;
    }
};

class B : public A {
public:
    void fun() {
        cout << "B::func" << endl;
    }
};

class C : public B {
public:
    void fun() {
        cout << "C::func" << endl;
    }
};

int main() {
    A *ptr;
    ptr = new C;
    ptr->fun();

    B *ptr1;
    ptr1 = new C;
    ptr1->fun();

    return 0;
}
#endif

// 纯虚函数案例
#if 0
class Hero
{
public:
    virtual void Back() = 0;
};

class Hero1 : public Hero
{
public:
    void Back()
    {
        cout << "hero1 back" << endl;
    }
};

class Hero2 : public Hero
{
public:
    void Back()
    {
        cout << "hero2 back" << endl;
    }
};

int main()
{
    // Hero h; 会报错，无法被实例化创建对象所以被叫作抽象基类，自然也无法为分配内存空间
    Hero1 h1;
    return 0;
}
#endif

// 抽象基类
#if 0
class Hero
{
public:
    virtual void Back() = 0;
};

class Hero1 : public Hero
{
public:
    void Back()
    {
        cout << "hero1 back" << endl;
    }
};

class Hero2 : public Hero
{
public:
    void Back()
    {
        cout << "hero2 back" << endl;
    }
};

int main()
{
    // 两种调用方法
    Hero *hptr;
    hptr = new Hero1;
    hptr->Back();

    
    Hero2 h2;
    hptr = &h2;
    hptr->Back();
    return 0;
}
#endif

// 抽象基类的设计问题
#if 0
class Shape
{
public:
    // 需要子类完成的功能, 不同形状的东西面积周长的公式都不一样
    // 无法在基类中实现
    virtual void getArea() = 0;
    virtual void getPermiter() = 0;
};

class Circle : public Shape
{
public:
    // 不带参数的构造函数
    Circle()
    {
        this->_radius = 10;
    }
    Circle(int radius) : _radius(radius) {}

public:
    void getArea()
    {
        int res = 3.14 * _radius * _radius;
        cout << "Circle Area: " << res << endl;
    }

    void getPermiter()
    {
        int res = 2 * 3.14 * _radius;
        cout << "Circle Permiter: " << res << endl;
    }

private:
    int _radius;
};

class Square : public Shape
{
public:
    Square()
    {
        this->_size = 10;
    }

    Square(int size) : _size(size) {}

public:
    void getArea()
    {
        int res = _size * _size;
        cout << "Square Area: " << res << endl;
    }
    void getPermiter()
    {
        int res = _size * 4;
        cout << "Square Permite: " << res << endl;
    }

private:
    int _size;
};
int main()
{
    // 经过测试，可以实例化，抽象基类的需求完成了
    Circle c1;
    Circle c2(5);

    Square s1;
    Square s2(5);

    // 用一个数组保存这两个圆
    Shape *shape[4];
    shape[0] = &c1;
    shape[1] = &c2;
    shape[2] = &s1;
    shape[3] = &s2;

    for (int i = 0; i < 4; i++)
    {
        shape[i]->getArea();
        shape[i]->getPermiter();
    }
    return 0;
}
#endif

// 虚析构函数
class Base
{
public:
    Base()
    {
        cout << "Base构造函数" << endl;
    }
    virtual ~Base()
    {
        cout << "Base析构函数" << endl;
    }
};

class Derived : public Base
{
public:
    Derived()
    {
        cout << "Derived构造函数" << endl;
    }
    ~Derived()
    {
        cout << "Derived的析构函数" << endl;
    }
};

int main()
{
    Base *ptr;
    ptr = new Derived;
    delete ptr;
    return 0;
}