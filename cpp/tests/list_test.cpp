#include "list.h"

#include <list>
#include <iostream>

using namespace myalgo;

int main() {
    LinkedList list;

    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    assert(list.front() == 1);
    assert(list.back() == 3);

    assert(list.pop_front() == 1);
    assert(list.pop_back() == 3);
    assert(list.pop_back() == 2);

    list.push_front(1);
    list.push_front(2);
    list.push_back(3);
    assert(list.pop_front() == 2);
    assert(list.pop_front() == 1);
    assert(list.pop_front() == 3);

    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    Node *n = list.get_node(2);
    list.insertAfter(n, 4);
    assert(list.pop_front() == 1);
    assert(list.pop_front() == 2);
    assert(list.pop_front() == 4);
    assert(list.pop_front() == 3);

    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.reverse();
    assert(list.pop_front() == 3);
    assert(list.pop_front() == 2);
    assert(list.pop_front() == 1);

    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.remove_last_index(0);
    assert(list.pop_back() == 2);
    assert(list.pop_back() == 1);

    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    assert(list.middle()->value == 2);
    list.push_back(4);
    assert(list.middle()->value == 2);


    LinkedList first, second;
    first.push_back(1);
    first.push_back(3);
    first.push_back(4);

    second.push_back(2);
    second.push_back(5);

    first.merge(second);

    LinkedList l;
    Node *f = new Node(1);
    Node *s = new Node(2);
    Node *t = new Node(3);

    f->next = s;
    s->next = t;
    l.insert_node_after(nullptr, f);
    assert(l.check_loop() == false);

    t->next = f;
    assert(l.check_loop());
}