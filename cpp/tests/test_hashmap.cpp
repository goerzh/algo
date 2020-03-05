#include "hashmap.h"
#include <string>

using namespace myalgo;

int main() {
    HashTable<int, std::string> table;

    table.insert(3, "123");
    table.insert(4, "13");
    table.insert(3, "3432");
    table.insert(4, "3432");
    table.insert(10, "3432");
    table.insert(3, "3432");
    table.insert(334, "3432");
    table.insert(13, "3432");
    table.insert(233, "3432");
    table.insert(32, "3432");
    table.insert(213, "3432");
    table.insert(43, "3432");
    table.insert(13, "3432");
    table.insert(33, "3432");
    table.insert(193, "3432");
    table.insert(376, "3432");

    table.printall();
}
