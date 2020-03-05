#include "skip_list.h"
#include <iostream>

using namespace myalgo;

int main() {
    SkipList skip;

    skip.insert(1);
    skip.insert(3);
    skip.insert(20);
    skip.insert(25);
    skip.insert(3);
    skip.insert(4);
    skip.insert(5);
    skip.insert(11);

    skip.printAll();


    SkipList skip2;

    skip2.insert2(1);
    skip2.insert2(3);
    skip2.insert2(20);
    skip2.insert2(25);
    skip2.insert2(3);
    skip2.insert2(4);
    skip2.insert2(5);
    skip2.insert2(11);
    skip2.deleteNode(4);

    skip2.printAll();

    std::cout << skip2.find(4) << std::endl;
}