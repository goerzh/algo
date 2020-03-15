#include "btree.h"

using namespace myalgo;

int main() {
    BTree<int, int, 2> mybtree;

    for (int i = 0; i < 10; ++i) {
        mybtree.replace_or_insert(i, i);
    }


}