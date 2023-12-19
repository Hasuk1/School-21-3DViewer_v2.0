// #include "model/parser/file_parser.h"

#include <iostream>
#include <set>

int main() {
    std::pair<unsigned int, unsigned int> pr1(1, 2);
    std::pair<unsigned int, unsigned int> pr3(4, 1);
    std::pair<unsigned int, unsigned int> pr4(3, 2);
    std::pair<unsigned int, unsigned int> pr5(91, 76);
    std::pair<unsigned int, unsigned int> pr6(3, 1);
    std::pair<unsigned int, unsigned int> pr2(4, 1);
    std::pair<unsigned int, unsigned int> pr2inv(pr2.second, pr2.first);

    std::set<std::pair<unsigned int, unsigned int>> kek;
    kek.insert(pr1);
    kek.insert(pr3);
    kek.insert(pr4);
    kek.insert(pr5);
    kek.insert(pr6);

    if (kek.find(pr2) == kek.end() && kek.find(pr2inv) == kek.end()) {
        kek.insert(pr2);
    }

    for (const auto& x : kek) {
        std::cout << "(" << x.first << ", " << x.second << ")\n";
    }

    return 0;
}
