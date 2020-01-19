#include <vector>
#include <iostream>
#include "vec.h"

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
}