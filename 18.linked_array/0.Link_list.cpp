#include <iostream>

// 定义链表节点结构
struct Node {
    int data;
    Node* next;
    
    Node(int value) : data(value), next(nullptr) {}
};

// 链表类定义
class LinkedList {
private:
    Node* head;
    
public:
    LinkedList() : head(nullptr) {}
    
    // 插入节点到链表末尾
    void insert(int value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = newNode;
        } else {
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
    }
    
    // 删除指定值的节点
    void remove(int value) {
        if (head == nullptr) {
            return;
        }
        
        if (head->data == value) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }
        
        Node* current = head;
        while (current->next != nullptr && current->next->data != value) {
            current = current->next;
        }
        if (current->next != nullptr) {
            Node* temp = current->next;
            current->next = current->next->next;
            delete temp;
        }
    }
    
    // 遍历链表并打印节点的值
    void print() {
        Node* current = head;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};

int main() {
    LinkedList list;
    
    list.insert(10);
    list.insert(20);
    list.insert(30);
    
    std::cout << "Original List: ";
    list.print();
     
    list.remove(20);
    
    std::cout << "List after removing 20: ";
    list.print();
    
    return 0;
}
