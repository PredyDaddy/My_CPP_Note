# 1. 引用
## 1.1 什么是引用？引用和指针有什么区别
1. 引用是一个更安全的指针
2. 引用是必须初始化且被赋的必须是一个左值，指针可以不初始化
3. 从下面的案例看出来，定义指针变量和引用变量一样的，先存地址再赋给左值
4. 在汇编上也是一样的，先把变量存入寄存器，再赋值给指针变量和引用变量
5. int &c = 20; 会报错， c不是左值《 20是一个右值
6. 更改也是通过地址截引用赋值
7. 引用只有一级引用，不像指针有多级指针
```cpp
int main()
{
    int a = 10;
    int *p = &a; // eax [a].  dword ptr [p] 
    int &b = a;  // eax [a].  dword ptr [b] 

    *p = 20;  // 更改地址内存上的变量
    cout << "a: " << a << " *p: " << *p << " b: " << b << endl;

    b = 30;   // 更改地址内存上的变量
    cout << "a: " << a << " *p: " << *p << " b: " << b << endl;

    // int &c = 20; 这个表达式错误的，因为20是无法确认地址的
    return 0;
}
```
## 1.2引用的好处
1. 下面这个案例没有办法交换, 因为形参和实参是值传递，形参交换了，但是实参没有交换
```cpp
void swap(int a, int b)
{
    int temp = a;
    a = b;
    b = temp;
}

int main()
{
    int a = 10;
    int b = 20;
    swap(a, b);
    cout << "a " << a << " b " << b << endl;  // 
    return 0;
}
```
1. 正确的写法: 通过引用或者指针直接取地址操作实参
2. 在案例中swap函数直接读的就是地址
```cpp
// void swap(int *x, int *y)
// {
//     int temp = *x;
//     *x = *y;
//     *y = temp;
// }

void swap(int &x, int &y)
{
    int temp = x;
    x = y;
    y = temp;
}


int main()
{
    int a = 10;
    int b = 20;
    swap(a, b);  
    // swap(&a, &b); 
    cout << "a " << a << " b " << b << endl;  // 
    return 0;
}
```
## 1 .3 引用是引用对象的联名
**相当于给数组array起了一个别名q, 这个跟指针还是不同的，指针变量的size还是比较小的**
```cpp
int main()
{
    int array[5] = {};
    int *p = array;
    int (&q)[5] = array;


    cout << sizeof(array) << endl;  // 20  5个int 5x4bits = 20 bits
    cout << sizeof(p) << endl;      // 一个 int 4bits
    cout << sizeof(q) << endl;      // 20 bits
    return 0;
}
```
# 2. 左值引用和右值引用
1. 左值: 有内存，有名字，值可以被修改
2. 右值: 没内存没名字
3. C++ 11 提出了右值引用 
```cpp
int &&c = 20;
```
   - dword ptr [ebp - 30h], 14h   产生一个临时量，存入20   14H
   - eax, [ebp - 30h]             把这个临时量存入寄存器
   - dword ptr [c], eax           把寄存器的值赋给指针/引用变量c
4. const int &d = 20;     汇编指令跟上面是一样的，但是不能更改，因为被const修饰
5. 理解: 一个右值引用变量，本身是一个左值
6. 右值专门用来引用右值对象，自动产生临时量然后直接引用临时量，还可以修改
7. 不能用右值引用对象引用一个左值

# 3. const 结合一级指针
## 3.1 写一句代码，在内存的0x0018ff44处写一个4字节的10
int *p = (int*)0x0018ff44;
## 3.2 指针覆盖引用的案例，学会还原指针/引用
```cpp
int main()
{
    int a = 10;
    int *p = &a;
    int **q = &p;
    return 0;
}
```
把引用放过去覆盖指针
```cpp
int main()
{
    int a = 10;
    int *p = &a;
    int *&q = p;
    return 0;
}
```