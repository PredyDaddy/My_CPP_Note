# 1. 链表的基本概念
链表（Linked List）是一种常见的数据结构，用于存储一系列元素，这些元素可以是任意类型的数据。链表中的每个元素被称为节点（Node），每个节点包含两部分：一个存储数据的值（或称为数据域），以及一个指向下一个节点的引用（或称为指针或链接）。

链表与数组相比，具有一些优势和不同之处：

1. **动态性：** 链表的大小可以在运行时动态地改变，而数组的大小通常是静态的。
   
2. **插入和删除：** 在链表中插入或删除元素相对容易，只需修改节点的引用，不需要像数组一样移动大量元素。

3. **空间利用：** 链表可以有效地利用内存，因为每个节点只需存储自身的值和下一个节点的引用，而数组可能需要一块连续的内存空间。

链表有几种常见的类型，其中最常见的是单向链表和双向链表：

1. **单向链表（Singly Linked List）：** 每个节点包含一个数据域和一个指向下一个节点的引用。链表的首节点称为头节点，链表的尾节点的下一个节点引用为空。

2. **双向链表（Doubly Linked List）：** 每个节点包含一个数据域和两个引用，分别指向前一个节点和后一个节点。这使得在链表中可以双向遍历。

基本操作：

1. **插入操作：** 插入节点涉及创建一个新的节点，并将其插入到合适的位置。对于单向链表，需要修改前一个节点的引用，对于双向链表，还需要修改后一个节点的前向引用。

2. **删除操作：** 删除节点涉及将待删除节点的前一个节点的引用指向待删除节点的下一个节点。同样，对于双向链表，还需要修改后一个节点的前向引用。

3. **搜索操作：** 从头节点开始，按顺序遍历链表，查找特定值的节点。

4. **遍历操作：** 从头节点开始，按顺序访问链表的每个节点，执行所需的操作。

链表在许多编程场景中都有用途，例如实现栈、队列、缓存等数据结构，也常用于解决某些特定的问题，如链表反转、寻找中间节点等。然而，需要注意链表的操作可能比数组稍微复杂，因为需要更多的指针操作。



# 2. 题目中的结构体
```cpp
struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};
```
ListNode* next;是单链表特性，除了储存value以外还都储存了next，指向下一个节点的指针。

这段代码定义了一个名为 `ListNode` 的结构体，用于表示链表中的节点。这个结构体有三个不同的构造函数，以便于创建节点对象：

1. **默认构造函数：**
```cpp
ListNode() : val(0), next(nullptr) {}
```
这个构造函数会创建一个值为0、下一个节点为空的链表节点。

2. **带有一个整数参数的构造函数：**
```cpp
ListNode(int x) : val(x), next(nullptr) {}
```
这个构造函数会创建一个具有给定整数值 `x`、下一个节点为空的链表节点。

3. **带有两个参数的构造函数：**
```cpp
ListNode(int x, ListNode* next) : val(x), next(next) {}
```
这个构造函数会创建一个具有给定整数值 `x` 和指向下一个节点的指针 `next` 的链表节点。

在这个结构体中，`val` 成员变量用于存储节点的值，而 `next` 成员变量是一个指向下一个节点的指针。这样，我们就可以通过创建多个 `ListNode` 对象，并使用 `next` 指针将它们链接在一起，从而形成一个链表。

这个结构体的定义允许我们在链表操作中方便地创建和操作节点，以实现链表的常见操作，如插入、删除和遍历。

# 2. 移除链表元素

## 2.1 以案例来学习链表，普通的删除方法

**复习指针**
### 1. delete ptr不是删除指针, 而是释放指针指向的内存
这里因为tmp和head都指向了同一内存空间，所以delete tmp就是释放之前的head, 因为我们要对head进行一个变动
```cpp
        while (head != NULL && head->val == val) { // 注意这里不是if
            ListNode* tmp = head;
            head = head->next;
            delete tmp;
        }
```

### 2. 比较容易的错误写法

在删除非头结点的时候容易犯这个错误, 因为是链表，写的时候就很容易参照链表的delete函数的写法，就是直接给一个tmp, 然后cur->next, 然后就直接删除，其实这样是不对的，因为链表删掉了中间节点还要考虑前后的加在一起

```cpp
        // 删除非头结点的节点
        ListNode *cur = head; // 当前指针是head
        while (cur != NULL){
            if (cur->val == val){
                ListNode* tmp = cur; // tmp, head指向同一内存空间
                cur = cur->next; // 头结点指针指向原来链表的第二个节点
                delete tmp;
            }
```


```cpp
#include <iostream>

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        // 删除头节点，同时也判断新的头结点是否需要删除
        while (head != NULL && head->val == val){
            ListNode *tmp = head;   // 这里让tmp指向需要被移除头结点同一地址
            head = head->next;      // 这里头结点的指针指向下一个节点
            delete tmp;             // 移除tmp, 同样也释放掉需要操作头结点的指针
        }

        // 删除非头结点的节点，这里不只是简单的删除，还要考虑把前一个后一个链接起来
        /*
        ex: 1->2->3->2->5, 处理2, 因为这里处理的是非头节点，在1位置链接3处理2，在3链接5处理2
                                  如果遍历的时候在2处理2，还要写一个prev指针

                                  如果5要处理，就在前一个地方(2)处理，5的next是nullptr, (2)链接5就行了
        */
        ListNode *cur = head; // 这里已经考虑完了头结点, 所以这个头结点不用操作
        while (cur != NULL && cur->next != NULL){ // 遍历链表的基本手法
            if (cur->next->val == val){    
                ListNode *tmp = cur->next;
                cur->next = cur->next->next;
                delete tmp;
            }
            else {
                cur = cur->next;
            }
        }
        return head;
    }
};

// 辅助函数：打印链表
void printList(ListNode* head) {
    ListNode* current = head;
    while (current != nullptr) {
        std::cout << current->val << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

// 这个地方跟上面删除非头结点最大的区别就是不用维护这个代码
void deleteList(ListNode* head) {
    ListNode* current = head;
    while (current != nullptr) {
        ListNode* tmp = current;
        current = current->next;
        delete tmp;
    }
}

int main() {
    Solution solution;

    // 示例 1
    ListNode* head1 = new ListNode(1);
    head1->next = new ListNode(2);
    head1->next->next = new ListNode(6);
    head1->next->next->next = new ListNode(3);
    head1->next->next->next->next = new ListNode(4);
    head1->next->next->next->next->next = new ListNode(5);
    head1->next->next->next->next->next->next = new ListNode(6);
    int val1 = 6;
    ListNode* newHead1 = solution.removeElements(head1, val1);
    std::cout << "Case 1: ";
    printList(newHead1);

    // 示例 2
    ListNode* head2 = nullptr;
    int val2 = 1;
    ListNode* newHead2 = solution.removeElements(head2, val2);
    std::cout << "Case 2: ";
    printList(newHead2);

    // 示例 3
    ListNode* head3 = new ListNode(7);
    ListNode* current3 = head3;
    for (int val : {7, 7, 7}){
        current3->next = new ListNode(val);
        current3 = current3->next;
    }
    std::cout << "Oringin case 3: ";
    printList(head3);
    int val3 = 7;
    ListNode* newHead3 = solution.removeElements(head3, val3);
    std::cout << "Case 3: ";
    printList(newHead3);

    
    // 释放节点内存
    deleteList(newHead1);
    deleteList(newHead2);
    deleteList(newHead3);

    return 0;
}

```

## 2.2 虚拟头结点写法

这样就只用考虑处理非头结点的情况就好了, 注意这里实例化了之后要用引用，这里也是复习一下实例化和在堆上生成内存返回指针，下面有两种写法

栈上的内存（Stack）：当你创建一个局部变量或对象（例如ListNode dummy(0);）时，这个对象是在栈上分配内存的。这些对象的生命周期是确定的，当它们所在的作用域结束时，它们会自动被销毁，内存会被释放。

堆上的内存（Heap）：当你使用new关键字（例如ListNode* dummy = new ListNode(0);）时，对象是在堆上分配内存的。这些对象的生命周期是不确定的，你需要显式地使用delete来释放内存。

使用指针的一个主要优点是，它允许你在运行时动态地创建和销毁对象。这给了你更大的灵活性，但代价是你需要更仔细地管理内存。

实例化虚拟头节点
```cpp
class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        ListNode dummy(0);
        dummy.next = head;

        // 处理非头节点
        ListNode *cur = &dummy; // 这里已经考虑完了头结点, 所以这个头结点不用操作
        while (cur != NULL && cur->next != NULL){ // 遍历链表的基本手法
            if (cur->next->val == val){    
                ListNode *tmp = cur->next;
                cur->next = cur->next->next;
                delete tmp;
            }
            else {
                cur = cur->next;
            }
        }
        return dummy.next;
    }
};
```

指针虚拟头结点
```cpp
class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        ListNode *dummy = new ListNode(999);

        // 处理非头节点
        ListNode *cur = dummy; // 这里已经考虑完了头结点, 所以这个头结点不用操作
        while (cur != NULL && cur->next != NULL){ // 遍历链表的基本手法
            if (cur->next->val == val){    
                ListNode *tmp = cur->next;
                cur->next = cur->next->next;
                delete tmp;
            }
            else {
                cur = cur->next;
            }
        }
        return dummy->next;
    }
};
```

# 3. 设计一个链表

通过完整的设计一个链表理解链表是怎么遍历的，新的节点怎么在各个地方链接起来

```cpp
#include <iostream>

class MyLinkedList {
public:
    struct ListNode   // 先创建节点的结构体, val, next, 以及ListNode的构造函数
    {
        int val;
        ListNode *next;
        ListNode(int x) : val(x), next(nullptr) {}
    };

private:
    ListNode *head;    // 指向头结点的指针
    int size;          // 链表的尺寸

public:
    MyLinkedList() {
        head = NULL;
        size = 0;
    }

    int get(int index) {
        // 这个就是取出索引的值
        if (index < 0 || index >= size)
            return -1;

        ListNode *cur = head;
        for (int i = 0; i < index; i++)
        {
            cur = cur->next;
        }
        return cur->val;
    }

    void addAtHead(int val) {
        /*
        1 -> 2 -> 3 -> 4   
        添加val
        val -> 1 -> 2 -> 3 -> 4  
        */
        ListNode *new_node = new ListNode(val); // 定义一个新的节点
        new_node->next = head;  // val链接头结点
        head = new_node;        // 更新头结点
        size++;                 
    }

    void addAtTail(int val) {
        /*
        1 -> 2 -> 3 -> 4   
        添加val
        1 -> 2 -> 3 -> 4 -> val
        */
        // 如果刚初始化也可以使用这个接口
        if (size == 0){
            addAtHead(val);
            return;
        }

        ListNode *cur = head; // 当前指针位置，从head开始
        while (cur->next != NULL){ // 这里遍历到最后一个节点
                cur = cur->next;
            }

        ListNode *new_node = new ListNode(val); // 定义指向新的节点的指针
        cur->next = new_node;                   // 链接起来
        size++; 
    }
    

    void addAtIndex(int index, int val) {
        if (index < 0 || index > size)
            return;

        if (index == 0) {
            addAtHead(val);
            return;
        }

        ListNode *cur = head;
        for (int i = 0; i < index - 1; i++){
            cur = cur->next;
        }
        // 现在来到要加的前一个
        ListNode *new_node = new ListNode(val);
        new_node->next = cur->next;
        cur->next = new_node;
        size++;
    }

    void deleteAtIndex(int index) {
        if (index < 0 || index >= size) return;
        
        ListNode *cur = head;
        
        if (index == 0) {
            head = head->next;
            delete cur;
            --size;
            return;
        }
         for (int i = 0; i < index - 1; i++){
            cur = cur->next;
        }
        // 现在来到要删除的前一个
        ListNode *tmp = cur->next;
        cur->next = cur->next->next;
        delete tmp;
        size--;
    }
};


int main() {
    MyLinkedList *myLinkedList = new MyLinkedList();
    myLinkedList->addAtHead(1);
    myLinkedList->addAtTail(3);
    myLinkedList->addAtIndex(1, 2);
    std::cout << myLinkedList->get(1) << std::endl;
    myLinkedList->deleteAtIndex(1);
    std::cout << myLinkedList->get(1) << std::endl;

    delete myLinkedList;

    return 0;
}

```

# 4. 反转链表

## 4.1 双指针法
```cpp
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode *cur = head; // 定义当前位置指针
        ListNode *prev = NULL; // 定义当前位置指针

        while (cur != NULL){
            ListNode *next_node = cur->next;
            cur->next = prev;     // 这里链接起来           
            prev = cur;           // prev上一位
            cur = next_node;      // cur上一位
        }
        return prev;
    }
};
```

递归的写法，复习一下递归
```cpp
class Solution {
public:
    ListNode* reverse(ListNode* prev, ListNode* cur){
        if (cur == NULL)
            return prev;

        ListNode *next_node = cur->next;
        cur->next = prev;

        return reverse(cur, next_node);
    }

public:
    ListNode* reverseList(ListNode* head) {
        return reverse(NULL, head);
    }
};
```

完整的代码
```cpp
#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* reverse(ListNode* prev, ListNode* cur){
        if (cur == NULL)
            return prev;

        ListNode *next_node = cur->next;
        cur->next = prev;

        return reverse(cur, next_node);
    }

public:
    ListNode* reverseList(ListNode* head) {
        return reverse(NULL, head);
    }
};

// 辅助函数：打印链表
void printList(ListNode* head) {
    ListNode* current = head;
    while (current != nullptr) {
        std::cout << current->val << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

int main() {
    Solution solution;

    // 示例
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);

    std::cout << "Original List: ";
    printList(head);

    ListNode* newHead = solution.reverseList(head);

    std::cout << "Reversed List: ";
    printList(newHead);

    return 0;
}

```
# 5. 反转链表

给你一个链表，两两交换其中相邻的节点，并返回交换后链表的头节点。你必须在不修改节点内部的值的情况下完成本题（即，只能进行节点交换）。

示例 1：

输入：head = [1,2,3,4]
输出：[2,1,4,3]

示例 2：

输入：head = []
输出：[]

示例 3：

输入：head = [1]
输出：[1]
 
核心就是两两交换，这个循环就要确保一定后面两个要有， 然后正常链起来就可以了
```cpp
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        // 1. 创建虚拟头结点
        ListNode *dummy = new ListNode(0);
        dummy->next = head;

        // 2. 遍历链表，为了两两交换，后面两个都不能为空
        // 0 -> 1 -> 2 -> 3 -> 4 
        ListNode *cur = dummy;
        while (cur->next != NULL && cur->next->next != NULL){
            ListNode *tmp1 = cur->next;              // 1 -> 2 -> 3 -> 4 
            ListNode *tmp2 = cur->next->next->next;  // 3 -> 4

            cur->next = cur->next->next;             // 0 -> 2 -> 3 -> 4
            cur->next->next = tmp1;                  //  0 -> 2 -> 1 -> 2 -> 3 -> 4 
            cur->next->next->next = tmp2;               

            cur = cur->next->next;                   // 0 -> 2 -> 1 -> 3 -> 4
            
        }
        return dummy->next;
    }
};
```

# 6. 删除链表的倒数第 N 个结点
https://leetcode.cn/problems/remove-nth-node-from-end-of-list/description/

给你一个链表，删除链表的倒数第 n 个结点，并且返回链表的头结点。

示例 1：

输入：head = [1,2,3,4,5], n = 2

输出：[1,2,3,5]

示例 2：

输入：head = [1], n = 1

输出：[]

示例 3：

输入：head = [1,2], n = 1

输出：[1]

**思路:** 让快指针先走n步, 这个时候快慢指针间隔是n, 然后让慢指针一起走, 
当n走到null时, 慢指针刚好是倒数第n-1个, 因为快慢间隔n, 快在NULL = 末尾 + 1
如果是用虚拟头结点的话, 要让快指针先走n+1个单位

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */


/*
思路: 思路: 让快指针先走n步, 这个时候快慢指针间隔是n, 然后让慢指针一起走, 
当n走到null时, 慢指针刚好是倒数第n-1个, 因为快慢间隔n, 快在NULL = 末尾 + 1
如果是用虚拟头结点的话, 要让快指针先走n+1个单位
*/
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        // 创建虚拟头结点, 快慢指针
        ListNode *dummy = new ListNode(0);
        dummy->next = head;
        ListNode *fast = dummy;
        ListNode *slow = dummy;

        // 让快指针先走n+1
        for (int i = 0; i < n+1; i++){
            fast = fast->next; // 移动
        }

        // 快慢指针一起走直到快指针走到NULL
        while (fast != NULL ){
            fast = fast->next; 
            slow = slow->next; 
        }

        // 这个时候slow指向要被删除的前一个, 走正常的删除操作
        ListNode *tmp = slow->next;
        slow->next = slow->next->next;
        delete tmp;

        
        return dummy->next;
    }
};
```