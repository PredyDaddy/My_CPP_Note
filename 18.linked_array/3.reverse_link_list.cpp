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
