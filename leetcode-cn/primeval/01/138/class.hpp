#include <unordered_map>
#include "headers.h"

class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (head == nullptr) {
            return head;
        }
        std::unordered_map<Node*, Node*> ump;
        Node* ret = new Node(head->val);
        ret->next = head->next;
        ret->random = head->random;
        ump[head] = ret;
        for (Node* p = head->next; p != nullptr; p = p->next) {
            Node* q = new Node(p->val);
            q->next = p->next;
            q->random = p->random;
            ump[p] = q;
        }
        for (Node* p = ret; p != nullptr; p = p->next) {
            p->next = ump[p->next];
            p->random = ump[p->random];
        }
        return ret;
    }
};
