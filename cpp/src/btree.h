#ifndef ALGO_BTREE_H
#define ALGO_BTREE_H

#include <vector>
#include <algorithm>

using namespace std;

namespace myalgo{
enum REMOVE {
    removeItem,
    removeMin,
    removeMax
};

template <class K, class V, int d> class BTree;

template <class K, class V>
struct Entry {
    Entry(K key, V value): key(key), value(value) {}
    bool operator<(Entry<K, V>& rhs) {
        return key < rhs.key;
    }

    bool operator==(Entry<K, V>& rhs) {
        return key == rhs.key;
    }

    bool operator!=(Entry<K, V>& rhs) {
        return key != rhs.key;
    }

    K key;
    V value;
};

template <class K, class V, int d>
class BTreeNode {
    friend class BTree<K, V, d>;
public:
    explicit BTreeNode(): items(), children() {
        items.reserve(2*d-1);
        children.reserve(2*d-1);
    }

    void insert_item_at(int index, Entry<K, V>item) {
        items.insert(items.begin()+index, item);
    }

    void insert_child_at(int index, BTreeNode *node) {
        children.insert(children.begin()+index, node);
    }

    void grow_child_and_remove(int i, int min_items, REMOVE typ) {

    }

    /// 分裂节点, ith item 放在原节点最后一位
    BTreeNode* split(int i) {
        BTreeNode* next = new BTreeNode();
        std::copy(items.begin()+i+1, items.end(), std::back_inserter(next->items));
        items.erase(items.begin()+i+1, items.end());
        if (children.size() > 0) {
            std::copy(children.begin()+i+1, children.end(), std::back_inserter(next->children));
            children.erase(children.begin()+i+1, children.end());
        }

        return next;
    }

    Entry<K, V> insert(Entry<K, V> item, int max_items) {
        int i = find_item(item);
        if (i < items.size() && items[i] == item) {
            auto out = items[i];
            items[i] = item;
            return out;
        }
        if (children.size() == 0) {
            items.insert(items.begin()+i, item);
            return item;
        }
        if (maybe_split_child(i, max_items)) {
            Entry<K, V> in_tree = items[i];
            if (in_tree < item) {
                ++i;
            } else if (item == in_tree) {
                items[i] = item;
                return in_tree;
            }
        }

        return children[i]->insert(item, max_items);
    }

    bool maybe_split_child(int i, int max_items) {
        if (children[i]->items.size() < max_items) {
            return false;
        }

        BTreeNode* first = children[i];
        BTreeNode* second = first->split(max_items/2);
        insert_item_at(i, first->items.back());
        first->items.pop_back();
        insert_child_at(i+1, second);
        return true;
    }

private:
    int find_item(Entry<K, V> item) {
        int i = 0;
        while (i < items.size() && items[i] < item) {
            ++i;
        }

        return i;
    }

private:
    std::vector<Entry<K, V>> items;
    std::vector<BTreeNode<K, V, d> *> children;
};



template <class K, class V, int d>
class BTree {
public:
    explicit BTree(): length(0), root(nullptr) {};

    Entry<K, V> replace_or_insert(K key, V value) {
        Entry<K, V> item{key, value};
        if (root == nullptr) {
            root = new BTreeNode<K, V, d>();
            root->insert_item_at(0, item);
            ++length;
            return item;
        } else {
            if (root->items.size() >= max_items()) {
                auto second = root->split(max_items() / 2);
                auto oldroot = root;
                root = new BTreeNode<K, V, d>();
                root->items.push_back(oldroot->items.back());
                oldroot->items.pop_back();
                root->children.push_back(oldroot);
                root->children.push_back(second);
            }
        }
        auto out = root->insert(item, max_items());
        if (item == out) {
            ++length;
        }

        return out;
    }

private:
    int max_items() {
        return d*2 -1;
    }

    int min_items() {
        return d - 1;
    }

private:
    BTreeNode<K, V, d> *root;
    int length{};
};
}

#endif //ALGO_BTREE_H
