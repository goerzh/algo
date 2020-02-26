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
    SkipList(): head(new Node), levelCount(0) {
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
    Node *find(int value) {
        Node *p = head;
        for (int i = levelCount; i >= 0 ; --i) {
            while (p->forward[i] != nullptr && p->forward[i]->data < value) {
                p = p->forward[i];
            }
        }

        if (p != nullptr && p->data == value ) {
            return p;
        } else {
            return nullptr;
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
