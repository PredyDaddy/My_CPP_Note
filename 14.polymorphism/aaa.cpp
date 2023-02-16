#include <iostream>
using namespace std;

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