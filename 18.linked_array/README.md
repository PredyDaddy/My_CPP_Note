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

## 2.1 以案例来学习链表

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

### 2. main函数中我们new了好多个为什么最后只delete三个？
在示例代码中，有多个 new 运算符用于动态分配内存来创建节点。然而，在使用 delete 释放内存时，我们只需要释放最终创建的链表的头节点。我们的removeElements()函数return的也是head，指向头结点的指针，会在函数里通过面判断是否需要改变头结点的指向

这是因为链表中的节点是通过 next 指针连接的，从而形成链式结构。释放链表中的头节点就会依次释放链表中的所有节点，因为每个节点都通过 next 指针连接。释放链表的头节点相当于释放整个链表。

所以，你只需要使用 delete 释放每个示例中最终创建的链表的头节点，就会释放整个链表的内存，而不需要逐个删除链表中的每个节点。不需要对每个节点使用 delete，因为链表节点之间是通过指针连接的，释放头节点就会自动释放整个链表。


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
        // 删除头结点
        while (head != NULL && head->val == val) { // 注意这里不是if
            ListNode* tmp = head;
            head = head->next;
            delete tmp;
        }

        // 删除非头结点
        ListNode* cur = head;
        while (cur != NULL && cur->next!= NULL) {
            if (cur->next->val == val) {
                ListNode* tmp = cur->next;
                cur->next = cur->next->next;
                delete tmp;
            } else {
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
    head3->next = new ListNode(7);
    head3->next->next = new ListNode(7);
    head3->next->next->next = new ListNode(7);
    int val3 = 7;
    ListNode* newHead3 = solution.removeElements(head3, val3);
    std::cout << "Case 3: ";
    printList(newHead3);

    
    // 释放节点内存
    delete newHead1;
    delete newHead2;
    delete newHead3;
    return 0;
}
```

