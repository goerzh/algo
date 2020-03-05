#ifndef ALGO_BINARY_SEARCH_TREE_H
#define ALGO_BINARY_SEARCH_TREE_H

#include <iostream>
#include <queue>

namespace myalgo{
template <class T>
class TreeNode;

template <class T>
class BinarySearchTree {
public:
    BinarySearchTree(): root(nullptr) {}

    void insert(T value) {
        if (root == nullptr) {
            root = new TreeNode<T>(value, nullptr, nullptr);
            return;
        }
        auto p = root;
        TreeNode<T> *pp = nullptr;
        do {
            pp = p;
            if (value < p->value) {
                p = p->left;
            } else {
                p = p->right;
            }
        } while (p != nullptr);

        if (value < pp->value) {
            pp->left = new TreeNode<T>(value, nullptr, nullptr);
        } else {
            pp->right = new TreeNode<T>(value, nullptr, nullptr);
        }
    }

    TreeNode<T>* find(T value) {
        auto p = root;
        while (p != nullptr && p->value != value) {
            if (value < p->value) {
                p = p->left;
            } else {
                p = p->right;
            }
        }
        return p;
    }

    void remove(T value) {
        if (root == nullptr) {
            return;
        }

        TreeNode<T> *pp = nullptr;
        auto p = root;

        while (p != nullptr && p->value != value) {
            pp = p;
            if (value < p->value) {
                p = p->left;
            } else {
                p = p->right;
            }
        }
        if (p == nullptr) {
            return;
        }

        if (p->left != nullptr && p->right != nullptr) {
            auto minpp = p;
            auto minp = p->right;
            while (minp->left != nullptr) {
                minpp = p;
                minp = p->left;
            }
            p->value = minp->value;

            pp = minpp;
            p = minp;
        }

        TreeNode<T> *child;
        if (p->left != nullptr) {
            child = p->left;
        } else if (p->right != nullptr) {
            child = p->right;
        } else {
            child = nullptr;
        }

        if (pp == nullptr) {
            root = child;
        } else if (pp->left == p) {
            pp->left = child;
        } else {
            pp->right = child;
        }
    }

    void pre_order() {
        _pre_order(root);
        std::cout << std::endl;
    }

    void in_order() {
        _in_order(root);
        std::cout << std::endl;
    }

    void post_order() {
        _post_order(root);
        std::cout << std::endl;
    }

    void level_order() {
        std::queue<TreeNode<T> *> q1;
        std::queue<TreeNode<T> *> q2;
        q1.push(root);

        while (!q1.empty() || !q2.empty()) {
            while (!q1.empty()) {
                TreeNode<T> *p = q1.front();
                q1.pop();
                if (p->left != nullptr) {
                    q2.push(p->left);
                }
                if (p->right != nullptr) {
                    q2.push(p->right);
                }
                std::cout << p->value << " ";
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
                std::cout << p->value << " ";
            }
            std::cout << std::endl;
        }
    }

private:
    void _pre_order(TreeNode<T> *node) {
        if (node == nullptr) {
            return;
        }
        std::cout << node->value << " ";
        _pre_order(node->left);
        _pre_order(node->right);
    }

    void _in_order(TreeNode<T> *node) {
        if (node == nullptr) {
            return;
        }
        _in_order(node->left);
        std::cout << node->value << " ";
        _in_order(node->right);
    }

    void _post_order(TreeNode<T> *node) {
        if (node == nullptr) {
            return;
        }
        _post_order(node->left);
        _post_order(node->right);
        std::cout << node->value << " ";
    }
private:
    TreeNode<T> *root;
};

template <class T>
class TreeNode {
public:
    TreeNode<T> *left;
    TreeNode<T> *right;
    T value;

    TreeNode() = default;
    TreeNode(T value, TreeNode* left, TreeNode* right): value(value), left(left), right(right) {}
};
}

#endif //ALGO_BINARY_SEARCH_TREE_H
