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
