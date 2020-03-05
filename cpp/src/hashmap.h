#ifndef ALGO_HASHMAP_H
#define ALGO_HASHMAP_H

#include <functional>
#include <iostream>

namespace myalgo{
// 散列表默认长度
const int DEFAULT_INITIAL_CAPACITY = 8;
// 装载因子
const float LOAD_FACTOR = 0.75;

template<class K, class V>
class Entry;

template <class K, class V>
class HashTable {
public:
    HashTable():
    table(new Entry<K, V>*[DEFAULT_INITIAL_CAPACITY]),
    length(DEFAULT_INITIAL_CAPACITY),
    size(0),
    used(0) {}

    void insert(K key, V value) {
        size_t index = hash(key);
        if (table[index] == nullptr) {
            table[index] = new Entry<K, V>();
        }

        Entry<K, V> *temp = table[index];
        if (temp->next == nullptr) {
            temp->next = new Entry<K, V>(key, value, nullptr);
            ++used;
            ++size;
            // 动态扩容
            if (used >= LOAD_FACTOR * length ) {
                resize();
            }
        } else { // 使用链表发解决hash冲突
            while (temp->next != nullptr) {
                if (temp->next->key == key) {
                    break;
                }
                temp = temp->next;
            }

            if (temp->next != nullptr && temp->next->key == key) {
                temp->next->value = value;
            } else {
                temp->next = new Entry<K, V>(key, value, nullptr);
                ++size;
            }
        }
    }

    V find(K key) {
        auto index = hash(key);
        auto temp = table[index]->next;
        while (temp != nullptr) {
            if (temp->key == key) {
                return temp->value;
            }

            temp = temp->next;
        }

        return V{};
    }

    void remove(K key) {
        auto index = hash(key);
        auto temp = table[index];
        if (temp == nullptr || temp->next == nullptr) {
            return;
        }
        while (temp->next != nullptr) {
            if (temp->next->key == key) {
                auto target = temp->next;
                temp->next = temp->next->next;
                free(target);
                --size;
                if (table[index]->next == nullptr) {
                    --used;
                }

                return;
            }

            temp =  temp->next;
        }
    }

    void printall() {
        for (int i = 0; i < length; ++i) {
            std::cout << i << ":";
            auto temp = table[i];
            while (temp != nullptr && temp->next != nullptr) {
                std::cout << temp->next->key << ": " << temp->next->value << " ";

                temp = temp->next;
            }

            std::cout << std::endl;
        }
    }


private:
    size_t hash(K key) {
        return std::hash<K>{}(key) % length;
    }

    void resize() {
        auto old_table = table;
        table = new Entry<K, V>*[2 * length];
        length *= 2;
        used = 0;
        size = 0;

        for (int i = 0; i < length / 2; ++i) {
            auto temp = old_table[i];
            while (temp != nullptr && temp->next != nullptr) {
               insert(temp->next->key, temp->next->value);
               temp = temp->next;
            }
        }
    }

private:
    Entry<K, V> **table;
    int length;
    int used;
    int size;

};

template <class K, class V>
class Entry {
    friend HashTable<K, V>;
public:
    Entry() = default;
    Entry(K k, V v, Entry<K, V> *n): key(k), value(v), next(n) {}

private:
    K key;
    V value;
    Entry<K, V> *next;


};
}

#endif //ALGO_HASHMAP_H
