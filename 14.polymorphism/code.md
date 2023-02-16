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