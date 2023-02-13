
# 函数的堆栈详细调用过程

### 案例
```cpp
# include <iostream>
using namespace std;

int sum(int a, int b) {
    int temp = 0;
    temp = a + b;
    return temp;
}

int main() {
    int a = 10;
    int b = 20;

    int ret = sum(a, b);
    cout << "ret is: " << ret << endl; 
    return 0;
}
```
### 问题
- 问题1： main函数调用sum, sum执行完了之后，怎么知道回到哪个函数去？
    - 
- 问题2：sum函数执行完了，回到main以后，怎么知道从哪一行指令继续往下执行?



# 基础知识
![在这里插入图片描述](https://img-blog.csdnimg.cn/0b529222910949a7a867b0769e9b56ae.png)

- ebp 栈底的地址   esp: 栈顶的地址 
- 压栈:把数据往栈顶压  
- 栈底是高地址，栈顶是低地址
- 局部变量都是通过访问栈底指针的偏移来访问的: a先进入栈，压栈 
- mov dword ptr[ebp - 4]  
- int: 4个字节
- 这里不是压栈，这里是位置的解释
-  ret的初始值不知道，sum返回才知道

# 寄存器
<=4字节 eax通过寄存器带出来
4字节 < < 8字节  eax edx 两个寄存器带出来
大于8字节, 产生临时量带出返回值了

# 函数的调用1: 压栈
![在这里插入图片描述](https://img-blog.csdnimg.cn/de9940a2a34c4844ab8cd7db26ef3f22.png)

- 压栈: 从右往左压，所以sum(a, b) 这里先压b
-  把b压倒栈顶  20 -> int b, 这里开辟形参变量内存，同样  esp栈顶也高了
- 先把b放到寄存器然后压到栈顶
- 然后同样压a的内存  
# 函数的调用2: call指令
- call的功能就是把下一行指令的地址入栈(压栈)  上面的24458，他就是执行下面的函数，出栈的时候定位用的

# 函数的调用2: call指令  call sum的过程
- 先call指令的功能就是把下一行指令的地址入栈(压栈)
- 进入sum()
  - 函数一进来，并不是直接去第一句话，大括号跟第一行是有指令生成的
  - 进入sum() 先把main()函数的栈帧，先入栈，然后正式进入sum()
# 函数的调用3: 进入sum函数的第一件事情，左括号跟第一句之间干的事情
![插入图片描述\](https://img-blog.csdnimg.cn/d87bba0017bc4a8d83b3a8798903e40a.png)](https://img-blog.csdnimg.cn/aa0873bac9124809a054557f487fd0f6.png)

- 绿色区是新开辟的栈帧空间
- 很重要，不然不开辟空间做不了任何事情
- push ebp: 入栈   : 使ebp指向esp
- mov ebp, esp     : ebp指向sum()的栈底
- sub esp, 4CH: 给sum()函数开辟栈帧空间
![在这里插入图片描述](https://img-blog.csdnimg.cn/c76519c76227432185d538c490a331a3.png)

# 函数的调用4: 在新开辟的空间里面
- int temp = 0; 在新的空间压栈，
- temp = a + b; 
- 这两行的通过mov指针偏移到下面a, b的地方，取到实参的数据
- 访问完数据之后算出 a + b 然后mov把新的temp数据放在之前的位置
- return temp; temp出不去的，mov 把数据放寄存器eax上面然后带出去 
  ![在这里插入图片描述](https://img-blog.csdnimg.cn/8e7a04c4c7b74b749ce4569b37fe293a.png)
# 函数的右括号: 归还栈空间并且回到原来的地方
- mov esp ebp 把栈空间交还给系统
- pop ebp 出栈并把出栈元素的值给ebp,这个值就是之前入栈的时候把ebp压上来的地址，这样又回去了，这样就标准的回到了main函数了
- 把出栈的内容，放入CPU的PC寄存器(下一行要执行的地址)
- 他的下一行就是call指令压栈的下一行，这也是回到main函数的时候为什么不会从main()函数第一行开始执行
- 把寄存器的给temp;