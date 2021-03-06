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

private:
    void insert_item_at(int index, Entry<K, V>item) {
        items.insert(items.begin()+index, item);
    }

    void insert_child_at(int index, BTreeNode *node) {
        children.insert(children.begin()+index, node);
    }

    int grow_child(int i, int min_items) {
        if (i > 0 && children[i-1]->items.size() > min_items) {
            /// Steal from left child
            BTreeNode* child = children[i];
            BTreeNode* steal_from = children[i-1];
            auto stolen_item = steal_from->items.back();
            steal_from->items.pop_back();
            child->insert_item_at(0, items[i-1]);
            items[i-1] = stolen_item;
            if (steal_from->children.size() > 0) {
                child->insert_child_at(0, steal_from->children.back());
                steal_from->children.pop_back();
            }
        } else if (i < items.size() && children[i+1]->items.size() > min_items) {
            BTreeNode* child = children[i];
            BTreeNode* steal_from = children[i+1];
            auto stolen_item = steal_from->items.front();
            steal_from->items.erase(steal_from->items.begin());
            child->items.push_back(items[i]);
            items[i] = stolen_item;
            if (steal_from->children.size() > 0) {
                child->children.push_back(steal_from->children.front());
                steal_from->children.erase(steal_from->children.begin());
            }
        } else {
            if (i >= items.size()) {
                --i;
            }
            BTreeNode* child = children[i];
            BTreeNode* merge_child = children[i+1];
            children.erase(children.begin()+i+1);
            auto merge_item = items[i];
            items.erase(items.begin()+i);
            child->items.push_back(merge_item);
            std::copy(
                    merge_child->items.begin(),
                    merge_child->items.end(),
                    std::back_inserter(child->items)
            );
            std::copy(
                    merge_child->children.begin(),
                    merge_child->children.end(),
                    std::back_inserter(child->children)
            );
            free(merge_child);
        }
        return i;
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

    Entry<K, V> remove_min(int min_items) {
        if (children.size() == 0) {
            auto out = items.front();
            items.erase(items.begin());
            return out;
        }
        int i = 0;
        if (children[i]->items.size() <= min_items) {
            grow_child(i, min_items);
        }

        BTreeNode* child = children.front();
        return child->remove_min(min_items);
    }

    Entry<K, V> remove_max(int min_items) {
        if (children.size() == 0) {
            auto out = items.back();
            items.pop_back();
            return out;
        }
        /// If we get to here, we have children
        int i = items.size();
        if (children[i]->items.size() <= min_items) {
            /// change items and children
            grow_child(i, min_items);
        }

        BTreeNode *child = children.back();
        return child->remove_max(min_items);
    }

    bool remove(Entry<K, V>& item, int min_items) {
        int i = 0;
        i = find_item(item);
        if (children.size() == 0) {
            if (i < items.size() && items[i] == item) {
                items.erase(items.begin()+i);
                return true;
            }
            return false;
        }
        /// If we get to here, we have children
        if (children[i]->items.size() <= min_items) {
            /// change items and children
            i = grow_child(i, min_items);
        } else {
            /// no change
            BTreeNode *child = children[i];
            /// found
            if (i < items.size() && items[i] == item) {
                items[i] = child->remove_max(min_items);
                return true;
            }
            return child->remove(item, min_items);
        }
        /// Final recursive call. Once we're here, we know that the item isn't in this
        /// node and that the child is big enough to remove from.
        return remove(item, min_items);
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

    void remove(K key) {
        remove_item(Entry<K, V>(key, 0));
    }

private:
    bool remove_item(Entry<K, V> item) {
        if (root == nullptr || root->items.size() == 0) {
            return false;
        }
        bool found = root->remove(item, min_items());
        if (root->items.size() == 0 && root->children.size() > 0) {
            auto oldroot = root;
            root = root->children[0];
            free(oldroot);
        }
        if (found) {
            --length;
        }

        return found;
    }

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
