#include <iostream>

using namespace std;


// 父类子类的构造函数，析构函数调用顺序，
// 当父类有多个构造函数的时候，在子类显示调用指定的构造函数
#if 0
// 基类/父类
class A
{
protected:
    int z;
private:
    int x;

public:
    A() // 默认构造函数
    {
        cout << "A()" << endl;
    }
    ~A()
    {
        cout << "~A()" << endl; 
    }

    // 自定义构造函数
    A(int a, int b) : z(a), x(b)
    {
        cout << "A(int a, int b)" << endl;
    }

    int get_z() { return z; }
    int get_x() { return x; }
    void set_x(int x) { this->x = x; }
};

// 派生类/子类
class B : public A
{
public:
    B()
    {
        cout << "B()" << endl;
    }
    ~B()
    {
        cout << "~B()" << endl;
    }

    // 指定使用父类的构造函数
    // A中有默认构造函数和带参数的构造函数
    B(int a, int b) : A(a, b)
    {
        cout << "B(int a, int b)" << endl;
    }
};
int main()
{
    // B b; // 先调用基类的构造函数再调用自己的构造函数

    cout << "------------------------" << endl;
    B b1(10, 20); // 这里的参数是显示调用A类的自定义构造函数
    return 0; // 这里调用析构函数，先调用派生类的析构函数再调用基类的构造函数
}
#endif

// 基类的成员变量，都在子类中共存，就算成员变量名称相同
#if 0
class A
{
	public:
		int x;
	protected:
		int y;
	private:
		int z;
	public:
		A(){cout << "基类的构造函数" << endl;}
		~A(){cout << "基类的析构函数" << endl;}
};
class E:public A
{
	public:
            int x;
		E(){cout << "派生类的构造函数" << endl;};
		~E(){cout << "派生类的析构函数" << endl;};
};
int main()
{
	E e;
       cout << "sizeof(E): " << sizeof(E) << endl; //16
       return 0;
 }
#endif

// 子类父类的成员变量名称冲突
#if 0
class A
{
public:
    int x;

public:
    A()
    {
        this->x = 1;
        cout << "基类的构造函数" << endl;
    }
    A(int x) 
    {
        this->x = x;
        cout << "基类中的A(int x)构造函数" << endl;
    }

    void func_a()
    {
        cout << "func_a" << endl;
    }
};

class E : public A
{
public:
    int x;
    E() { cout << "派生类的默认构造函数" << endl; }
    E(int a) : x(a) { cout << "派生类中的构造函数E(int a)" << endl; }
    ~E() { cout << "派生类中的析构函数" << endl; }
};

int main() 
{
    E e(10);
    // 如果子类有成员和父类同名，子类访问其成员默认访问子类的成员(本作用域，就近原则)
    cout << e.x << endl;

    // 当子类成员和父类成员同名时，子类依然从父类继承同名成员
    // 在子类通过作用域::进行同名成员区分(在派生类中使用基类的同名成员，显示使用类名限定符)
    cout << e.A::x << endl;
    cout << sizeof(E) << endl; // 两个int，所以是8
}
#endif

// 隐藏问题
#if 0
// 1. func2() 父类子类名称相同，参数不相同，父类的方法被隐藏
// 2. func1() 父类子类名称相同，参数也相同，但是没有virtual，父类的方法被隐藏
class Father
{
public:
    void func1()
    {cout << "father func1" << endl;}

    void func2(int x)
    {cout << "father func2" << endl;}
};

class Son : public Father
{
public:
    void func1()
    {cout << "son func1" << endl;}

    void func2(char x)
    {cout << "son func2" << endl;}
};

int main()
{
    Father father;
    Son son;
    son.func1();
    son.func2('s');
    return 0;
}
#endif

// 访问公开的普通成员变量和静态成员变量，静态成员变量的初始化
#if 0
class Base
{
public:

public:
     int sNum = 10;
     static int sNum1;
};

int Base::sNum1 = 10;

int main()
{
     Base obj;
     cout << obj.sNum << endl;
     cout << Base ::sNum1 << endl; 
     return 0;
}
#endif

// 继承中的静态成员特性
#if 1
class Base
{
public:
    static int getNum() { return sNum; }
    static int getNum(int param){
        return sNum + param; }

    public:
        static int sNum;
};
int Base ::sNum = 10;

class Derived : public Base
{
public:
    static int sNum; // 这里的话父类同名的成员属性被隐藏

    // 父类的方法同样被隐藏了
    // 改变基类中一个函数的特征，所有使用该函数名的基类版本都会被隐藏
    static int getNum(int param1, int param2)
    {
        return sNum + param1 + param2;
    }
};
int Derived :: sNum = 100;

int main()
{
        Base obj;
        cout << obj.getNum() << endl;
        cout << obj.getNum(1) << endl;
        Derived obj2;

        // 编译器报错，这里不会去父类找可以匹配到的，因为被隐藏了
        // obj2.getNum();

        cout << obj2.getNum(1, 2) << endl;
        
        return 0;
}
#endif