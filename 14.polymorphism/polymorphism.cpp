#include <iostream>
using std::cout, std::endl;

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