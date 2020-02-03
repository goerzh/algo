#include <vector>
#include <iostream>
#include "vec.h"
#include <new>

using namespace myalgo;

void noMemory() {
    std::cout << "not enough memory";
    abort();
}

int main() {
    Vec<int> v(5);

    v.push_back(1);
    v.push_back(1);
    v.push_back(1);
    v.insert(2, 3);
    assert(v.get(2) == 3);
    v.remove(2);
    assert(v.get(2) == 1);
    v.push_back(1);
    v.push_back(1);
    v.push_back(1);
    assert(v.capital() == 10);

//    std::set_new_handler(noMemory);
//
//    auto i = new int[1000000000000000];
}