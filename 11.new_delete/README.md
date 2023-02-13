# new delete 基础
## 1. 基础问题
1. new和delete
2. new和malloc的区别是什么？
   - malloc和free, 称作C的库函数
   - new和delete是运算符
   - malloc开辟内存失败，通过返回值和nullptr来判断，而new开辟内存失败，是通过抛出bad_alloc类型的异常来判断的
   - malloc是按照字节开辟的，需要对返回值进行类型的转换
   - new是指定类型开辟内存的，不仅开辟内存还能给定初始值
3. **new 开辟的内存区域是一个连续的内存空间，用来存储指定数量的同类型数据。为了引用这个内存空间，需要使用一个指针变量来存储内存的首地址，从而访问这个内存空间中的元素。因此，把 new 开辟出来的内存赋给一个指针变量是一种常见的做法**
```cpp
int main()
{
    int *p = (int*)malloc(sizeof(int));
    if (p == nullptr)
    {
        return -1;
    }

    int *p1 = new int(20);

    try
    {
        int *p1 = new int(20);
    }
    catch (const bad_alloc &e)
    {
        throw "Fail";
    }
    return 0;
}
```
3. delete和free的区别是什么？
    - free就是给起始地址释放内存，就是一个标准的函数调用
    - delete释放单个元素内存和数组内存需要有一个[]的区别

## 2. 开辟数组内存
1. C开辟数组内存
```cpp
int main()
{
    // C中开辟数组内存
    int *q = (int*)malloc(sizeof(int) * 20);

    if (q == nullptr)
    {
        return -1;
    }

    free (q);
    return 0;
}
```
1. C++ 中开辟数组内存
```cpp
int main()
{
    // C++中开辟数组内存
    int *q = new int[20]; // 没有初始值数组内存
    int *q1 = new int[20](); // 全部初始化为0

    delete []q;
    delete []q1;
    return 0;
}
```
## 3. new的几种变种
```cpp
int main()
{
    // 都在堆上开辟内存
    int *p1 = new int(20);
    int *p2 = new (nothrow) int; // 跟malloc一样
    const int *p3 = new const int(40);
    const int *p4 = new int(40);
    
    // 定位new, 在定位好的内存上划分一块指定类型的空间
    int data = 0;
    int *p5 = new (&data) int(50); 
    cout << "data: " << data << endl;

    delete p1;
    delete p2;
    delete p3;
    delete p4;
    delete p5;
    return 0;
}
```