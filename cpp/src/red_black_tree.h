#ifndef ALGO_RED_BLACK_TREE_H
#define ALGO_RED_BLACK_TREE_H

#include <queue>
#include <iostream>

namespace myalgo{
enum Color { BLACK, RED };

std::ostream& operator<<(std::ostream& out, const Color c) {
    if (c == BLACK) {
        return out << "BLACK";
    } else {
        return out << "RED";
    }
}

template <class T> class RBTreeNode;

template <class T>
class RedBlackTree {
public:
    RedBlackTree():
    root(nullptr),
    nil_node(new RBTreeNode<T>(T(), BLACK, nullptr, nullptr, nullptr)) {}

    void insert(T value) {
        auto p = root;
        if (root == nullptr) {
            root = new RBTreeNode<T>(value);
            p = root;
        } else {
            while (p != nil_node) {
                if (value < p->value) {
                    if (p->left == nil_node) {
                        p->left = new RBTreeNode<T>(value);
                        p->left->parent = p;

                        p = p->left;
                        break;
                    }
                    p = p->left;
                } else {
                    if (p->right == nil_node) {
                        p->right = new RBTreeNode<T>(value);
                        p->right->parent = p;

                        p = p->right;
                        break;
                    }
                    p = p->right;
                }
            }
        }
        p->left = nil_node;
        p->right = nil_node;

        fixAfterInsert(p);
    }

    void fixAfterInsert(RBTreeNode<T> *p) {
        p->color = RED;
        while (p != root && p->parent->color == RED) {
            RBTreeNode<T> *uncle;
            if (p->parent == p->parent->parent->left) {
                uncle = p->parent->parent->right;
            } else {
                uncle = p->parent->parent->left;
            };
            /// 情况1
            if (getColor(uncle) == RED) {
                setColor(p->parent, BLACK);
                setColor(uncle, BLACK);
                setColor(p->parent->parent, RED);
                p = p->parent->parent;
            /// 情况2
            } else if (getColor(uncle) == BLACK && p == p->parent->right) {
                p = p->parent;
                rotateLeft(p);
            /// 情况3
            } else if (getColor(uncle) == BLACK && p == p->parent->left) {
                rotateRight(p->parent->parent);
                setColor(p->parent, BLACK);
                setColor(p->parent->right, RED);
            }
        }
        root->color = BLACK;
    }
    void remove() {}

    void level_order() {
        std::queue<RBTreeNode<T> *> q1;
        std::queue<RBTreeNode<T> *> q2;
        q1.push(root);

        while (!q1.empty() || !q2.empty()) {
            while (!q1.empty()) {
                RBTreeNode<T> *p = q1.front();
                q1.pop();
                if (p->left != nullptr) {
                    q2.push(p->left);
                }
                if (p->right != nullptr) {
                    q2.push(p->right);
                }
                if (p == nil_node) {
                    std::cout << "nil:" << p->color << " ";
                } else {
                    std::cout << p->value << ":" << p->color << " ";
                }
            }
            std::cout << std::endl;

            while (!q2.empty()) {
                auto p = q2.front();
                q2.pop();
                if (p->left != nullptr) {
                    q1.push(p->left);
                }
                if (p->right != nullptr) {
                    q1.push(p->right);
                }
                if (p == nil_node) {
                    std::cout << "nil:" << p->color << " ";
                } else {
                    std::cout << p->value << ":" << p->color << " ";
                }
            }
            std::cout << std::endl;
        }
    }

private:
    void rotateLeft(RBTreeNode<T> *p) {
        if (p == nullptr) {
            return;
        }
        auto r = p->right;
        p->right = r->left;
        if (r->left != nil_node) {
            r->left->parent = p;
        }
        r->parent = p->parent;
        if (p->parent == nullptr) {
            root = r;
        } else if (p == p->parent->left) {
            p->parent->left = r;
        } else {
            p->parent->right = r;
        }

        r->left = p;
        p->parent = r;

    }
    void rotateRight(RBTreeNode<T> *p) {
        if (p == nullptr) {
            return;
        }
        auto l = p->left;
        p->left = l->right;
        if (l->right != nil_node) {
            l->right->parent = p;
        }
        l->parent = p->parent;
        if (p->parent == nullptr) {
            root = l;
        } else if (p->parent->left == p) {
            p->parent->left = l;
        } else {
            p->parent->right = l;
        }

        l->right = p;
        p->parent = l;
    }

private:
    RBTreeNode<T> *root;
    RBTreeNode<T> *nil_node;
};

template <class T>
class RBTreeNode {
    friend class RedBlackTree<T>;
//    friend RBTreeNode<T>* LeftOf(RBTreeNode<T>*);
//    friend RBTreeNode<T> *RightOf(RBTreeNode<T> *node);
//    friend RBTreeNode<T> *ParentOf(RBTreeNode<T> *node);
public:
    friend void setColor(RBTreeNode *p, Color c) {
        p->color = c;
    }
    friend Color getColor(RBTreeNode *p) {
        return p->color;
    }

    RBTreeNode() = default;
    explicit RBTreeNode(T value): value(value) {}
    RBTreeNode(T value, Color color, RBTreeNode<T> *left, RBTreeNode<T> *right, RBTreeNode<T> *parent)
        : color(color), left(left), right(right), parent(parent) {}

private:
    T value;
    Color color = RED;
    RBTreeNode<T> *left;
    RBTreeNode<T> *right;
    RBTreeNode<T> *parent;
};

}

#endif //ALGO_RED_BLACK_TREE_H
