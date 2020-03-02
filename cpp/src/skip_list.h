#ifndef ALGO_SKIP_LIST_H
#define ALGO_SKIP_LIST_H

#include <cstdlib>
#include <cstdio>
#include <iostream>

namespace myalgo{
const int MAX_LEVEL = 16;

struct Node {
    Node() = default;

    int data = -1;
    Node *forward[MAX_LEVEL]{};
    int max_level = 0;
};

class SkipList {
public:
    SkipList(): head(new Node), levelCount(1) {
    }

    void insert(int value) {
        int level = random();

        Node *newNode = new Node();
        newNode->data = value;
        newNode->max_level = level;

        Node *update[level];
        for (int i = level-1; i >=0 ; --i) {
            update[i] = head;
        }

        Node *p = head;
        for (int i = level-1; i >=0 ; --i) {
            while (p->forward[i] != nullptr && p->forward[i]->data < value) {
                p = p->forward[i];
            }
            update[i] = p;
        }

        for (int i = level-1; i >=0 ; --i) {
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }

        if (levelCount < level) {
            levelCount = level;
        }

    }

    void insert2(int value) {
        int level = head->forward[0] == nullptr ? 1 : random();
        if (level > levelCount) {
            level = ++levelCount;
        }

        Node *newNode = new Node();
        newNode->data = value;
        newNode->max_level = level;

        Node *p = head;
        for (int i = level; i >= 0; --i) {
            while (p->forward[i] != nullptr && p->forward[i]->data < value) {
                p = p->forward[i];
            }

            newNode->forward[i] = p->forward[i];
            p->forward[i] = newNode;
        }

        if (level > levelCount) {
            levelCount = level;
        }
    }

    Node *find(int value) {
        Node *p = head;
        for (int i = levelCount; i >= 0 ; --i) {
            while (p->forward[i] != nullptr && p->forward[i]->data < value) {
                p = p->forward[i];
            }
        }

        if (p->forward[0] != nullptr && p->forward[0]->data == value ) {
            return p->forward[0];
        } else {
            return nullptr;
        }
    }

    void deleteNode(int value) {
        Node *p = head;
        Node *target = nullptr;
        for (int i = levelCount; i >= 0 ; --i) {
            while (p->forward[i] != nullptr && p->forward[i]->data < value) {
                p = p->forward[i];
            }
            if (i == 0) {
                target = p->forward[0];
            }

            if (p->forward[i] != nullptr && p->forward[i]->data == value) {
                p->forward[i] = p->forward[i]->forward[i];
            }
        }

        if (target != nullptr && target->data == value) {
            free(target);
        }
    }

    int random() {
        int level = 1;
        for (int i = 0; i < MAX_LEVEL; ++i) {
            if (rand() % 2 == 1) {
                ++level;
            }
        }

        return level;
    }

    void printAll() {
        Node *p = head->forward[0];
        while (p != nullptr) {
            std::cout << p->data << " ";
            p = p->forward[0];
        }
        std::cout << std::endl;
    }

private:
    int levelCount;
    Node *head;
};

}

#endif //ALGO_SKIP_LIST_H
