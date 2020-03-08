#include "red_black_tree.h"
#include <istream>

using namespace myalgo;

int main() {
    RedBlackTree<int> rbt;

    rbt.insert(7);
    rbt.insert(2);
    rbt.insert(8);
    rbt.insert(1);
    rbt.insert(3);
    rbt.insert(10);
    rbt.insert(0);

    rbt.level_order();
}