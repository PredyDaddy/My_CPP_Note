#include <iostream>
using namespace std;

template<typename T>
class Operator
{
public:
    T add(T a, T b);

    T minus(T a, T b);
};

// 在类模版外定义成员函数，也要加上template 
template<typename T>
T Operator<T>::add(T a, T b)
{
    return a + b;
}

template<typename T>
T Operator<T>::minus(T a, T b)
{
    return a - b;
}

int main()
{
    Operator<int> op1;
    Operator<float> op2;
    cout << op1.add(3, 5) << endl;
    cout << op1.minus(3, 1.5) << endl; // op1.minus(3, 1)

    cout << op2.add(0.5, 0.2) << endl; 
    cout << op2.minus(3, 2) << endl; 

    return 0;
}