#include "binary_search_tree.h"
#include <iostream>

using namespace myalgo;

int main() {
    BinarySearchTree<int> tree;

    tree.insert(1);
    tree.insert(4);
    tree.insert(10);
    tree.insert(5);
    tree.insert(3);
    tree.insert(0);
    tree.insert(-1);

//    tree.remove(4);

    tree.pre_order();
    tree.in_order();
    tree.post_order();
    tree.level_order();

}