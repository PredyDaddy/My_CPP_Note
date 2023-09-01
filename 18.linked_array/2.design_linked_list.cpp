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
