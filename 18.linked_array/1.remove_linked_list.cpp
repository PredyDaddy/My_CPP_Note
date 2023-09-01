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
        // 删除头结点, 当头结点的val等于我们要删除的val的时候使用的
        while (head != NULL && head->val == val){
            ListNode* tmp = head; // tmp, head指向同一内存空间
            head = head->next; // 头结点指针指向原来链表的第二个节点
            delete tmp;
        }

        // 删除非头结点的节点
        ListNode *cur = head; // 当前指针是head
        while (cur != NULL){
            if (cur->val == val){
                ListNode* tmp = cur; // tmp, head指向同一内存空间
                cur = cur->next; // 头结点指针指向原来链表的第二个节点
                delete tmp;
            }
            else{
                cur = cur->next;
            }
        }
        // 处理链表只有一个节点且值等于 val 的情况
        if (cur != NULL && cur->val == val) {
            delete cur;
            head = NULL; // 链表为空
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
    delete newHead1;
    delete newHead2;
    delete newHead3;
    return 0;
}
