#ifndef ALGO_LIST_H
#define ALGO_LIST_H

#include <cassert>

namespace myalgo {

struct Node {
    int value;
    Node *next;
    Node *prev;

    explicit Node() : Node(0) {}

    explicit Node(int data) : value(data), next(nullptr), prev(nullptr) {}
};

class LinkedList {
public:
    LinkedList() : head(nullptr) {};

    void push_back(int data) {
        Node *n = new Node(data);

        insert_node_after(tail(), n);
    }

    void push_front(int data) {
        Node *n = new Node(data);

        insert_node(head, n);
    }

    void insertAfter(Node *n, int data) {
        assert(n != nullptr);
        Node *new_node = new Node(data);

        Node *position = head;
        while (position != n) {
            position = position->next;
        }

        new_node->next = position->next;
        position->next = new_node;
    }

    void remove(int data) {

        Node *r = get_node(data);
        remove_node(r);

        free(r);
    }

    int pop_back() {
        assert(head != nullptr);
        int data = back();
        remove(data);

        return data;
    }

    int pop_front() {
        assert(head != nullptr);
        int data = head->value;
        remove(data);

        return data;
    }

    int front() {
        assert(head != nullptr);
        return head->value;
    }

    int back() {
        assert(head != nullptr);
        Node *n = head;
        while (n->next != nullptr) {
            n = n->next;
        }
        return n->value;
    }

    Node *get_node(int data) {
        Node *n = head;
        while (n->value != data) {
            n = n->next;
        }

        return n;
    }

    Node *find_index(int index) {
        assert(index < len());
        Node *n = head;
        int i = 0;
        while (i != index) {
            n = n->next;
            i++;
        }

        return n;
    }

    void remove_last_index(int i) {
        Node *target = find_index(len() - i - 1);
        remove_node(target);
    }

    void reverse() {
        Node *old_head = head;
        Node *temp = nullptr;
        head = nullptr;

        while (old_head != nullptr) {
            temp = old_head;
            old_head = old_head->next;

            push_front(temp->value);
        }
    }

    Node *middle() {
        return find_index((len() - 1) / 2);
    }

    void merge(LinkedList &right) {
        Node *first = head;
        Node *second = right.head;
        while (first != nullptr && second != nullptr) {
            if (first->value > second->value) {
                right.remove_node(second);

                second->next = nullptr;
                insert_node(first, second);

                second = right.head;
            } else {
                first = first->next;
            }
        }

        while (second != nullptr) {
            right.remove_node(second);

            insert_node_after(tail(), second);

            second = right.head;
        }
    }

    bool check_loop() {
        Node *slow, *fast;
        slow = head;
        fast = head->next;
        while (slow != fast && fast != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }

        return slow == fast;
    }

    int len() {
        Node *n = head;
        int len = 0;
        while (n != nullptr) {
            n = n->next;
            len++;
        }

        return len;
    }


    void insert_node_after(Node *pos, Node *data) {
        Node **indirect = &head;

        while (*indirect != pos) {
            indirect = &((*indirect)->next);
        }

        if (*indirect == nullptr) {
            *indirect = data;
        } else {
            data->next = (*indirect)->next;
            (*indirect)->next = data;
        }
    }

    void insert_node(Node *pos, Node *data) {
        Node *prev = nullptr;
        Node *cur = head;

        while (cur != pos) {
            prev = cur;
            cur = cur->next;
        }

        if (prev == nullptr) {
            head = data;
            data->next = cur;
        } else {
            prev->next = data;
            data->next = cur;
        }
    }

    void remove_node(Node *n) {
        Node **indirect = nullptr;
        indirect = &head;
        while (*indirect != n) {
            indirect = &((*indirect)->next);
        }

        *indirect = (*indirect)->next;
    }

    Node *tail() {
        Node *pos = head;

        if (head == nullptr) {
            return head;
        }

        while (pos->next != nullptr) {
            pos = pos->next;
        }
        return pos;
    }

private:

    Node *head;
};
}
#endif //ALGO_LIST_H
